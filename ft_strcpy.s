bits 64

section .text

global	ft_strcpy

ft_strcpy:
	xor		rax, rax 				; set to 0
	mov		rcx, rdi

cpy:
	mov		al, BYTE [rsi]
	mov		BYTE [rcx], al
	cmp		BYTE [rsi], 0
	je		return
	inc		rsi
	inc		rcx
	jmp		cpy

return:
	mov		rax, rdi				; copy dest adress in return register
	ret								; return dest adress
