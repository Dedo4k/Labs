.model small
.stack 100h

.data
    max_path_size           equ 124
    file_path               db max_path_size dup (0)
    old_str                 db max_path_size dup (0)
    buf                     db ?
    buf1_pos_high           dw ?
    buf1_pos_low            dw ?
    buf2_pos_high           dw ?
    buf2_pos_low            dw ?
    PSP                     dw ?
    EOF                     db ?
    check_if_has_word_buf   dw ?
    message_old_str         db "desired word: ", '$'
    message_file_path       db "filename: ", '$'
    wrong_args              db "Wrong args", 0Dh, 0Ah
                            db "Correct format:", 0Dh, 0Ah
                            db "filepath arg1", 0Dh, 0Ah, '$'
    unidentifyed_error      db "unidentified error", 0Dh, 0Ah, '$'
    function_number_invalid db "function number invalid", 0Dh, 0Ah, '$'
    file_not_found          db "file not found", 0Dh, 0Ah, '$'
    path_not_found          db "path not found", 0Dh, 0Ah, '$'
    too_many_open_files     db "too many open files (no handles available)", 0Dh, 0Ah, '$'
    access_denied           db "access denied", 0Dh, 0Ah, '$'
    invalid_handle          db "invalid handle", 0Dh, 0Ah, '$'
    access_code_invalid     db "access code invalid", 0Dh, 0Ah, '$'
    invalid_password        db "invalid password", 0Dh, 0Ah, '$'
.code
    jmp start

check_size macro str
    push cx
    mov di, offset str
    call strlen
    cmp cx, 0
    je parse_command_line_error
    pop cx
endm


printlnz macro str
    mov si, offset str
    call printz
    mov ah, 02h
    mov dl, 0Dh
    int 21h
    mov ah, 02h
    mov dl, 0Ah
    int 21h
endm

parse_command_line proc;
    push si
    push di
    push ax
    push cx

    mov ah, 62h
    int 21h
    mov PSP, bx

    push ds

    mov ds, bx
    xor ah, ah
    mov al, byte ptr ds:[80h]
    pop ds
    cmp al, 0
    je parse_command_line_error

    xor ch, ch
    mov cl, al
    mov si, 81h
    
    mov di, offset file_path
    call get_word
    jc parse_command_line_error

    check_size file_path
    
    mov di, offset old_str
    call get_word
    jc parse_command_line_error

    check_size old_str

    call check_if_ended
    jnc parse_command_line_error

    parse_command_line_fine:
    clc
    jmp parse_command_line_end

    parse_command_line_error:
    stc
    jmp parse_command_line_end

    parse_command_line_end:
    pop cx
    pop ax
    pop di
    pop si
    ret
endp

check_if_ended proc; si - source, cx - size
    push si
    push di
    push ax
    push cx

    mov di, si
    mov al, ' '
    repe scasb
    cmp cx, 0
    je check_if_ended_error

    check_if_ended_fine:
    clc
    jmp check_if_ended_end

    check_if_ended_error:
    stc
    jmp check_if_ended_end

    check_if_ended_end:
    pop cx
    pop ax
    pop di
    pop si
    ret
endp

get_word proc; si - source, di - dest, cx - size; output: si is modified, cx is modified
    push bx
    push ax
    push di
    push ds

    mov ax, PSP
    mov ds, ax

    mov bx, di
    mov di, si
    cmp byte ptr [di], ' '
    jne get_word_no_spaces
    mov al, ' '
    repe scasb
    get_word_no_spaces:
    mov si, di
    mov di, bx
    cmp cx, 0
    je get_word_error

    get_word_space_loop:
        lodsb
        cmp al, ' '
        je get_word_space
        stosb
        loop get_word_space_loop

    jmp get_word_fine

    get_word_space:
    dec cx
    jmp get_word_fine

    get_word_fine:
    clc
    jmp get_word_end

    get_word_error:
    stc
    jmp get_word_end

    get_word_end:
    pop ds
    pop di
    pop ax
    pop bx
    ret
endp

replace_strings proc; bx - file descr
    push di

    xor cx, cx    
    mov EOF, 0

    mov di, offset old_str
    replace_strings_loop:
        ;if (has_word) delete_line();
        call check_if_has_word
        jnc replace_strings_no

        ;printlnz old_str

        call delete_line

        jmp replace_strings_loop

        ;else to_next_line();
        replace_strings_no:
        cmp EOF, 1
        je replace_strings_end
        replace_string_continue:
        call point_to_next
        jmp replace_strings_loop

    replace_strings_end:
    pop di
    ret
endp

delete_line proc; bx - file descr
    push ax
    push bx
    push cx
    push dx

    ;buf_pos = lseek(cur, 0);
    mov ah, 42h
    mov al, 01h
    xor cx, cx
    xor dx, dx
    int 21h
    mov buf1_pos_high, dx
    mov buf1_pos_low, ax

    push dx
    push ax

    delete_line_next_line_loop:
        mov ah, 3Fh
        mov cx, 1
        mov dx, offset buf
        int 21h
        cmp ax, 0
        je delete_line_record_pos
        cmp buf, 0Ah
        je delete_line_record_pos
        jmp delete_line_next_line_loop

    delete_line_record_pos:
    mov ah, 42h
    mov al, 01h
    xor cx, cx
    xor dx, dx
    int 21h
    mov buf2_pos_high, dx
    mov buf2_pos_low, ax

    delete_line_replace_loop:
        mov ah, 42h
        mov al, 0h
        mov cx, buf2_pos_high
        mov dx, buf2_pos_low
        int 21h
        mov ah, 3Fh
        mov cx, 1
        mov dx, offset buf
        int 21h
        cmp ax, 0
        je delete_line_trunc
        mov ah, 42h
        mov al, 01h
        xor cx, cx
        xor dx, dx
        int 21h
        mov buf2_pos_high, dx
        mov buf2_pos_low, ax

        mov ah, 42h
        mov al, 0h
        mov cx, buf1_pos_high
        mov dx, buf1_pos_low
        int 21h
        mov ah, 40h
        mov cx, 1
        mov dx, offset buf
        int 21h
        mov ah, 42h
        mov al, 01h
        xor cx, cx
        xor dx, dx
        int 21h
        mov buf1_pos_high, dx
        mov buf1_pos_low, ax
        jmp delete_line_replace_loop


    delete_line_trunc:
        mov ah, 42h
        mov al, 0h
        mov cx, buf1_pos_high
        mov dx, buf1_pos_low
        int 21h
        mov ah, 40h
        mov cx, 0
        int 21h

    delete_line_end:
    mov ah, 42h
    mov al, 0h
    pop dx
    pop cx
    int 21h

    pop dx
    pop cx
    pop bx
    pop ax
    ret
endp

point_to_next proc; bx - file descr
    push ax
    push cx
    push dx

    point_to_next_loop:
        ;read char
        mov ah, 3Fh 
        mov cx, 1
        mov dx, offset buf
        int 21h
        ;if (EOF) return;
        cmp ax, 0
        je point_to_next_end
        ;if (buf == '\n') return;
        cmp buf, 0Ah
        je point_to_next_end
        ;else continue;
        jmp point_to_next_loop

    point_to_next_end:
    pop dx
    pop cx
    pop ax
    ret
endp

check_if_has_word proc; bx - file descr, di - str; output: c set if has word str
    push ax
    push bx
    push cx
    push dx
    push di
    push si

    mov check_if_has_word_buf, di

    ;save filepos
    mov ah, 42h
    mov al, 01h
    xor cx, cx
    xor dx, dx
    int 21h
    push ax
    push dx


    ;while(true)
    ;{
    check_if_has_word_loop:
    ;    int i = 0;
        mov si, check_if_has_word_buf
    ;    while(true)
    ;    {   
        check_if_has_word_compare_loop:
    ;        char buf_char = str[i++];
            lodsb
    ;        if (buf_char == 0)
    ;            return true;
            cmp al, 0
            je check_if_str_yes
    ;        buf = fread();
            mov di, ax
            mov ah, 3Fh
            mov cx, 1
            mov dx, offset buf
            int 21h
    ;        if (EOF)
    ;            EOF = true;
    ;            return false;
            cmp ax, 0
            mov ax, di
            je check_if_str_eof
    ;        if (buf == '\n')
    ;            return false;
            cmp buf, 0Ah
            je check_if_str_no
    ;        if (buf_char != buf)
    ;            break;
            cmp buf, al
            jne check_if_has_word_skip_to_spaces
    ;        if (buf == ' ')
    ;            goto skip_spaces
            cmp buf, ' '
            je check_if_has_word_skip_spaces


            cmp buf, '.'
            je check_if_has_word_skip_spaces
            cmp buf, ','
            je check_if_has_word_skip_spaces

    ;       if (buf == 0Dh)
    ;           goto skip_spaces
            cmp buf, 0Dh
            je check_if_has_word_skip_spaces
    ;    }
        jmp check_if_has_word_compare_loop

    ;   do
    ;   {
        check_if_has_word_skip_to_spaces:
    ;       buf = fread();
            mov ah, 3Fh
            mov cx, 1
            mov dx, offset buf
            int 21h
    ;       if (EOF)
    ;           EOF = true;
    ;           return false;
            cmp ax, 0
            je check_if_str_eof
    ;       if (buf == '\n')
    ;           return false;
            cmp buf, 0Ah
            je check_if_str_no
    ;   } while(buf != ' ' && buf != 0Dh);
        cmp buf, ' '
        je check_if_has_word_skip_spaces
        cmp buf, 0Dh
        je check_if_has_word_skip_spaces
        cmp buf, '.'
        je check_if_has_word_skip_spaces
        cmp buf, ','
        je check_if_has_word_skip_spaces
        jmp check_if_has_word_skip_to_spaces
    ;
    ;   do
    ;   {
        check_if_has_word_skip_spaces:
    ;       buf = fread();
            mov ah, 3Fh
            mov cx, 1
            mov dx, offset buf
            int 21h
    ;       if (EOF)
    ;           EOF = true;
    ;           return false;
            cmp ax, 0
            je check_if_str_eof
    ;       if (buf == '\n')
    ;           return false;
            cmp buf, 0Ah
            je check_if_str_no
    ;   } while(buf == ' ' || buf == 0Dh);
        cmp buf, ' '
        je check_if_has_word_skip_spaces
        cmp buf, 0Dh
        je check_if_has_word_skip_spaces
        cmp buf, '.'
        je check_if_has_word_skip_spaces
        cmp buf, ','
        je check_if_has_word_skip_spaces
    ;
    ;   lseek(cur, -1);
        mov ah, 42h
        mov al, 01h
        mov cx, 0FFFFh
        mov dx, -1
        int 21h
    ;}
    jmp check_if_has_word_loop

    
        
    check_if_str_eof:
    mov EOF, 1
    jmp check_if_str_no

    check_if_str_yes:
    mov ah, 3Fh
    mov cx, 1
    mov dx, offset buf
    int 21h
    cmp ax, 0
    je check_if_str_final_yes
    cmp buf, ' '
    je check_if_str_final_yes
    cmp buf, 0Dh
    je check_if_str_final_yes
    cmp buf, '.'
    je check_if_str_final_yes
    cmp buf, ','
    je check_if_str_final_yes
    jmp check_if_str_no
    check_if_str_final_yes:
    ;restore filepos
    mov ah, 42h
    mov al, 00h
    pop cx
    pop dx
    int 21h
    ;return_value = true;
    stc
    jmp check_if_str_end

    check_if_str_no:
    ;restore filepos
    mov ah, 42h
    mov al, 00h
    pop cx
    pop dx
    int 21h
    ;return_value = false
    clc
    jmp check_if_str_end

    check_if_str_end:

    pop si
    pop di
    pop dx
    pop cx
    pop bx
    pop ax
    ret
endp

printz proc
    printz_loop:
        lodsb
        cmp al, 0
        je printz_end
        mov ah, 02h
        mov dl, al
        int 21h
        jmp printz_loop
    printz_end:
    ret
endp

print macro str
    mov ah, 09h
    mov dx, offset str
    int 21h
endm


strlen proc; di - str; output: cx - length
    push si
    push ax
    mov si, di
    xor cx, cx

    strlen_loop:
        lodsb
        cmp al, 0
        je strlen_end
        inc cx
        jmp strlen_loop
    
    strlen_end:
    pop ax
    pop si
    ret
endp

start:
    mov ax, @data
    mov ds, ax
    mov es, ax

    call parse_command_line
    jc _error_wrong_args

    print message_file_path
    printlnz file_path
    print message_old_str
    printlnz old_str

    mov ah, 3Dh
    mov al, 0010010b
    mov dx, offset file_path
    int 21h
    jc _error_file
    mov bx, ax

    call replace_strings

    mov ah, 3Eh
    int 21h
    jc _error_file

    jmp _end

    _error_wrong_args:
    print wrong_args
    jmp _end

    _error_file:
    cmp ax, 01h
    je _error_function_number_invalid
    cmp ax, 02h
    je _error_file_not_found
    cmp ax, 03h
    je _error_path_not_found
    cmp ax, 04h
    je _error_too_many_open_files
    cmp ax, 05h
    je _error_access_denied
    cmp ax, 0Ch
    je _error_access_code_invalid
    cmp ax, 56h
    je _error_invalid_password
    print unidentifyed_error
    jmp _end

    _error_function_number_invalid:
    print function_number_invalid
    jmp _end
    _error_file_not_found:
    print file_not_found
    jmp _end
    _error_path_not_found:
    print path_not_found
    jmp _end
    _error_too_many_open_files:
    print too_many_open_files
    jmp _end
    _error_access_denied:
    print access_denied
    jmp _end
    _error_invalid_handle:
    print invalid_handle
    jmp _end
    _error_access_code_invalid:
    print access_code_invalid
    jmp _end
    _error_invalid_password:
    print invalid_password
    jmp _end

    

    _end:
    mov ax, 4C00h
    int 21h
end start