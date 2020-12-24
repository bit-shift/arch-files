	.section	__TEXT,__text,regular,pure_instructions
	.macosx_version_min 10, 13
	.globl	_main
	.p2align	4, 0x90
_main:                                  ## @main
	.cfi_startproc
## BB#0:
	pushq	%rbp
Lcfi0:
	.cfi_def_cfa_offset 16
Lcfi1:
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
Lcfi2:
	.cfi_def_cfa_register %rbp
	subq	$48, %rsp
	leaq	L_.str(%rip), %rdi
	movl	$0, -4(%rbp)
	movb	$0, %al
	callq	_printf
	leaq	L_.str.1(%rip), %rdi
	movl	$2, -8(%rbp)
	movl	-8(%rbp), %esi
	movl	%eax, -20(%rbp)         ## 4-byte Spill
	movb	$0, %al
	callq	_printf
	leaq	L_.str.2(%rip), %rdi
	leaq	-13(%rbp), %rsi
	movl	L_main.name(%rip), %ecx
	movl	%ecx, -13(%rbp)
	movb	L_main.name+4(%rip), %dl
	movb	%dl, -9(%rbp)
	movl	%eax, -24(%rbp)         ## 4-byte Spill
	movb	$0, %al
	callq	_printf
	leaq	L_.str.3(%rip), %rdi
	leaq	-13(%rbp), %rsi
	movq	%rdi, -32(%rbp)         ## 8-byte Spill
	movq	%rsi, %rdi
	movl	%eax, -36(%rbp)         ## 4-byte Spill
	callq	_strlen
	movq	-32(%rbp), %rdi         ## 8-byte Reload
	movq	%rax, %rsi
	movb	$0, %al
	callq	_printf
	leaq	L_.str.4(%rip), %rsi
	movl	$5, %ecx
	movl	%ecx, %edx
	leaq	-13(%rbp), %rdi
	movl	%eax, -40(%rbp)         ## 4-byte Spill
	callq	_strncmp
	cmpl	$0, %eax
	jne	LBB0_2
## BB#1:
	leaq	L_.str.5(%rip), %rdi
	movb	$0, %al
	callq	_printf
	movl	%eax, -44(%rbp)         ## 4-byte Spill
	jmp	LBB0_3
LBB0_2:
	leaq	L_.str.6(%rip), %rdi
	movb	$0, %al
	callq	_printf
	movl	%eax, -48(%rbp)         ## 4-byte Spill
LBB0_3:
	xorl	%eax, %eax
	addq	$48, %rsp
	popq	%rbp
	retq
	.cfi_endproc

	.section	__TEXT,__cstring,cstring_literals
L_.str:                                 ## @.str
	.asciz	"Hello, World!\n"

L_.str.1:                               ## @.str.1
	.asciz	"%d\n"

L_main.name:                            ## @main.name
	.asciz	"John"

L_.str.2:                               ## @.str.2
	.asciz	"%s\n"

L_.str.3:                               ## @.str.3
	.asciz	"%lu\n"

L_.str.4:                               ## @.str.4
	.asciz	"John"

L_.str.5:                               ## @.str.5
	.asciz	"Hello John!\n"

L_.str.6:                               ## @.str.6
	.asciz	"You are not John\n"


.subsections_via_symbols
