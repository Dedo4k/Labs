.model tiny
org 100h

.data
    max_path_size               equ 124
    buf                         db ?
    psp                         dw ?
    length                      dw 0
    file_ends                   db 0
    exec_file_path              db max_path_size dup(0),0
    file_path                   db max_path_size dup(0),0
    
    wrong_args_msg              db "Wrong args"
                                db "Correct format: filename",10,13,'$'
    unknown_error_msg           db "Unknown error accured",10,13,'$'                            
    operation_error_msg         db "Operation error", 0Dh, 0Ah, '$'
    file_not_found_msg          db "File not found", 0Dh, 0Ah, '$'
    path_not_found_msg          db "Path not found", 0Dh, 0Ah, '$'
    too_many_files_msg          db "Too many files are opened", 0Dh, 0Ah, '$'
    access_denied_msg           db "Access is denied", 0Dh, 0Ah, '$'
    invalid_access_mode_msg     db "Invalid access mode", 0Dh, 0Ah, '$'
    error_start_msg             db "Start Error",10,13,'$'
    newline                     db 10,13,'$'

print macro str
    mov ah,9
    lea dx,str
    int 21h
endm

printlnz macro str
    lea si, str
    call printz
    mov ah, 02h
    mov dl, 0Dh
    int 21h
    mov ah, 02h
    mov dl, 0Ah
    int 21h
endm    

check_size macro str
    push cx
    lea di, str
    call strlen
    cmp cx, 0
        je cmd_error
    pop cx
endm

clrstr macro Z,str
    lea di,str
Z:
    cmp [di],0
        je clrstr_end
    mov [di],0
    inc di
    jmp Z
clrstr_end:        
endm    

shrink_memory macro
    push ax
    push bx
    mov sp, length_of_program + 100h + 200h
    mov ax, length_of_program + 100h + 200h
    shr ax, 4
    inc ax
    mov bx, ax
    mov ah, 4Ah
    int 21h
    pop bx
    pop ax
endm

printz proc
    l3:
        lodsb
        cmp al, 0
            je printz_end
        mov ah, 02h
        mov dl, al
        int 21h
        jmp l3
printz_end:
    ret
endp

strlen proc
    push si
    push ax
    mov si, di
    xor cx, cx

    l2:
        lodsb
        cmp al, 0
            je strlen_end
        inc cx
        jmp l2
    
strlen_end:
    pop ax
    pop si
    ret
endp 

get_word proc
    push bx
    push ax
    push di
    push ds

    ;mov ax, psp
    ;mov ds, ax

    mov bx, di
    mov di, si
    cmp [di], ' '
        jne no_spaces
    mov al, ' '
    repe scasb
no_spaces:
    ;--
    inc cx
    ;--
    mov si, di
    mov di, bx
    cmp cx, 0
        je get_word_error
    ;--
    dec si
    ;--
    l1:
        lodsb
        cmp al, ' '
            je space
        stosb
        loop l1

    jmp get_word_no_error

space:
    dec cx
    jmp get_word_no_error

get_word_end:
    pop ds
    pop di
    pop ax
    pop bx
    ret

;********************************************
get_word_no_error:
    clc
    jmp get_word_end

get_word_error:
    stc
    jmp get_word_end
;********************************************    
endp

check_end proc
    push si
    push di
    push ax
    push cx

    mov di, si
    mov al, ' '
    repe scasb
    cmp cx, 0
        je check_end_error

check_end_no_error:
    clc
    jmp check_end_end

check_end_error:
    stc
    jmp check_end_end

check_end_end:
    pop cx
    pop ax
    pop di
    pop si
    ret
endp

parse_cmd proc
    push si
    push di
    push ax
    push cx

    ;mov ah, 62h     ;загружаем в bx psp
    ;int 21h
    ;mov psp, bx

    ;push ds

    ;mov ds, bx
    xor ah, ah
    mov al, ds:[80h]    ;загружаем длину cmd
    ;pop ds
    cmp al, 0
        je cmd_error

    xor ch, ch
    mov cl, al
    mov si, 81h         ;cmd
    
    lea di, file_path
    call get_word
        jc cmd_error

    check_size file_path

    ;call check_end
    ;    jnc cmd_error

cmd_end:
    pop cx
    pop ax
    pop di
    pop si
    ret
    
;*****************************************
cmd_no_error:
    clc
    jmp cmd_end

cmd_error:
    stc
    jmp cmd_end
;*****************************************    
endp

execute proc
    pusha

exec_files1:
        lea di,exec_file_path
        call get_word_from_file

        prep_for_start:
            shrink_memory
            jc execute_end
            jmp init_EPB
        
        init_EPB:
            mov ax,cs
            mov word ptr EPB+4,ax
            mov word ptr EPB+8,ax
            mov word ptr EPB+0Ch,ax
            
            mov ax,04B00h
            mov cx,dx
            lea dx,exec_file_path
            lea bx,EPB
            int 21h
            jc error_start
            jmp execute_end

error_start:
    push ax
    print error_start_msg
    pop ax
    cmp ax,02h
        je error_1
    cmp ax,05h
        je error_2
    jmp error_3
error_1:
    print file_not_found_msg
error_2:
    print access_denied_msg
error_3:
                            
execute_end:
    call get_word_from_file
    ;jmp exec_files             
    popa
    ret
endp    

get_word_from_file proc
    read:
        mov ah,3Fh
        mov cx,1
        lea dx,buf
        int 21h
        mov cx,ax
        cmp ax,0
            je read_ends
        
        cmp [buf],' '
            je no_word
        
        cmp [buf],10
            je no_word
        
        cmp [buf],13
            je no_word
        
        inc length
        mov dl,[buf]
        mov [di],dl
        inc di
        jmp read       
read_ends:
    mov file_ends,1
    
no_word:
    cmp length,4
        jl wr_length
    jmp read_end
wr_length:
    mov length,0
                    
    read_end:
        ret            
endm

run proc
        prep_for_start2:
            shrink_memory
            jc execute_end
            jmp init_EPB
        
        init_EPB2:
            mov ax,cs
            mov word ptr EPB+4,ax
            mov word ptr EPB+8,ax
            mov word ptr EPB+0Ch,ax
            
            mov ax,04B00h
            mov cx,dx
            ;lea dx,exec_file_path
            lea bx,EPB
            int 21h
            jc error_start2
            jmp error_32
error_start2:
    push ax
    print error_start_msg
    pop ax
    cmp ax,02h
        je error_12
    cmp ax,05h
        je error_22
    jmp error_32
error_12:
    print file_not_found_msg
error_22:
    print access_denied_msg
error_32:
ret
endp

.code
start:
    call parse_cmd
    jc wrong_args_error
    
    printlnz file_path
    
open_file:
    mov ah,3Dh
    mov al,0
    lea dx,file_path
    int 21h
    jc file_error
    mov bx,ax    

;******************************************
q1:    
    lea di,exec_file_path
    call get_word_from_file
        cmp length,4
            jl wr_length2
    printlnz exec_file_path
    lea dx,exec_file_path
    call run
    clrstr R,exec_file_path 
    mov length,0
    
    cmp file_ends,1
        je close_file
    
    jmp q1
wr_length2:
    mov length,0
    call get_word_from_file
    jmp q1    
;******************************************   
    
close_file:
    mov ah, 3Eh
    int 21h
    jc file_error
    
exit:
    mov ax,4C00h
    int 21h    
    
;******************************************
wrong_args_error:
    print wrong_args_msg
    jmp exit

file_error:
    cmp ax, 01h
        je operation_error
    cmp ax, 02h
        je file_not_found
    cmp ax, 03h
        je path_not_found
    cmp ax, 04h
        je too_many_files_are_opened
    cmp ax, 05h
        je access_is_denied
    cmp ax, 0Ch
        je invalid_access_mode
    print unknown_error_msg
    jmp exit

operation_error:
    print operation_error_msg
    jmp exit 
    
file_not_found:
    print file_not_found_msg
    jmp exit
    
path_not_found:
    print path_not_found_msg
    jmp exit
    
too_many_files_are_opened:
    print too_many_files_msg
    jmp exit 
    
access_is_denied:
    print access_denied_msg
    jmp exit  
    
invalid_access_mode:
    print invalid_access_mode_msg
    jmp exit    
;******************************************    

EPB              dw 0000
                 dw offset commandline,0
                 dw 005Ch,0,006Ch,0
                 
commandline      db 124
command_text     db 125 dup(?)

length_of_program equ $-start                 
    
end start