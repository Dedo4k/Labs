.model small
.stack 100h

new_line macro ;перевод курсора
    mov ah,2
    mov dl,0dh
    int 21h
    mov dl,0ah
    int 21h
endm

clrscr macro
    mov ah,6
    xor al,al
    xor cx,cx
    mov dx,184Fh
    mov bh,7
    int 10h
endm

movcursor_r macro
    mov ah,3
    xor bh,bh
    int 10h
    
    mov ah,2 
    inc dl
    int 10h
endm

movcursor_l macro
    mov ah,3
    xor bh,bh
    int 10h
    
    mov ah,2
    dec dl
    int 10h
endm

setcursor macro r,c
    mov ah,2
    xor bh,bh
    mov dh,r
    mov DL,c
    int 10h
endm    

nums macro lp1, lp2, lp3, lp4, cnt, outs, val
    mov cx,4
    mov dl,val
    cmp dl,0
    je lp4 
    
    mov ax,1
    mov cx,0
    mov cl,dl
    sub cl,'A'
    add cl,1
    sal ax,cl
    
    mov len,0
    mov bl,10
    
lp1:
    div bl
    
    mov cx,0
    mov cl,ah
    add cl,48
    push cx
    add len,1
    mov ah,0
    cmp al,0
    jne lp1
    
    mov al,4
    sub al,len
    cmp al,0
    je cnt
    
    mov cx,0
    mov cl,al
    mov ah,2
    mov dl,' '
    
lp2:
    int 21h
    loop lp2
    
cnt:
lp3:
    sub len,1
    pop ax
    mov ah,9
    xor bh,bh
    mov cx,1
    mov bl,34h
    int 10h
    movcursor_r
    cmp len,0
    jne lp3
    
    mov dl,' '
    int 21h
    jmp outs
    
    mov cx,4
    
lp4:
    mov ah,2
    mov dl,' '
    int 21h
    loop lp4
    int 21h
outs:
endm

macro c_score
    mov ax,score
    mov dx,0
    mov bx,10
    
    mov len,0
    
L1:
    mov dx,0
    div bx
    push dx
    add len,1
    cmp ax,0
    jne L1
    
    setcursor 23,25
    mov ah,9
    lea dx,str7 ; строка score
    int 21h
    
L2:
    pop dx
    add dl,48
    sub len,1
    mov ah,2
    int 21h
    cmp len,0
    jne L2
endm  

macro underline
    mov len,10
UND:
    sub len,1
    mov ah,2
    mov dl,'_'
    int 21h
    cmp len,0
    jne UND
endm

macro ununderline unund
    mov len,10
unund:
    sub len,1
    mov ah,2
    mov dl,' '
    int 21h
    cmp len,0
    jne unund
endm

macro cool g1,g2,g3,e1,str
    lea si,str
g1:
    mov dl,[si]
    cmp dl,'$'
    je e1
    mov tmp1,dl
    mov tmp2,dl
    mov len,12
    mov dl,tmp1
    
g2:
    dec len
    inc tmp1
    mov al,tmp1
    mov cx,1
    mov ah,9h
    int 10h
    mov cx,30000
    
g3:
    loop g3
    cmp len,0
    jne g2
    
    mov al,tmp2
    mov cx,1
    mov ah,9h
    int 10h
    movcursor_r
    inc si
    jmp g1

e1:
endm    

.data
arr db 17 dup(0)
beg db 0
score dw 0
tsc dw 1
calc db 0
userin db ?
csr db 0    ;cursor row position
csc db 0    ;cursor column position
len db 0
tmp dw ?
tmp1 db ?
tmp2 db ?
tmp3 db ?
flag db 'A'
flag2 db 0
done db 0
choise db 0
mode db 0 
str1 db "YOU LOSE...$"
str2 db "YOU WIN!$"
str3 db "L = LEFT, R = RIGHT, U = UP, D = DOWN$"
str4 db "2048 GAME$"                           
str5 db "GAME ENDED... PRESS Esc$"
str6 db "PRESS Esc FOR MENU$"
str7 db "SCORE: $"
str8 db "<< 2048 >>$"
str9 db "PLAY$"
str10 db "KID MODE$"
str11 db "EXIT$"
strz db 2 dup("$")

.code
main proc
    mov ax,@data
    mov ds,ax
    
setwindow:
    mov ah,0
    mov al,1
    int 10h
    
initialize:
    mov score,0
    mov ah,9
    mov al,' '
    xor bh,bh
    mov bl,10
    mov cx,200
    int 10h   
    
    setcursor 4,14
    cool pp1,pp2,pp3,pp4,str8
    setcursor 8,14
    
    mov ah,9
    mov al,' '
    xor bh,bh
    mov bl,15
    mov cx,251
    int 10h
    
    mov ah,9
    lea dx,str9
    int 21h
    
    setcursor 12,14
    mov ah,9
    lea dx,str11
    int 21h
    
    mov csr,9
    setcursor csr,14
    mov choise,1
    
menu:
    setcursor csr,14
    underline
    
    mov ah,0
    int 16h
    cmp ah,0
    int 16h
    
    cmp ah,50h
    je lower
    cmp ah,48h
    je upper
    cmp ah,1ch
    je background
    jmp menu
    
lower:        
    cmp csr,13
    je menu
    setcursor csr,14
    ununderline t1
    add csr,4  
    add choise,1
    setcursor csr,14
    jmp menu

upper:
    cmp csr,9
    je menu
    setcursor csr,14
    ununderline t2
    sub csr,4
    sub choise,1
    setcursor csr,14
    jmp menu

background:
    cmp choise,2
    je exit    
    
    mov ah,6
    mov cx,0
    mov dh,24
    mov dl,39
    mov bh,30h
    mov al,0
    int 10h
    
    lea si,arr
    mov cx,17
    
set_0:
    mov [si],0
    inc si
    loop set_0
    
begin:
            
    mov ah,2ch
    int 21h
    
randomize:
    mov ax,0
    mov al,dl
    mov dl,16
    div dl
    mov beg,ah
    
    shr ah,1
    jc four
    
    mov flag,'A'
    jmp searching
    
four:
    mov flag,'B'
    
searching:
    lea si,arr
    mov ax,0
    mov al,beg
    add ax,1
    add si,ax
    
    mov cx,16
    
round:
    cmp [si],0
    je placeval
    
    cmp si,16
    jne noreset

reset:
    lea si,arr
    inc si
    jmp last
    
noreset:
    inc si
    
last:
    loop round
    jmp next
    
placeval:
    mov dl,flag
    mov [si],dl
    jmp next
    
next:
                            
    
exit:
    clrscr    
    mov ah,4ch
    int 21h
    main endp

END main