	.file	"code.c"
	.text
	.globl	apple_gets
	.type	apple_gets, @function
apple_gets:
.LFB51:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	pushq	%rbx
	.cfi_def_cfa_offset 24
	.cfi_offset 3, -24
	subq	$8, %rsp
	.cfi_def_cfa_offset 32
	movq	%rdi, %rbp
	cmpl	$0, warned.1(%rip)
	je	.L10
.L2:
	movq	%rbp, %rbx
	jmp	.L6
.L10:
	movq	stderr(%rip), %rcx
	movl	$52, %edx
	movl	$1, %esi
	leaq	w.0(%rip), %rdi
	call	fwrite@PLT
	movl	$1, warned.1(%rip)
	jmp	.L2
.L3:
	movb	%al, (%rbx)
	leaq	1(%rbx), %rbx
.L6:
	movq	stdin(%rip), %rdi
	call	getc@PLT
	cmpl	$10, %eax
	je	.L5
	cmpl	$-1, %eax
	jne	.L3
	cmpq	%rbp, %rbx
	je	.L11
.L5:
	movb	$0, (%rbx)
	movq	%rbp, %rax
.L1:
	addq	$8, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 24
	popq	%rbx
	.cfi_def_cfa_offset 16
	popq	%rbp
	.cfi_def_cfa_offset 8
	ret
.L11:
	.cfi_restore_state
	movl	$0, %eax
	jmp	.L1
	.cfi_endproc
.LFE51:
	.size	apple_gets, .-apple_gets
	.globl	musl_gets
	.type	musl_gets, @function
musl_gets:
.LFB52:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	pushq	%rbx
	.cfi_def_cfa_offset 24
	.cfi_offset 3, -24
	subq	$8, %rsp
	.cfi_def_cfa_offset 32
	movq	%rdi, %rbx
	movq	stdin(%rip), %rcx
	movl	$2147483647, %edx
	movq	$-1, %rsi
	call	__fgets_chk@PLT
	movq	%rax, %rbp
	testq	%rax, %rax
	je	.L12
	movq	%rbx, %rdi
	call	strlen@PLT
	leaq	-1(%rbx,%rax), %rax
	cmpb	$10, (%rax)
	je	.L15
.L12:
	movq	%rbp, %rax
	addq	$8, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 24
	popq	%rbx
	.cfi_def_cfa_offset 16
	popq	%rbp
	.cfi_def_cfa_offset 8
	ret
.L15:
	.cfi_restore_state
	movb	$0, (%rax)
	jmp	.L12
	.cfi_endproc
.LFE52:
	.size	musl_gets, .-musl_gets
	.globl	calloc
	.type	calloc, @function
calloc:
.LFB53:
	.cfi_startproc
	endbr64
	testq	%rsi, %rsi
	je	.L17
	movl	$0, %ecx
	movq	%rdi, %rax
	mulq	%rsi
	jo	.L28
.L18:
	testq	%rcx, %rcx
	jne	.L24
.L17:
	pushq	%rbx
	.cfi_def_cfa_offset 16
	.cfi_offset 3, -16
	movq	%rsi, %rbx
	imulq	%rdi, %rbx
	movq	%rbx, %rdi
	call	malloc@PLT
	testq	%rax, %rax
	je	.L16
	leaq	7(%rbx), %rdx
	shrq	$3, %rdx
	movq	%rax, %rcx
	jmp	.L21
.L28:
	.cfi_def_cfa_offset 8
	.cfi_restore 3
	movl	$1, %ecx
	jmp	.L18
.L22:
	.cfi_def_cfa_offset 16
	.cfi_offset 3, -16
	subq	$1, %rdx
	addq	$8, %rcx
.L21:
	testq	%rdx, %rdx
	je	.L16
	cmpq	$0, (%rcx)
	je	.L22
	movq	$0, (%rcx)
	jmp	.L22
.L24:
	.cfi_def_cfa_offset 8
	.cfi_restore 3
	movl	$0, %eax
	ret
.L16:
	.cfi_def_cfa_offset 16
	.cfi_offset 3, -16
	popq	%rbx
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE53:
	.size	calloc, .-calloc
	.section	.rodata.str1.8,"aMS",@progbits,1
	.align 8
.LC0:
	.string	"This is the assign3 code program.\nWhat is your name? "
	.align 8
.LC1:
	.string	"Buffer is size %zu, your name is size %zu.\n"
	.text
	.globl	main
	.type	main, @function
main:
.LFB54:
	.cfi_startproc
	endbr64
	subq	$40, %rsp
	.cfi_def_cfa_offset 48
	movq	%fs:40, %rax
	movq	%rax, 24(%rsp)
	xorl	%eax, %eax
	leaq	.LC0(%rip), %rsi
	movl	$1, %edi
	call	__printf_chk@PLT
	movq	%rsp, %rdi
	movl	$0, %eax
	call	gets@PLT
	testl	%eax, %eax
	jne	.L33
.L30:
	movq	24(%rsp), %rax
	subq	%fs:40, %rax
	jne	.L34
	movl	$0, %eax
	addq	$40, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 8
	ret
.L33:
	.cfi_restore_state
	movq	%rsp, %rdi
	call	strlen@PLT
	movq	%rax, %rcx
	movl	$16, %edx
	leaq	.LC1(%rip), %rsi
	movl	$1, %edi
	movl	$0, %eax
	call	__printf_chk@PLT
	jmp	.L30
.L34:
	call	__stack_chk_fail@PLT
	.cfi_endproc
.LFE54:
	.size	main, .-main
	.section	.rodata
	.align 32
	.type	w.0, @object
	.size	w.0, 53
w.0:
	.string	"warning: this program uses gets(), which is unsafe.\n"
	.local	warned.1
	.comm	warned.1,4,4
	.ident	"GCC: (Ubuntu 11.4.0-1ubuntu1~22.04) 11.4.0"
	.section	.note.GNU-stack,"",@progbits
	.section	.note.gnu.property,"a"
	.align 8
	.long	1f - 0f
	.long	4f - 1f
	.long	5
0:
	.string	"GNU"
1:
	.align 8
	.long	0xc0000002
	.long	3f - 2f
2:
	.long	0x3
3:
	.align 8
4:
