	.file	"d.c"
	.text
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC2:
	.string	"%f %x\n"
	.section	.text.startup,"ax",@progbits
	.p2align 4,,15
	.globl	main
	.type	main, @function
main:
.LFB23:
	.cfi_startproc
	subq	$8, %rsp
	.cfi_def_cfa_offset 16
	movss	.LC0(%rip), %xmm1
	movss	.LC1(%rip), %xmm0
	call	mul@PLT
	movl	$1, %edi
	movl	$1, %eax
	leaq	.LC2(%rip), %rsi
	movaps	%xmm0, %xmm1
	cvtss2sd	%xmm0, %xmm0
	movd	%xmm1, %edx
	call	__printf_chk@PLT
	xorl	%eax, %eax
	addq	$8, %rsp
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE23:
	.size	main, .-main
	.section	.rodata.cst4,"aM",@progbits,4
	.align 4
.LC0:
	.long	1085695590
	.align 4
.LC1:
	.long	1067869798
	.ident	"GCC: (Ubuntu 8.4.0-1ubuntu1~18.04) 8.4.0"
	.section	.note.GNU-stack,"",@progbits
