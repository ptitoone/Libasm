bits 64

section	.text

global	ft_strlen

ft_strlen:
	xor		rax, rax

check:
	cmp		BYTE [rdi], 0
	je		return
	jmp		increment

increment:
	inc		rax
	inc		rdi
	jmp		check

return:
	ret
