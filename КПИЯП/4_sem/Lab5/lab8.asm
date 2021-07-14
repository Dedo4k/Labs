.model small
.stack 100h

.data
    maxPathSize              equ 124
    filePath                 db maxPathSize dup (0)
    buf                      db ?
    psp                      dw ?
    counter                  dw 0
    hasChar                  db 0
    linux                    db 0
    filePathMsg              db "File name: ", '$'
    wrongArgsMsg             db "Wrong args", 0Dh, 0Ah
                             db "Correct format: filepath arg", 0Dh, 0Ah,'$'
    unknownErrorMsg          db "Unknown error accured", 0Dh, 0Ah, '$'
    operationErrorMsg        db "Operation error", 0Dh, 0Ah, '$'
    fileNotFoundMsg          db "File not found", 0Dh, 0Ah, '$'
    pathNotFoundMsg          db "Path not found", 0Dh, 0Ah, '$'
    tooManyFilesAreOpenedMsg db "Too many files are opened", 0Dh, 0Ah, '$'
    accessIsDeniedMsg        db "Access is denied", 0Dh, 0Ah, '$'
    invalidAccessModeMsg     db "Invalid access mode", 0Dh, 0Ah, '$'
    resultMsg                db "Number of empty strings: $"
    newline                  db 10,13,'$'
        
.code
    jmp start

OutInt proc
    xor     cx, cx
    mov     bx, 10
oi2:
    xor     dx,dx
    div     bx
    push    dx
    inc     cx
    test    ax, ax
    jnz     oi2
    mov     ah, 02h
oi3:
    pop     dx
    add     dl, '0'
    int     21h
    loop    oi3
    
    ret
OutInt endp

checkSize macro str
    push cx
    lea di, str
    call strlen
    cmp cx, 0
        je cmdError
    pop cx
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

cmd proc;
    push si
    push di
    push ax
    push cx

    mov ah, 62h     ;загружаем в bx psp
    int 21h
    mov psp, bx

    push ds

    mov ds, bx
    xor ah, ah
    mov al, ds:[80h]    ;загружаем длину cmd
    pop ds
    cmp al, 0
        je cmdError

    xor ch, ch
    mov cl, al
    mov si, 81h         ;cmd
    
    lea di, filePath
    call getWord
        jc cmdError

    checkSize filePath

    call checkEnd
        jnc cmdError

cmdNoError:
    clc
    jmp cmdEnd

cmdError:
    stc
    jmp cmdEnd

cmdEnd:
    pop cx
    pop ax
    pop di
    pop si
    ret
endp

checkEnd proc
    push si
    push di
    push ax
    push cx

    mov di, si
    mov al, ' '
    repe scasb
    cmp cx, 0
        je checkEndError

checkEndNoError:
    clc
    jmp checkEndEnd

checkEndError:
    stc
    jmp checkEndEnd

checkEndEnd:
    pop cx
    pop ax
    pop di
    pop si
    ret
endp

getWord proc
    push bx
    push ax
    push di
    push ds

    mov ax, psp
    mov ds, ax

    mov bx, di
    mov di, si
    cmp [di], ' '
        jne noSpaces
    mov al, ' '
    repe scasb
noSpaces:
    mov si, di
    mov di, bx
    cmp cx, 0
        je getWordError

    l1:
        lodsb
        cmp al, ' '
            je space
        stosb
        loop l1

    jmp getWordNoError

space:
    dec cx
    jmp getWordNoError

getWordNoError:
    clc
    jmp getWordEnd

getWordError:
    stc
    jmp getWordEnd

getWordEnd:
    pop ds
    pop di
    pop ax
    pop bx
    ret
endp

printz proc
    l3:
        lodsb
        cmp al, 0
            je printzEnd
        mov ah, 02h
        mov dl, al
        int 21h
        jmp l3
printzEnd:
    ret
endp

print macro str
    mov ah, 09h
    lea dx, str
    int 21h
endm


strlen proc
    push si
    push ax
    mov si, di
    xor cx, cx

    l2:
        lodsb
        cmp al, 0
            je strlenEnd
        inc cx
        jmp l2
    
strlenEnd:
    pop ax
    pop si
    ret
endp

count proc
    read:    
    mov ah,3Fh
    mov cx,1
    lea dx,buf
    int 21h
    mov cx,ax
    
    cmp ax,0
    je dollar
    
    ;mov ah,2
    ;mov dl,[buf]
    ;int 21h
        
    cmp [buf],10
    je linuxgo
    
    cmp [buf],13
    je newl
    
    mov hasChar,1
    
    jmp read

linuxgo:
    cmp linux,1
        je nolinux
    cmp hasChar,1
        je has
    inc counter
nolinux:
    jmp read
    
newl:
    mov linux,1
    cmp hasChar,1
        je has
    inc counter
    jmp read
    
has:
    mov hasChar,0
    jmp read

dollar:
    cmp hasChar,1
        je closeFile
    inc counter        
    jmp closeFile
    ret
endp

start:
    mov ax, @data
    mov ds, ax
    mov es, ax

    call cmd
    jc wrongArgsError

    print filePathMsg
    printlnz filePath

    mov ah, 3Dh
    mov al, 0010010b
    lea dx, filePath
    int 21h
    jc fileError
    mov bx, ax

;----------------------------------------------    

    call count        
    
;----------------------------------------------

closeFile:    
    mov ah, 3Eh
    int 21h
    jc fileError
    
    print newline
    print resultMsg
    
    xor ax,ax
    mov ax,counter
    call OutInt
        
    jmp exit

wrongArgsError:
    print wrongArgsMsg
    jmp exit

fileError:
    cmp ax, 01h
        je operationError
    cmp ax, 02h
        je fileNotFound
    cmp ax, 03h
        je pathNotFound
    cmp ax, 04h
        je tooManyFilesAreOpened
    cmp ax, 05h
        je accessIsDenied
    cmp ax, 0Ch
        je invalidAccessMode
    print unknownErrorMsg
    jmp exit

operationError:
    print operationErrorMsg
    jmp exit 
    
fileNotFound:
    print fileNotFoundMsg
    jmp exit
    
pathNotFound:
    print pathNotFoundMsg
    jmp exit
    
tooManyFilesAreOpened:
    print tooManyFilesAreOpenedMsg
    jmp exit 
    
accessIsDenied:
    print accessIsDeniedMsg
    jmp exit  
    
invalidAccessMode:
    print invalidAccessModeMsg
    jmp exit
    
exit:
    mov ax, 4C00h
    int 21h
    
end start