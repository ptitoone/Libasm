bits 64

extern __errno_location

global ft_read

section .text

ft_read:
	mov		rax, 0
	syscall
	cmp		rax, 0
	jl		err
	mov		BYTE [rsi+rax], 0
	ret

err:
	xor		rbx, rbx
	mov		rbx, rax
	NEG		rax
	mov		rdi, rax
	call	__errno_location wrt ..plt
	mov		[rax], rdi
	mov		rax, rbx
	ret
