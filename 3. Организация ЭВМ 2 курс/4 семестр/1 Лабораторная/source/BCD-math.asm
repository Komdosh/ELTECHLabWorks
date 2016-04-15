TITLE LAB1.2
.Model Tiny
.STACK 100h
.Data   
.Code
begin:
	mov al, 37h
	mov bl, 68h
	add al, bl
	daa
	mov ah, al
	mov al, 10h
	mov bl, 20h
	adc al, bl
	daa
	mov bh, al
	mov al, ah
	sub al, 96h
	das
	mov ah, al
	mov al, bh
	sbb al, 35h
	das
	mov bl, al
	mov al, ah
	mov ah, bl
	mov ah, 4ch
	int 21h
END begin
