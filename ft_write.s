bits 64

extern __errno_location

global ft_write

section .text

ft_write:
	mov		rax, 1
	syscall
	cmp		rax, 0
	jl		err
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
