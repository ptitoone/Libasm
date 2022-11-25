bits 64

section	.text
global ft_list_size

ft_list_size:
	xor		rax, rax
	mov		rcx, rdi	
	cmp		rcx, 0x0
	je		return
	inc		rax

loop:
	mov		rcx, [rcx + 8]
	cmp		rcx, 0x0
	je		return
	inc 	rax
	jmp		loop

return:
	ret

