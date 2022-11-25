bits 64

section .text

global	ft_strcmp

ft_strcmp:
	push	rbx
	xor		rax, rax
	xor		rbx, rbx

compare:
	mov		al, BYTE [rdi]
	mov		bl, BYTE [rsi]
	cmp		al, bl
	jne		return
	cmp		BYTE [rdi], 0
	je		return
	cmp		BYTE [rsi], 0
	je		return
	inc		rdi
	inc		rsi
	jmp		compare

return:
	sub		rax, rbx
	pop		rbx
	ret

