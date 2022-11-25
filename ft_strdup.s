bits 64

extern malloc

global ft_strdup

section .text

ft_strdup:
	push	rbp
	mov		rbp, rsp
	push	rbx
	xor		rbx, rbx			; set index to 0
	xor		rax, rax
	push	rdi					; save source string address on stack

get_len:
	cmp		BYTE [rdi+rbx], 0	; check if null byte has been reached
	je		alloc				
	inc		rbx					; index + 1
	jmp		get_len

alloc:
	add		rbx, 1				; add 1 to index for len
	mov		rdi, rbx			; set len/size in bytes in malloc arg registery
	call	malloc	         	; allocated address returned from malloc (rax)
	jmp		dupl

dupl:
	pop		rsi					; pop source string address in rsi (source for movsb)
	mov		rdi, rax			; copy allocated address in rdi (destination for movsb) 
	mov		rcx, rbx			; copy len in rcx (counter for movsb)
	rep		movsb				; copy byte from rsi++ to dst++ and rcx-- untill rcx > 0

return:
	pop		rbx
	mov		rsp, rbp
	pop		rbp
	ret

