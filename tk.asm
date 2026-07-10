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

	comp    str_loc, loc_len
	je      .run_loc
	pop     rdi
	pop     rsi

	comp    str_mu, mu_len
	je      .run_mu
	pop     rdi
	pop     rsi

	comp    str_relf, relf_len
	je      .run_relf
	pop     rdi
	pop     rsi

	comp    str_tm, tm_len
	je      .run_tm
	pop     rdi
	pop     rsi

	comp    str_help, help_len
	je      .help

	exit    0

.help:
	write   1, help_msg, help_msg_len
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
loc_len =				$ - str_loc

str_mu          db      "mu", 0
mu_len = 				$ - str_mu

str_relf        db      "relf", 0
relf_len = 			$ - str_relf

str_tm          db      "tm", 0
tm_len = 				$ - str_tm

str_help        db      "--help", 0
help_len = 			$ - str_help

error_msg       db      "Not enough arguments were provided! See --help for usage", 10
error_msg_len = $ - error_msg

help_msg        db      "Programs: ", 10
								db      " loc - Lines Of Code", 10
								db      " mu - Disk Memory Usage", 10
								db      " relf - Read Elf", 10
								db      " tm - Time", 10
help_msg_len = 	$ - help_msg

section '.note.GNU-stack'