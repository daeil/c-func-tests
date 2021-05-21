	.file	"d.c"
	.text
	.section	.rodata
.LC2:
	.string	"%f %x\n"
	.text
	.globl	main
	.type	main, @function
main:
.LFB0:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$48, %rsp
	movl	%edi, -36(%rbp)
	movq	%rsi, -48(%rbp)
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	movss	.LC0(%rip), %xmm0
	movss	%xmm0, -16(%rbp)
	movss	.LC1(%rip), %xmm0
	movss	%xmm0, -12(%rbp)
	movss	-12(%rbp), %xmm1
	movss	-16(%rbp), %xmm0
	call	mul@PLT
	movd	%xmm0, %eax
	movl	%eax, -20(%rbp)
	leaq	-20(%rbp), %rax
	movl	(%rax), %eax
	movss	-20(%rbp), %xmm0
	cvtss2sd	%xmm0, %xmm0
	movl	%eax, %esi
	leaq	.LC2(%rip), %rdi
	movl	$1, %eax
	call	printf@PLT
	movl	$0, %eax
	movq	-8(%rbp), %rdx
	xorq	%fs:40, %rdx
	je	.L3
	call	__stack_chk_fail@PLT
.L3:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	main, .-main
	.section	.rodata
	.align 4
.LC0:
	.long	1067869798
	.align 4
.LC1:
	.long	1085695590
	.ident	"GCC: (Ubuntu 8.4.0-1ubuntu1~18.04) 8.4.0"
	.section	.note.GNU-stack,"",@progbits
