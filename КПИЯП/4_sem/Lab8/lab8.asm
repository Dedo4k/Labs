.model tiny 
.code
.386
org 100h
start:
    jmp handlerInstall
    flagKill db 0
    flagSave db 0
    oldIRQ0 dd ?
    oldIRQ1 dd ?
     
    msgIntReturn db "Interrupts has been renewed", 0Dh,0Ah
    msgIntReturnSize equ 29
    msgSaved db "Screen was saved", 0Dh,0Ah
    msgSavedSize equ 18
    msgErrSave db "Error while saving screen", 0Dh,0Ah
    msgErrSaveSize equ 27
    flag db "flag"
    videoStart equ 0B800h
    screenEnd equ 0FA0h

    destFileName db "F000.txt", 0
    destFileCounter dw 0
    destFile dw 0

    wordSize dw 4
    videoPtr dw 0
    byteBuf db ?
    flagWrited db 0
    getWord db 126 dup('$')

    newIRQ0 proc far
        pusha
        push ds
        push es
        
        mov ax, cs
        mov ds, ax

        mov flagWrited,0 
        cmp flagKill,1
        jne keepIRQ

        mov ah, 25h  ;óñòàíàâëèâàåì àäðåñ îáðàáîò÷èêà
        mov al, 08h    
        mov dx, word ptr cs:oldIRQ0      ;ñìåùåíèå îáðàáîò÷èêà
        mov ds, word ptr cs:oldIRQ0 + 2  ;ñåãìåíò îáðàáîò÷èêà
        int 21h
        mov ah, 25h
        mov al, 09h  ;óñòàíàâëèâàåì àäðåñ îáðàáîò÷èêà  
        mov dx, word ptr cs:oldIRQ1
        mov ds, word ptr cs:oldIRQ1 + 2
        int 21h

        mov ax, cs
        mov es, ax
        mov ah, 03h
        mov bh, 0
        int 10h
        
        mov ah, 13h
        mov al, 1
        mov bh, 0
        mov bl, 07h
        mov cx, msgIntReturnSize
        lea bp, msgIntReturn
        int 10h
       
        jmp oldIRQ0Mark
    keepIRQ:
        mov ax, videoStart
        mov es, ax
        mov videoPtr, 0
        
    loopFindWord:
        mov di, videoPtr
        lea si, getWord
    loopCheckWord:
        mov bl, es:di
        cmp bl, [si]
        jne nextSym
        add di, 2
        mov bx, videoPtr
        add bx, wordSize
        add bx, wordSize
        cmp di, bx
        je foundIt
qqq:        
        inc si
        jmp loopCheckWord

    foundIt:
        
        mov bl,es:di
        cmp bl,' '
            jne qqq
            
        sub di,wordSize
        sub di,wordSize
        sub di,2
        mov bl,es:di
        cmp bl,' '
            jne nextSym
            
        cmp flagSave, 1
        jne noHide
        call saveWord
        mov flagWrited,1
        mov cx, wordSize
        mov di, videoPtr

    noHide:        
        mov ax, wordSize
        add videoPtr, ax
        add videoPtr, ax
        jmp loopFindWordEnd      
    nextSym:                   ;èùåì ñëåäóþùåå ñîâïàäåíèå
        add videoPtr, 2
    loopFindWordEnd:
        cmp videoPtr, screenEnd
        jb loopFindWord

    oldIRQ0Mark:
        mov flagSave, 0
        cmp flagWrited,1
        jne oldIRQ0End
        mov ax, cs
        mov es, ax
        mov ah, 03h
        mov bh, 0
        int 10h
        
        mov ah, 13h
        mov al, 1
        mov bh, 0
        mov bl, 07h
        mov cx, msgSavedSize           ;âûâîäèì ñîîáùåíèå î çàâåðøåíèè ïîèñêà
        lea bp, msgSaved
        int 10h
    oldIRQ0End: 
        pushf
        call cs:dword ptr oldIRQ0      ;âîçâðàùàåì íàçàä ñòàðûå îáðàáîò÷èêè ïðåðûâàíèÿ
        pop es
        pop ds
        popa 
        iret 
    newIRQ0 endp
    
    newIRQ1 proc far
        pusha
        pushf
        call cs:dword ptr oldIRQ1
        mov ah, 01h                ;ïðîâåðêà íàæàòèÿ êëàâèø
        int 16h
        mov dh, ah
        jz newIRQ1end
        mov ah, 02h
        int 16h
        and al, 4
        cmp al, 0
        jne checkS
        jmp newIRQ1end
    checkS:        
        cmp dh, 2Eh
        jne checkQ
        mov cs:flagSave, 1
        mov ah, 00h
        int 16h
        jmp newIRQ1end
    checkQ:
        cmp dh, 2Ch
        jne newIRQ1end
        mov cs:flagKill, 1
        mov ah, 00h
        int 16h
    newIRQ1end:
        popa 
        iret 
    newIRQ1 endp

    saveWord proc
        pusha
        mov ah, 34h
        int 21h
        cli
        
        mov al, es:bx   ;çàãðóæàåì âèäåîïàìÿòü ñî ñëîâîì
        dec bx
        mov ah, es:bx
        cmp al, 0
        jne endPrintSCR
        cmp ah, 0
        jne endPrintSCR
        
        mov ax, videoStart ;íà÷àëî ïàìÿòè
        mov es, ax
        
        mov destFileCounter, 0
    openFindLoop:
        mov ax, destFileCounter
        mov dl, 100
        div dl
        add al, '0'
        mov destFileName + 1, al
        mov al, ah
        xor ah, ah
        mov dl, 10
        div dl
        add al, '0'
        add ah, '0'
        mov destFileName + 2, al   
        mov destFileName + 3, ah
        lea  dx, destFileName        ;ôîðìèðóåì íàçâàíèå ôàéëà
        xor cx, cx
        mov ah, 5Bh                  ;ñîçäà¸ì íîâûé ôàéë
        int 21h
        jnc nameFound                ;åñëè ôàéë ñîçäàí óñïåøíî
        inc destFileCounter
        cmp ax, 50h                  ;åñëè òàêîé ôàéë ñóùåñòâóåò
        je openFindLoop
        jmp endPrintSCR

    nameFound:
        mov destFile, ax             ;çàïèñûâàåì èäåíòèôèêàòîð ôàéëà
        mov ax, videoPtr
        mov bl, 80
        div bl
        xor ah, ah
        inc al
        mul bl
        mov di, ax
        cmp di, 160  
        jb less1
        sub di, 240
        mov cx, 240
        jmp loopWriteSaved
    less1:
        cmp di, 80
        jb less2    
        sub di, 80
        mov cx, 160
    less2:
        mov cx, 160
        
    loopWriteSaved:
        mov bx, destFile
        mov ah, 40h
        push cx
        mov cl, es:di
        mov byteBuf, cl
        lea dx,  byteBuf
        mov cx, 1
        int 21h   
        pop cx 
        
        add di, 2
        cmp di, 4000
        jae loopWriteSavedEnd
        cmp cx, 161
        jne cmp81 

        mov bx, destFile
        mov ah, 40h
        push cx
        lea dx,  endl
        mov cx, 1
        int 21h
        pop cx   
cmp81:
        cmp cx, 81
        je NLWrite
        jmp woNL
        
    NLWrite:
        mov bx, destFile
        mov ah, 40h
        push cx
        mov byteBuf, 10
        mov dx, offset  byteBuf
        mov cx, 1
        int 21h   
        pop cx
    woNL:
        loop loopWriteSaved
        
    loopWriteSavedEnd:             ;çàêðûâàåì ôàéë
        mov bx, destFile
        xor ax,ax
        mov ah,3eh
        int 21h
        jb endPrintSCR
        mov dx,1
    endPrintSCR:
        sti
        popa
        ret
    saveWord endp

handlerInstall:
        mov si, 80h
        lea di, getWord     ;äîñòà¸ì èç cmd èñêîìîå ñëîâî
        lodsb 
    loopSkip:
        lodsb
        cmp al, ' '
        je loopSkip      ;ïðîïóñêàåì ïðîáåëû
        cmp al, 0dh
        je endErrMark    ;âûõîä åñëè êîíåö ñòðîêè
        mov es:di, al    ;çàïèñûâàåì ñèìâîë â ñëîâî
        inc di           
    loopCL:
        lodsb
        cmp al, ' '
        je endOneArg
        cmp al, 0dh
        je endOneArg
        mov es:di, al    ;çàïèñûâàåì îñòàëüíûå ñèìâîëû
        inc di
        jmp loopCL
    endOneArg:
        ;mov [di],' ' 
        ;inc di
        sub di, offset getWord    ;èç êîíöà ñëîâà îòíèìàåì íà÷àëî
        mov wordSize, di       ;çàïèñûâàåì äëèíó ñëîâà
        
        mov ah, 35h            ;ïîëó÷àåì àäðåñ îáðàáîò÷èêà
        mov al, 08h            ;íîìåð âåêòîðà îáðàáîò÷èêà òàéìåðà
        int 21h
        mov word ptr oldIRQ0, bx     ;ñìåùåíèå îáðàáîò÷èêà
        mov word ptr oldIRQ0 + 2, es ;ñåãìåíò îáðàáîò÷èêà

        lea di,   flag      
        lea si,   flag
        mov cx, 4
        repe cmpsb              ;ïðîâåðÿåì 
        je loaded
        mov ah, 25h             ;óñòàíàâëèâàåì àäðåñ îáðàáîò÷èêà
        mov al, 08h             ;òàéìåð
        mov dx, offset newIRQ0  ;ñìåùåíèå îáðàáîò÷èêà â ñåãìåíòå
        int 21h
        mov ah, 35h             ;ïîëó÷àåì àäðåñ îáðàáîò÷èêà
        mov al, 09h             ;íîìåð âåêòîðà ïðåðûâàíèÿ îò êëàâèàòóðû
        int 21h
        mov word ptr oldIRQ1, bx  ;ñìåùåíèå îáðàáîò÷èêà
        mov word ptr oldIRQ1 + 2, es  ;ñåãìåíò îáðàáîò÷èêà  
        mov ah, 25h
        mov al, 09h
        mov dx, offset newIRQ1   ;ñìåùåíèå îáðàáîò÷èêà â ñåãìåíòå
        int 21h
        mov ah, 09h
        mov dx, offset msgControls
        int 21h   
        mov ax, 3100h                                ;îñòàâëÿåì ïðîãðàììó ðåçèäåíòíîé
        mov dx, (handlerInstall-start + 10Fh) / 16   ;ðàçìåð ðåçèäåíòíîé ïðîãðàììû â ïàðàãðàôà÷
        int 21h

    endErrMark:
        jmp handlerInstallEnd
        loaded:
        mov ah, 09h
        mov dx, offset msgAlready
        int 21h  
    handlerInstallEnd:
        .exit                  
msgErrArgs db "One argument required. Proper arguments example:command requiredWord", '$'
msgControls db "Ctrl+C - find word, Ctrl+Z - return interrupts",0Dh,0Ah,'$'
msgAlready db "Programm was already launched ", '$'
endl db 10, 13, '$'          
end start
