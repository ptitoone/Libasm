DEFAULT REL
bits 64

section .data
	lenStr	dd	0
	startStr	dd	0
	lenBase	dd	0
	pow		dd	0
	res		dq	0
	i_Base	dd	0
	isNeg	dq	0

section .text

global ft_atoi_base

ft_atoi_base:
	push	rbx
	xor		rax, rax
	xor		rbx, rbx				; i = 0
	xor		rcx, rcx				; j = 0
	xor		rdx, rdx				; k = 0
	add		rcx, 1					; j = 1
	mov		al, BYTE [rsi + rbx]			; isolate byte

chk_base_err_empty:
	cmp		al, 0
	je 		ret_err

chk_str_err_empty:
	cmp		al, 0
	je 		ret_err
	
chk_base_err_dup:

	mov		al, BYTE [rsi + rbx]			; isolate byte

	cmp		al, 43							; check if '+' || '-'
	je		ret_err							;
	cmp		al, 45							;
	je		ret_err							;

	cmp		al, 7							; check whitespaces
	je		ret_err							;
	cmp		al, 8							;
	je		ret_err							;
	cmp		al, 9							;
	je		ret_err							;
	cmp		al, 10							;
	je		ret_err							;
	cmp		al, 11							;
	je		ret_err							;
	cmp		al, 12							;
	je		ret_err							;
	cmp		al, 13							;
	je		ret_err							;
	cmp		al, 32							;
	je		ret_err							;

	cmp		al, BYTE [rsi + rcx]			; check if duplicate chars
	je		ret_err							;

	cmp		BYTE [rsi + rbx + 2], 0			; check if last char to compare
	je		chk_str							;

	cmp		BYTE [rsi + rbx + 2], 43		; check if +
	je		ret_err							;
	cmp		BYTE [rsi + rbx + 2], 45		; check if -
	je		ret_err							;

	cmp		BYTE [rsi + rbx + 2], 7			; check if white
	je		ret_err							;
	cmp		BYTE [rsi + rbx + 2], 8			; check if white
	je		ret_err							;
	cmp		BYTE [rsi + rbx + 2], 9			; check if white
	je		ret_err							;
	cmp		BYTE [rsi + rbx + 2], 10		; check if white
	je		ret_err							;
	cmp		BYTE [rsi + rbx + 2], 11		; check if white
	je		ret_err							;
	cmp		BYTE [rsi + rbx + 2], 12		; check if white
	je		ret_err							;
	cmp		BYTE [rsi + rbx + 2], 32		; check if white
	je		ret_err							;

	cmp		BYTE [rsi + rcx + 1], 0			; check rcx '\0'
	je		chk_base_err_dup_inc_i			
	inc		rcx
	jmp		chk_base_err_dup

chk_base_err_dup_inc_i:
	inc		rbx
	xor		rcx, rcx
	mov		rcx, rbx
	add		rcx, 1
	jmp		chk_base_err_dup

chk_str:
	xor		rbx, rbx
	mov		rbx, -1
	jmp		chk_str_while_white

chk_str_while_white:
	inc		rbx
	mov		al, BYTE [rdi + rbx]			; isolate byte

	cmp		al, 7							; check whitespaces
	je		chk_str_while_white				;
	cmp		al, 8							;
	je		chk_str_while_white				;
	cmp		al, 9							;
	je		chk_str_while_white				;
	cmp		al, 10							;
	je		chk_str_while_white				;
	cmp		al, 11							;
	je		chk_str_while_white				;
	cmp		al, 12							;
	je		chk_str_while_white				;
	cmp		al, 13							;
	je		chk_str_while_white				;
	cmp		al, 32							;
	je		chk_str_while_white				;

	cmp		al, 43							; check '+' || '-' 
	je		chk_str_sign					;
	cmp		al, 45							; 
	je		chk_str_sign

	jmp		chk_zero

chk_str_sign:
	cmp		al, 43							; check '+' || '-'
	je		chk_str_sign_p					;
	cmp		al, 45							;
	je		chk_str_sign_n					;
	jmp		chk_zero

chk_str_sign_p:
;	mov		QWORD [isNeg], 0					; set positiv flag
	inc		rbx								;
	mov		al, BYTE [rdi + rbx]			;
	jmp		chk_str_sign					;

chk_str_sign_n:
	inc		QWORD [isNeg]					; set negativ flag
	inc		rbx								;
	mov		al, BYTE [rdi + rbx]			;
	jmp		chk_str_sign					;

chk_zero:
	cmp		al, 48
	jne		get_lens
	inc		rbx
	mov		al, BYTE [rdi + rbx]
	jmp		chk_zero

get_lens:
	cmp		BYTE [rdi + rbx], 0
	je		ret_err
	add		rdx, rbx
	mov		[startStr], ebx					; save startStr index 
	jmp		get_len_str

get_len_str:
	mov		al, BYTE [rdi + rdx]
	cmp		al, 0
	je		set_len_str
	mov 	rcx, -1
	jmp		chk_is_base

chk_is_base:
	inc		rcx
	cmp		BYTE [rsi + rcx], 0
	je		set_len_str
	cmp		al, [rsi + rcx]
	jne		chk_is_base
	inc		rdx
	jmp		get_len_str
		

set_len_str:
	sub		rdx, rbx
	mov		[lenStr], edx
	mov		rcx, -1
	jmp		get_len_base

get_len_base:
	inc		rcx
	cmp		BYTE [rsi + rcx], 0
	jne		get_len_base
	mov		[lenBase], ecx
	jmp		calc

;;;;;;;;;;;;;;;;;

calc:
	xor		rax, rax
	xor		rcx, rcx
	jmp		get_i_base

get_i_base:
	mov		al,	BYTE [rdi + rbx]
	cmp		BYTE [rsi + rcx], 0				; RCX = BASE_I
	je		ret_err
	cmp		al, BYTE [rsi + rcx]			; RCX = BASE_I
	je		calc_pow
	inc		rcx
	jmp		get_i_base

calc_pow:
	mov		[i_Base], ecx
	xor		rcx, rcx
	xor		rax, rax
	cmp		DWORD [lenStr], 2
	je 		calc_lenStr_two
	cmp		DWORD [lenStr], 1
	je 		calc_last
	mov		ecx, [lenStr]
	mov		eax, [lenBase]
	jmp		calc_pow_loop

calc_pow_loop:
	dec		rcx
	cmp		rcx, 1
	je		add_res
	mul		DWORD [lenBase]
	jmp		calc_pow_loop
	
add_res:
	mul		DWORD [i_Base]
	add		QWORD [res], rax
	inc		rbx
	dec		DWORD [lenStr]
	jmp		calc 

calc_lenStr_two:
	mov		rax, [i_Base]
	mul		DWORD [lenBase]
	add		QWORD [res], rax
	dec		DWORD [lenStr]
	inc		rbx
	jmp		calc

calc_last:
	xor		rax, rax
	mov		rax, QWORD [res]
	add		eax, DWORD [i_Base]
	cmp		QWORD [isNeg], 0
	jg		set_polarity
	jmp		return

;;;;;;;;;;;;;;;;;

set_polarity:
	xor		rcx, rcx
	mov		rcx, QWORD [isNeg]
	cmp		rcx, 1
	je		negate
	xor		rdx, rdx
	push	rax
	xor		rax, rax
	mov		rcx, 2
	mov		al, BYTE [isNeg]
	idiv	rcx
	pop		rax
	cmp		rdx, 0
	je		return
	jmp		negate

negate:
	neg 	rax
	jmp		return

return:
	mov		QWORD [res], 0
	mov		DWORD [i_Base], 0
	mov		DWORD [lenStr], 0
	mov		DWORD [lenBase], 0
	mov		BYTE [isNeg], 0
	pop		rbx
	ret

ret_err:
	xor		rax, rax
	pop		rbx
	ret

