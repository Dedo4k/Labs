.model medium
 
.stack  200h
 
.data
        ;ƒанные
        msgPressAnyKey  db      0Dh, 0Ah, 'Press any key to exit...', '$'
        CrLf            db      0Dh, 0Ah, '$'
        asPrompt        db      'Enter an array:', 0Dh, 0Ah, '$'
        asShowArray     db      0Dh, 0Ah, 'Entered array:', 0Dh, 0Ah, '$'
        press1          db      0Dh, 0Ah, 'Press [q] to get [-n]',0Dh, 0Ah, '$'
        press2          db      0Dh, 0Ah, 'Press [w] to get [sqrt(n)]',0Dh, 0Ah, '$'
        press3          db      0Dh, 0Ah, 'Press [e] to get [abs(n)]',0Dh, 0Ah, '$'
        press4          db      0Dh, 0Ah, 'Press [r] to get [1/n]',0Dh, 0Ah, '$'
        press5          db      0Dh, 0Ah, 'Press [z] to exit',0Dh, 0Ah, '$'
        iAverage        dw      ?
        N               dw      ?
        Array           dw      100 dup(?)

.code

ShowInt16 proc
        pusha
        mov bx,10
        xor cx,cx      ;символов в модуле числа
        or ax,ax
        jns @@div
            neg ax
            push ax
            mov ah,02h
            mov dl,'-'
            int 21h
            pop ax
            
        @@div:
            xor dx,dx
            div bx
            push dx
            inc cx      ;количество цифр в числе
            or ax,ax
            
        jnz @@div
        mov ah,02h
        
        @@store:
            pop dx
            add dl,'0'
            int 21h
            
        loop @@store
        popa
        ret
ShowInt16 endp
 
;¬ывод массива слов (word)
;cx - количество выводимых элементов
;ds:dx - адрес массива слов
ShowArray proc
        pusha
 
        jcxz @@saExit        ;если массив пустой - завершить
 
        mov si,1       ;индекс элемента массива
        mov di,dx      ;адрес текущего элемента массива
        
        @@saForI:
            mov ax,[di]
            call ShowInt16
            mov ah,02h
            mov dl,' '
            int 21h
            ;переход к следующему элементу
            inc si
            add di,2
            
        loop @@saForI
        
@@saExit:
        popa
        ret
        
ShowArray endp

printStr proc
    pusha
        mov ah,9
        int 21h
    popa
    ret
printStr endp

invers proc
    pusha
        lea dx,CrLf         ;newline
        call printStr
        mov cx,[N]
        lea si,[Array]
        xor bx,bx
        xor di,di
        
        for1:
            lodsw
            cwd
            
            neg ax           ;sing changing 
            lea dx,ax
            call ShowInt16   ;output number
            
            pusha
                mov ah,2         ;adding spaces
                xor dx,dx
                mov dl,32
                int 21h
            popa
             
        loop for1
        
    popa
        lea dx,CrLf         ;newline
        call printStr
    call input
    ret    
invers endp

sqrt proc
    pusha
        lea dx,CrLf         ;newline
        call printStr
        mov cx,[N]
        lea si,[Array]
        xor bx,bx
        xor di,di
        
        for2:
            lodsw
            cwd
            
            mul ax           ;sqrt counting
            lea dx,ax
            call ShowInt16   ;output number
            
            pusha            ;adding spaces
                mov ah,2
                xor dx,dx
                mov dl,32
                int 21h
            popa
            
        loop for2
        
    popa
        lea dx,CrLf         ;newline
        call printStr
    call input
    ret    
sqrt endp

abs proc
    pusha
        lea dx,CrLf         ;newline
        call printStr
        mov cx,[N]
        lea si,[Array]
        xor bx,bx
        xor di,di
        
        for3:
            lodsw
            cwd
            
            getAbs:         ;abs counting
            neg ax
            js getAbs
            lea dx,ax       ;output number
            call ShowInt16
            
            pusha
                mov ah,2
                xor dx,dx
                mov dl,32
                int 21h
            popa
             
        loop for3
            
    popa 
        lea dx,CrLf         ;newline
        call printStr
    call input
    ret
abs endp

invert proc
    pusha
        lea dx,CrLf         ;newline
        call printStr
        mov cx,[N]
        lea si,[Array]
        xor bx,bx
        xor di,di
        
        for4:
            lodsw            ;ax=n
            cwd
            
            cmp ax,0
            jns pos
            min:
                pusha
                mov ah,2
                mov dl,45
                int 21h
                popa
                neg ax
            pos:   
            mov bx,1         ;bx=1
            
            xchg ax,bx       ;swap(ax,bx)
            cmp bx,0
            je exit
            cwd

            idiv bx           ;ax=ax/bx=1/n ax-цела€ dx-остаток
               
            push ax          ;сохран€ем остаток
            push bx          ;сохран€ем делимое
            push dx          ;сохран€ем делитель                   
            
            lea dx,ax        ;вывод целой части
            call ShowInt16   
            
            mov ah,2         ;вывод точки
            mov dl,'.'
            int 21h
            
            pop dx
            pop bx
            pop ax 
            
            push cx          ;сохран€ем счЄтчие массива for4
            
            push ax
            push bx
            push dx
            
            mov cx,3         ;количество знаков после зап€той
            
            for5:
                pop dx       ;возвращаем остаток    1
                pop bx       ;возвращаем делимое    0
                pop ax       ;возвращаем делитель   3
                                
                mov ax,bx    ;                                bx=ax
                push bx
                xchg ax,dx   ;увеличиваем остаток в 10 раз    dx=3 ax=1            
                mov bx,10    ;                                bx=10
                mul bx
                pop bx
                
                cmp bx,0
                je next1
                
                idiv bx
                
                push ax
                push bx
                push dx
                
                lea dx,ax
                call ShowInt16
            loop for5
            
            next1:
                pop dx
                pop bx
                pop ax
                pop cx
                pusha 
                    mov ah,2
                    mov dl,32
                    int 21h
                popa
        loop for4
            
    popa
        lea dx,CrLf         ;newline
        call printStr
    call input
    ret
invert endp

main    proc
        mov ax,@data
        mov ds,ax
 
        ;программа
        mov ah,09h
        lea dx,[asPrompt]
        int 21h
        ;ввод массива
        lea di,[Array]                 ;
        xor cx,cx                      ; n=0
        xor bx,bx                      ; x=0
        xor si,si                      ; sign=0
        
        do:                            ; do{
            mov ah,01h                 ;    al=getch()
            int 21h
            cmp al,'-'                 ;    if(al=='-')
            jne @@IsDigit
                mov si, -1             ;      sign=-1;
                jmp do
                
        @@IsDigit:
                cmp al,'0'             ;    if(isdigit(al))
                jb  store
                cmp al,'9'
                ja store
                    push ax            ;      x=x*10+al-'0'
                    mov ax,10
                    mul bx
                    pop bx
                    sub bl,'0'
                    xor bh,bh
                    add  bx,ax
                    jmp next
                    
                store:                 ;    else{
                    xor bx,si          ;      if(sign==-1)
                    sub bx,si          ;      { x= -x;
                    xor si,si          ;        sign=0};
                    mov [di],bx        ;      a[n]=x
                    add di,2
                    inc cx             ;      n=n+1
                    xor bx,bx          ;      x=0
                    cmp al,0Dh         ;      if(al=enter)
                    je break           ;        break;
                                       ;    }
        next:
        jmp do
                                       ;  }while(1)
break:
        mov [N],cx
 
        mov ah,09h
        lea dx,[asShowArray]
        int 21h
        mov cx,[N]
        lea dx,[Array]
        call ShowArray
        
menu:
        lea dx,press1       ;menu messages
        call printStr
        lea dx,press2
        call printStr
        lea dx,press3
        call printStr
        lea dx,press4
        call printStr
        lea dx,press5
        call printStr
input:        
        mov ah,1            ;выбор пункта меню
        int 21h
        
        cmp al,'q'          ;инверси€
        je invers
        
        cmp al,'w'          ;квадрат
        je sqrt
        
        cmp al,'e'          ;модуль
        je abs
        
        cmp al,'r'
        je invert
        
        cmp al,'z'
        je exit
        lea dx,CrLf         ;newline
        call printStr
        jmp input
exit:
        mov ax,4C00h
        int 21h                
main endp
end main