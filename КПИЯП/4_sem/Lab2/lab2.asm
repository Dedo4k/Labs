org 100h
.model small
.stack 100h

.data
    buf equ 20
    strb db buf
    strl db 0  
    str db buf+1 dup('$')
    
    msg1 db "Enter the string: $"
    msg2 db "String after sorting: $"
    msg3 db "Swap",10,13,'$'
    msg4 db "Sort",10,13,'$'
    newline db 10,13,"$"
    
.code
start:
     mov ax, @data
     mov ds, ax
     
     lea dx,msg1
     call outStr;Enter the string
               
     lea dx,strb
     call inStr;Input string
     
     lea dx,newline
     call outStr;NewLine
     
     lea si,str
     dec si     
     xor cx,cx
     
sort:     
     inc si
     cmp si,'$'
     je exit
     
     mov al,[si]
     mov bl,[si+1]
     
     cmp bl,13
     je next
     
     cmp al,bl
     jnl swap
     call sort
     ret
     
swap:
     mov [si],bl
     mov [si+1],al
     call sort
               
     call exit

next:
     inc cx
     lea si,str
     dec si
     cmp cl,[strl]
     je exit
     call sort
outStr:
    push ax
    mov ah,9h
    int 21h
    pop ax
    ret

inStr:
    push ax
    mov ah,0ah
    int 21h
    pop ax
    ret
    
exit:
    lea dx,msg2
    call outStr;String after sorting
     
    lea dx,str
    call outStr;Output string
    
    mov ax,4c00h
    int 21h
    
end start                     