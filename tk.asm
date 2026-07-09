format ELF64

	extrn   loc_main
	extrn   mu_main
	extrn   relf_main
	extrn   tm_main

public main

SYS_WRITE       equ     1
SYS_EXIT        equ     60

macro write fd, buffer, count
	{
	mov     rax, SYS_WRITE
	mov     rdi, fd
	mov     rsi, buffer
	mov     rdx, count
	syscall
	}

macro exit code
	{
	mov     rax, SYS_EXIT
	mov     rdi, code
	syscall
	}

macro comp string, count
	{
	push    rsi
	push    rdi

	mov     rsi, [rsi + 8]
	lea     rdi, [string]
	mov     rcx, count

	repe    cmpsb
	}

macro prepreg offst
	{
	pop     rdi
	pop     rsi

	add     rsi, offst
	dec     edi
	sub     rsp, offst
	}

section '.text' executable

main:
	cmp     edi, 1
	jle     .err

	comp    str_loc, 4
	je      .run_loc
	pop     rdi
	pop     rsi

	comp    str_mu, 3
	je      .run_mu
	pop     rdi
	pop     rsi

	comp    str_relf, 5
	je      .run_relf
	pop     rdi
	pop     rsi

	comp    str_tm, 3
	je      .run_tm
	pop     rdi
	pop     rsi

	exit    0

.err:
	write   1, error_msg, error_msg_len
	exit    1

.run_mu:
	prepreg 8
	call    mu_main

	add     rsp, 8
	exit    0

.run_loc:
	prepreg 8
	call    loc_main

	add     rsp, 8
	exit    0

.run_relf:
	prepreg 8
	call    relf_main

	add     rsp, 8
	exit    0

.run_tm:
	prepreg 8
	call    tm_main

	add     rsp, 8
	exit    0

section '.data'
str_loc         db      "loc", 0
str_mu          db      "mu", 0
str_relf        db      "relf", 0
str_tm          db      "tm", 0
error_msg       db      "Not enough arguments were provided!", 10
error_msg_len = $ - error_msg

section '.note.GNU-stack'