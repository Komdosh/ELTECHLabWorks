.Model tiny
.Data
    greeting db "This programm print array with max elements of given two arrays", 0dh, 0ah, "$"
    textSizeF db "Please input size of first array from 1 to 9", 0dh, 0ah,"first array size = $"                                     
    textSizeS db "Please input size of second array from 1 to 9", 0dh, 0ah,"second array size = $"  
    textNum db "Please input numbers from 0 to 9", 0dh, 0ah,"$"
    textRes db "Result saved in RESARR$"
    equSym db " = $"
    endl db 0ah, 0dh, "$"    
    textFirstArr db "DSARR[$"
    textSecondArr db "ESARR[$"
    textResArr db "RESARR[$" 
    closeBracket db "]$"
    question db "Press any key for retry, 0 to exit", 0dh, 0ah, "$"
    pkey db "Press any key...$"
    firstArr dw 10 dup(0)      
    firstArrSize dw ?
    secondArr dw 10 dup(0) 
    secondArrSize dw ?
    resArrSize dw ? 
    resArr dw 10 dup(0)  
    temp dw ?
    
    buffer db 6 		;max num with 5 symbols
    blength db ? 
    bconteg:			;consistance of buf is over of prog
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
    lea dx, textSizeF  ;enter size of first arr msg
    mov ah, 09h
    int 21h
    
    call input         ;input size of first arr 
    mov firstArrSize, ax
    mov temp, ax
    
inpFirstArr:        
    call endlp
    lea dx, textFirstArr    ;DSARR[
    mov ah, 09h
    int 21h     
    mov ax, firstArrSize
    sub ax, temp
    call printAX            ;i for DSARR[i]
    mov dl, ']'
    mov ah, 02h
    int 21h
    mov dl, '=' 
    mov ah, 02h
    int 21h                  
    
    call input                  ;write in DSARR[i] arr num
    mov cx, ax   
    mov ax, firstArrSize
    sub ax, temp
    mov bx, 2h
    mul bx
    mov bx, ax 
    mov ds:[bx+firstArr], cx 
    dec temp     
    cmp temp, 0
    jnz  inpFirstArr    
    call endlp 

    lea dx, textSizeS  ;enter size of first arr msg
    mov ah, 09h
    int 21h
    
    call input         ;input size of second arr 
    mov secondArrSize, ax
    mov temp, ax
inpSecondArr:        
    call endlp
    lea dx, textSecondArr    ;ESARR[
    mov ah, 09h
    int 21h     
    mov ax, secondArrSize
    sub ax, temp
    call printAX             ;i for ESARR[i]
    mov dl, ']'
    mov ah, 02h
    int 21h
    mov dl, '=' 
    mov ah, 02h
    int 21h                    
    
    call input                  ;write in ESARR[i] arr num
    mov cx, ax   
    mov ax, secondArrSize
    sub ax, temp
    mov bx, 2h
    mul bx
    mov bx, ax 
    mov es:[bx+secondArr], cx  
    dec temp     
    cmp temp, 0
    jnz  inpSecondArr    
    call endlp 
    
       
;Main code
    mov cx, firstArrSize 
    cmp cx, secondArrSize
    jnb sizeOk
    mov cx, secondArrSize
sizeOk:
    mov resArrSize, cx         ;resArrSize=max(firstArrSize, secondArrSize)
    
    xor bx, bx                 ;bx = 0 
mainL:                         ;resARR[bx] = max(DSARR[bx], ESARR[bx])
    mov ax, ds:[firstArr+bx]   ;ax = DSARR[bx]
    cmp ax, es:[secondArr+bx]  ;if ax < ESARR[bx]
    jb mainElse
    mov es:[resArr+bx], ax      
    jmp mainEnd 
mainElse:
    mov ax, es:[secondArr+bx]
    mov es:[resArr+bx], ax 
mainEnd:        
    add bx, 2   
    loop mainL
;**********************   
    mov ax, resArrSize 
    mov temp, ax 
    lea dx, textRes      ;Result saved in RESARR
    mov ah, 09h
    int 21h 
printing:      
    call endlp
    lea dx, textResArr    ;RESARR[
    mov ah, 09h
    int 21h     
    mov ax, resArrSize
    sub ax, temp
    call printAX          ;i for RESARR[i]
    mov dl, ']'
    mov ah, 02h
    int 21h
    mov dl, '=' 
    mov ah, 02h
    int 21h                  
    
    mov cx, ax                ;print RESARR[i]
    mov ax, resArrSize
    sub ax, temp
    mov bx, 2h
    mul bx
    mov bx, ax 
    mov ax, es:[resArr+bx]
    call printAX  
    dec temp     
    cmp temp, 0
    jnz  printing    
    call endlp             
     
    lea dx, question     ;Enter any key for retry, 0 to exit
    mov ah, 09h
    int 21h
    mov ah, 01h
    int 21h
    cmp al, '0'
    jz stopLab
    call start
stopLab:
    call quit                                                 

proc setDisp   
 	xor dx,dx		;cursor's position
	mov ah,02h		;set at (0,0)
	int 10h    
	mov bl,00001010b	;colors green on black
	mov cx,25*80		;count of simbols on display	
	mov ax,0920h		;printing 25*80 spaces
	int 10h  
	ret
endp  

proc quit         
    mov ax, 4c00h ; exit to operating system.
    int 21h 
endp

proc endlp        ;press enter
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
nM:
	jmp endInp 
	
badInp:	
    jmp start			 
    
endInp:	    
    ret
endp

proc printAX 
    push cx
    push bx             
	mov bx,0ah			;divider
	xor cx,cx			;clear count    
	
divloop:
	xor dx,dx			;clear dx
	div bx				;divide on 10
	add dx,'0'		        ;make a symbol from num
	push dx			        ;save dx
	inc cx				
	test ax,ax			;if ax!=0
	jnz divloop			;continue to divide  
	
restore:
	;pop ax				 
	pop ax                          ;read from stack 
	mov dx, ax		
	mov ah,2			;print symbol from al
	int 21h				;
	loop restore          
	pop bx
	pop cx
	ret
endp

end start ; set entry point and stop the assembler.