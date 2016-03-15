TITLE LAB1.1
.Model Tiny
.STACK 100h
.Data   
.Code
begin:
	mov al, 100d
	mov bl, 76d
	add al, bl
	mov bl, 20d
	sub al, bl
	mov bl, 65d
	mul bl
	xor ax, ax
	mov al, 100d
	mov bl, 66d
	add al, bl
	mov bl, -30d
	sub al, bl
	mov bl, 97d
	mul bl
	mov ax, 2047d
	mov bx, 255d
	add ax, bx
	mov bx, 1040d
	sub ax, bx
	mov bx, 8193d
	mul bx
	mov ah, 4Ch
	int 21h
END begin
