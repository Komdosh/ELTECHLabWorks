.Model tiny
.Data
    greeting db "This programm do (A+B-D)xC", 0dh, 0ah, "$"
    help db "Please, input number from -9000 to 9000", 0dh, 0ah, "$"
    textA db "A = $"                                     
    textB db "B = $"
    textC db "C = $"
    textD db "D = $"
    textRes db "Result = $"
    endl db 0ah, 0dh, "$"
    pkey db "Press any key...$"  
    negative db 0
    arr dw 4 dup(?)
    
    buffer db 6 ;max num with 4 symbols
    blength db ? 
    bconteg:				  ;consistance of buf is over of prog
        hexstring equ bconteg  
.Stack 0100h

.Code
start:  
    mov ax, @data
    mov ds, ax
    mov es, ax  
    
    call setDisp
    
    lea dx, greeting   ;greeting message
    mov ah, 09h
    int 21h  
    lea dx, help       ;help message
    mov ah, 09h
    int 21h
    
    lea dx, textA      ;A=
    mov ah, 09h
    int 21h
    
    call input         ;input A
    mov arr, ax
    call endlp          
     
    lea dx, textB      ;B=
    mov ah, 09h
    int 21h
    
    call input         ;input B
    mov arr+2, ax
    call endlp
    
    lea dx, textC      ;C=
    mov ah, 09h
    int 21h
    
    call input         ;input C
    mov arr+4, ax
    call endlp          
     
    lea dx, textD      ;D=
    mov ah, 09h
    int 21h
    
    call input         ;input D
    mov arr+6, ax
    call endlp  
        
    mov ax, arr
    mov bx, arr+2
    add ax, bx         ;A+B
    mov bx, arr+6
    sub ax, bx         ;(A+B)-D
    mov bx, arr+4
    mul bx             ;(A+B-D)xC 
    jns printing
    mov negative, 1
    
    
printing:   
    push ax
    lea dx, textRes ;Result=
    mov ah, 09h
    int 21h    
    pop ax             
    call print         ;output result
    call endlp              
    
    call quit                                                 

proc setDisp   
 	xor dx,dx			;cursor's position
	mov ah,02h			;set at (0,0)
	int 10h    
	mov bl,00001010b	;colors green on black
	mov cx,25*80		;count of simbols on display	
	mov ax,0920h		;printing 25*80 spaces
	int 10h  
	ret
endp  

proc quit          
    lea dx, pkey
    mov ah, 9h
    int 21h        ; output string at ds:dx
    
    ; wait for any key....    
    mov ah, 1h
    int 21h
    
    mov ax, 4c00h ; exit to operating system.
    int 21h 
endp

proc endlp       ;press enter
    push dx    
    push ax
    lea dx, endl
    mov ah, 09h
    int 21h 
    pop ax  
    pop dx
    ret
endp     

proc input
	lea dx,buffer       ;buffer's address
	mov ah,0ah			;write in buffer	
	int 21h  
	
;from string to bin  

	xor di,di			;start of buffer
	xor ax,ax			;clear ax
	mov cl,blength
	xor ch,ch
	xor bx,bx
	mov si,cx			;buffer's length	
	mov cl,10			;multiplier      
	
    mov bl,byte ptr bconteg[di]
	cmp bl, '-'
	jnz toHex
	mov negative, 1
	inc di  

toHex:
	mov bl,byte ptr bconteg[di]
	sub bl,'0'		    	    ;num = num's code - 30h
	jb  badInp		    	    ;if symbol not a num
	cmp bl,9		    	    ;same
	ja  badInp		    	    ;try input again
	mul cx			    	    ;multiply on 10
	add ax,bx		    	    ;+new num to ax	
	inc di			      	    ;next symbol
	cmp di,si		    	    ;if di<blength + 1  	
	jb toHex                        
	cmp negative, 1             ;num is negative 
	jnz nM
	neg ax
	mov negative, 0
nM:
	jmp endInp 
	
badInp:	
    jmp start			 
    
endInp:	
    ret
endp

proc print              
    cmp negative, 1     ;if num<0
    jnz stPrint
    push ax
    mov dl, '-'
    mov ah, 02h
    int 21h
    pop ax
    neg ax
    
stPrint:
	mov bx,0ah			;divider
	xor cx,cx			;clear count    
	
divloop:
	xor dx,dx			;clear dx
	div bx				;divide on 10
	add dx,'0'		;make a symbol from num
	push dx			    ;save dx
	inc cx				
	test ax,ax			;if ax!=0
	jnz divloop			;continue to divide  
	
restore:
	;pop ax				;read from stack  
	pop ax
	mov dx, ax		;
	mov ah,2			;print symbol from al
	int 21h				;
	loop restore
	ret
endp

end start ; set entry point and stop the assembler.