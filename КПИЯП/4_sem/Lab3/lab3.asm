.model medium
 
.stack  200h
 
.data
        ;ƒанные
        msgPressAnyKey  db      0Dh, 0Ah, 'Press any key to exit...', '$'
        CrLf            db      0Dh, 0Ah, '$'
        asPrompt        db      'Enter a array:', 0Dh, 0Ah, '$'
        asShowArray     db      0Dh, 0Ah, 'Entered a array:', 0Dh, 0Ah, '$'
        asAverage       db      0Dh, 0Ah, 'Average:', 0Dh, 0Ah, '$'
        press1          db      0Dh, 0Ah, 'Press [q] to get [-n]',0Dh, 0Ah, '$'
        press2          db      0Dh, 0Ah, 'Press [w] to get [sqrt(n)]',0Dh, 0Ah, '$'
        press3          db      0Dh, 0Ah, 'Press [e] to get [abs(n)]',0Dh, 0Ah, '$'
        press4          db      0Dh, 0Ah, 'Press [r] to get [1/n]',0Dh, 0Ah, '$'
        iAverage        dw      ?
        N               dw      ?
        Array           dw      100 dup(?)
 
.code

printStr:
        mov ah,9
        int 21h
        ret

square proc
        pusha
        lea dx,CrLf
        call printStr
        mov cx,[N]
        lea si,[Array]
        xor bx,bx
        xor di,di
        
        for:
            lodsw
            cwd
            mul ax
            lea dx,ax
            call ShowInt16
            pusha
            mov ah,2
            xor dx,dx
            mov dl,32
            int 21h
            popa
        loop for
        popa
        call exit
        ret   
square endp

invers proc
    pusha
        lea dx,CrLf
        call printStr
        mov cx,[N]
        lea si,[Array]
        xor bx,bx
        xor di,di
        
        for2:
            lodsw
            cwd
            neg ax
            lea dx,ax
            call ShowInt16
            pusha
            mov ah,2
            xor dx,dx
            mov dl,32
            int 21h
            popa 
        loop for2
     popa
     call exit
     ret
invers endp    

abs proc
    pusha
    lea dx,CrLf
        call printStr
        mov cx,[N]
        lea si,[Array]
        xor bx,bx
        xor di,di
        
        for3:
            lodsw
            cwd
            getAbs:
            neg ax
            js getAbs
            lea dx,ax
            call ShowInt16
            pusha
            mov ah,2
            xor dx,dx
            mov dl,32
            int 21h
            popa 
        loop for3
    popa
    call exit
    ret
abs endp    

obratn proc
    pusha
        lea dx,CrLf
        call printStr
        mov cx,[N]
        lea si,[Array]
        xor bx,bx
        xor di,di
        
        for4:
            lodsw              ;ax=b
            cwd
            
            mov bx,1           ;1 шаг
                               ;bx=1
            xchg bx,ax         ;ax=1 bx=b
            div bx             ;ax=ax/bx=1/b=целое    dx=остаток
            push dx            ;сохран€ем остаток
            push bx            ;сохран€ем делитель
            lea dx,ax
            call ShowInt16     ;получить целую часть от делени€
            
            pusha              ;вывести точку
            mov ah,2
            mov dl,'.'
            int 21h
            popa  
            push cx
            mov cx,3
            afterDot:          ;вывести 3 числа после зап€той
                pop dx         ;возвращаем остаток в dx
                mov ax,dx      
                mov bx,10
                mul bx         ;умножаем его на 10
                pop bx         ;возвращаем делитель в bx
                div bx         
                push bx        ;сохран€ем делитель
                push dx        ;сохран€ем остаток
                lea dx,ax
                call ShowInt16
            loop afterDot
            pop cx
            pusha
            mov ah,2
            xor dx,dx
            mov dl,32
            int 21h
            popa 
        loop for4
    popa
    call exit
    ret
obratn endp
          
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
         
manu:
        lea dx,press1
        call printStr
        lea dx,press2
        call printStr
        lea dx,press3
        call printStr
        lea dx,press4
        call printSTr
        
        mov ah,1
        int 21h
        cmp al,'q'
        je invers
        cmp al,'w'
        je square
        cmp al,'e'
        je abs
        cmp al,'r'
        je obratn
        ;mov dx,di
        ;mov ax,bx
        ;idiv [N]
        ;mov [iAverage],ax
        ;вывод результатов
        ;mov ah,09h
        ;lea dx,[asAverage]
        ;int 21h
        ;mov ax,[iAverage]
        ;call ShowInt16
        ;ожидание нажати€ любой клавиши
        mov ah,09h
        lea dx,[msgPressAnyKey]
        int 21h
        mov ah,00h
        int 16h
 
        ;завершение программы
exit:        
        mov ax,4C00h
        int 21h
main    endp
 
end     main 