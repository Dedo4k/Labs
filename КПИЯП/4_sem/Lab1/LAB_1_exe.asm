.model small
;.stack 100h

.data
    start_msg db "Enter some string:",0Dh,0Ah,'$'  
    output_msg db "You enter:$"
    new_line db 0Dh,0Ah,'$'
    buf label byte

.code
start:
    mov ah,09h
    lea dx,start_msg
    int 21h;output start_msg in cmd   
    
    mov dx, offset buf   
    mov ah, 0ah
    int 21h;input string in buf
    
    mov ah,09h
    lea dx, new_line
    int 21h;new line
    
    mov ah,09h
    lea dx, output_msg
    int 21h;output output_msg in cmd
    
    mov	di,	offset buf          ;buf address
    mov	bx,	0h        
    mov	bl,	[di+1]	            ;string length
    mov	byte ptr [di+bx+2], '$'	;address after string
    mov	dx,	offset buf
    add	dx,	2h
    mov	ah,	9h
    int	21h;output buf
    
generate_sound:;generating sound while any key will be pressed
    call speaker_on
    call delay
    call speaker_off
    call delay

    mov ah,1
    int 16h
    jz generate_sound
    mov ax,4C00h

                             
speaker_on:
    in al,61h
    or al,2
    out 61h,al
    ret

speaker_off:
    in al, 61h
    and al,11111100b
    out 61h,al
    ret

delay:
    mov cx,65535
    ret

_wait:
    loop _wait
    ret

end start
