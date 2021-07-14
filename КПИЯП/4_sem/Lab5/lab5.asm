org 100h  

.data
    filename        db 'file.txt',0
    filepname       db "file.txt$"
    fileOpenMsg     db "File was opened$"
    fileOpenError   db "File was not opened$"
    fileCloseMsg    db "File was closed$"
    finalMsg        db "Number of empty strings: $" 
    newline         db 10,13,'$'
    line            db "********************$"
    buff            db 2 dup('$')
    hasNewLine      db 0
    hasCharInRow    db 0
    counter         db 0
    linux           db 0
        
printStr macro str
    lea dx,str
    mov ah,9
    int 21h
endm    

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
    
.code
main:
    mov ax,3D00h
    lea dx,filename
    int 21h
    jc openError
    mov bx,ax
    mov di,01
    
    printStr fileOpenMsg
    printStr newline
    printStr newline
    printStr filepname
    printStr newline
    printStr line
    printStr newline
    
read:    
    mov ah,3Fh
    mov cx,1             
    lea dx,buff
    int 21h
    jc closeFile
    mov cx,ax
    jcxz closeFile
    
    cmp [buff],10
    je newl
    cmp [buff],13
    je cret
    cmp [buff],'$'
    je dollar
    
    mov hasCharInRow,1
    
print:    
    mov ah,40h              
    xchg bx,di
    int 21h
    xchg di,bx
    jc closeFile
    jmp read
    
closeFile:
    mov ah,3Eh
    int 21h
    
    printStr newline
    printStr line
    printStr newline
    printStr newline 
    printStr fileCloseMsg
    printStr newline
    jmp result
        
newl:
    mov linux,1 
    mov hasNewLine,1
    jmp print
    
cret:
    cmp hasCharInRow,1
    je hasChar
    cmp linux,0;убрать линуксго
    je linuxgo    
    cmp hasNewLine,1
    jne read  
    
linuxgo:    
    mov hasNewLine,0
    mov hasCharInRow,0
    inc counter
    jmp read    

dollar:
    cmp hasCharInRow,1
        je result
    inc counter
    jmp result    

hasChar:
    mov hasCharInRow,0
    jmp print
    
openError:
    printStr fileOpenMsg
    jmp exit

result: 
    printStr newline
    printStr finalMsg
    xor ax,ax
    mov al,counter
    call OutInt    
    jmp exit
    
exit:
    mov ax,4C00h
    int 21h
    
end main    