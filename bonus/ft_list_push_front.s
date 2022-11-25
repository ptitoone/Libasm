bits 64

extern malloc

section	.text
global	ft_list_push_front

ft_list_push_front:
	push	rsp						; Save stack
	push	rdi						; Save t_list **
	push	rsi						; Save void *data

call_malloc:
	mov		rdi, 16					; 16 BYTES in malloc param
	call	malloc
	pop		rsi						; Get ft_list_push_front second param
	pop		rdi						; Get ft_list_push_front t_list **

;;;; Initilaisation of t_list new ;;;;

set_data:
	mov		rcx, QWORD [rdi]		; Recup de *list
	mov		QWORD [rax + 8], rcx	; new->next = *list
	mov		QWORD [rax], rsi		; Set second param in new->data

set_head:
	mov		QWORD [rdi], rax		; Placement of in first position of list
	pop		rsp
	ret
