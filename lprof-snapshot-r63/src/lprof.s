	.file	"lprof.c"
	.section	.debug_abbrev,"",@progbits
.Ldebug_abbrev0:
	.section	.debug_info,"",@progbits
.Ldebug_info0:
	.section	.debug_line,"",@progbits
.Ldebug_line0:
	.text
.Ltext0:
	.p2align 4,,15
.globl lprof_close
	.type	lprof_close, @function
lprof_close:
.LFB59:
	.file 1 "lprof.c"
	.loc 1 73 0
	.cfi_startproc
	.loc 1 75 0
	movl	num_ctrs(%rip), %eax
	.loc 1 73 0
	pushq	%rbx
.LCFI0:
	.cfi_def_cfa_offset 16
	.loc 1 75 0
	testl	%eax, %eax
	js	.L4
	.cfi_offset 3, -16
	xorl	%ebx, %ebx
.LVL0:
	.p2align 4,,10
	.p2align 3
.L3:
.LBB12:
.LBB13:
	.file 2 "../include/linux/lprof.h"
	.loc 2 50 0
	xorl	%r8d, %r8d
	xorl	%ecx, %ecx
	movl	%ebx, %edx
	xorl	%esi, %esi
	xorl	%eax, %eax
	movl	$299, %edi
	call	syscall
.LBE13:
.LBE12:
	.loc 1 75 0
	addl	$1, %ebx
.LVL1:
	cmpl	%ebx, num_ctrs(%rip)
	jge	.L3
.L4:
	.loc 1 77 0
	popq	%rbx
.LVL2:
	ret
	.cfi_endproc
.LFE59:
	.size	lprof_close, .-lprof_close
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC0:
	.string	"Error registering CS"
	.section	.rodata.str1.8,"aMS",@progbits,1
	.align 8
.LC1:
	.string	"Configuring counter %d as %04x\n"
	.section	.rodata.str1.1
.LC2:
	.string	"Error configuring counter"
	.text
	.p2align 4,,15
.globl lprof_init
	.type	lprof_init, @function
lprof_init:
.LFB58:
	.loc 1 40 0
	.cfi_startproc
.LVL3:
	pushq	%r14
.LCFI1:
	.cfi_def_cfa_offset 16
	.file 3 "/usr/include/bits/string3.h"
	.loc 3 86 0
	xorl	%eax, %eax
	.loc 1 40 0
	movl	%edi, %r14d
	.cfi_offset 14, -16
	pushq	%r13
.LCFI2:
	.cfi_def_cfa_offset 24
	pushq	%r12
.LCFI3:
	.cfi_def_cfa_offset 32
	pushq	%rbp
.LCFI4:
	.cfi_def_cfa_offset 40
	pushq	%rbx
.LCFI5:
	.cfi_def_cfa_offset 48
	subq	$80, %rsp
.LCFI6:
	.cfi_def_cfa_offset 128
	.loc 1 40 0
	movq	%rdx, 48(%rsp)
	.loc 3 86 0
	movl	$__lp_stats, %edx
	.loc 1 40 0
	movq	%rcx, 56(%rsp)
	.loc 3 86 0
	movq	%rdx, %rdi
.LVL4:
	movl	$11, %ecx
	.loc 1 40 0
	movq	%rsi, 40(%rsp)
	movq	%r8, 64(%rsp)
	movq	%r9, 72(%rsp)
.LBB34:
.LBB36:
.LBB38:
.LBB39:
	.loc 2 50 0
	xorl	%edx, %edx
.LBE39:
.LBE38:
.LBE36:
.LBE34:
	.loc 3 86 0
	rep stosq
.LBB42:
.LBB35:
	.loc 1 32 0
	movl	$__lp_sec1, %ecx
.LBB37:
.LBB40:
	.loc 2 50 0
	movl	$__lp_sec0, %r8d
	movl	$4, %esi
	subq	$__lp_sec0, %rcx
	movl	$299, %edi
	.cfi_offset 3, -48
	.cfi_offset 6, -40
	.cfi_offset 12, -32
	.cfi_offset 13, -24
	call	syscall
.LBE40:
.LBE37:
	.loc 1 35 0
	testl	%eax, %eax
	js	.L23
.L8:
.LBE35:
.LBE42:
.LBB43:
.LBB44:
	.loc 1 32 0
	movl	$__lp_sec2, %ecx
.LBB45:
.LBB46:
	.loc 2 50 0
	xorl	%eax, %eax
	movl	$__lp_sec1, %r8d
	subq	$__lp_sec1, %rcx
	movl	$1, %edx
	movl	$4, %esi
	movl	$299, %edi
	call	syscall
.LBE46:
.LBE45:
	.loc 1 35 0
	testl	%eax, %eax
	js	.L24
.L9:
.LBE44:
.LBE43:
.LBB48:
.LBB49:
	.loc 1 32 0
	movl	$__lp_sec3, %ecx
.LBB50:
.LBB51:
	.loc 2 50 0
	xorl	%eax, %eax
	movl	$__lp_sec2, %r8d
	subq	$__lp_sec2, %rcx
	movl	$2, %edx
	movl	$4, %esi
	movl	$299, %edi
	call	syscall
.LBE51:
.LBE50:
	.loc 1 35 0
	testl	%eax, %eax
	js	.L25
.L10:
.LBE49:
.LBE48:
.LBB53:
.LBB54:
.LBB55:
.LBB56:
	.loc 2 50 0
	movl	$__lp_sec_end, %ecx
	xorl	%eax, %eax
	movl	$__lp_sec3, %r8d
	subq	$__lp_sec3, %rcx
	movl	$3, %edx
	movl	$4, %esi
	movl	$299, %edi
	call	syscall
.LBE56:
.LBE55:
	.loc 1 35 0
	testl	%eax, %eax
	js	.L26
.L11:
.LBE54:
.LBE53:
	.loc 1 53 0
	leaq	128(%rsp), %rax
	.loc 1 54 0
	testl	%r14d, %r14d
	.loc 1 53 0
	movl	$8, (%rsp)
	movq	%rax, 8(%rsp)
	leaq	32(%rsp), %rax
	movq	%rax, 16(%rsp)
	.loc 1 54 0
	je	.L12
	movl	$1, %ebp
	movl	$1, %r13d
.LVL5:
	.p2align 4,,10
	.p2align 3
.L18:
	.loc 1 55 0
	movl	(%rsp), %edx
	cmpl	$47, %edx
	ja	.L13
	mov	%edx, %eax
	addq	16(%rsp), %rax
	addl	$8, %edx
	movl	%edx, (%rsp)
.L14:
	movzwl	(%rax), %r12d
.LVL6:
.LBB58:
.LBB59:
	.file 4 "/usr/include/bits/stdio2.h"
	.loc 4 105 0
	movl	%r13d, %edx
	movl	$.LC1, %esi
	movl	$1, %edi
	xorl	%eax, %eax
	movl	%r12d, %ecx
	mov	%r12d, %r12d
.LVL7:
	call	__printf_chk
	.p2align 4,,10
	.p2align 3
.L16:
.LBE59:
.LBE58:
.LBB60:
.LBB61:
	.loc 2 50 0
	xorl	%eax, %eax
	movl	$__lp_stats, %r8d
	movq	%r12, %rcx
	movl	%ebp, %edx
	movl	$1, %esi
	movl	$299, %edi
	call	syscall
.LBE61:
.LBE60:
	.loc 1 59 0
	testl	%eax, %eax
.LBB63:
.LBB62:
	.loc 2 50 0
	movl	%eax, %ebx
.LBE62:
.LBE63:
	.loc 1 59 0
	jns	.L15
	call	__errno_location
	cmpl	$16, (%rax)
	.p2align 4,,2
	je	.L16
	.loc 1 62 0
	movl	$.LC2, %edi
	call	perror
.L15:
	.loc 1 54 0
	addl	$1, %r13d
	cmpl	%r13d, %r14d
	movl	%r13d, %ebp
	jae	.L18
.L12:
	.loc 1 67 0
	movl	%r14d, num_ctrs(%rip)
	.loc 1 70 0
	movl	%ebx, %eax
	addq	$80, %rsp
	popq	%rbx
.LVL8:
	popq	%rbp
	popq	%r12
	popq	%r13
.LVL9:
	popq	%r14
.LVL10:
	ret
.LVL11:
	.p2align 4,,10
	.p2align 3
.L13:
	.loc 1 55 0
	movq	8(%rsp), %rax
	leaq	8(%rax), %rdx
	movq	%rdx, 8(%rsp)
	jmp	.L14
.LVL12:
.L23:
.LBB64:
.LBB41:
	.loc 1 36 0
	movl	$.LC0, %edi
	call	perror
	jmp	.L8
.L24:
.LBE41:
.LBE64:
.LBB65:
.LBB47:
	movl	$.LC0, %edi
	call	perror
	.p2align 4,,3
	jmp	.L9
.L25:
.LBE47:
.LBE65:
.LBB66:
.LBB52:
	movl	$.LC0, %edi
	call	perror
	.p2align 4,,3
	jmp	.L10
.L26:
.LBE52:
.LBE66:
.LBB67:
.LBB57:
	movl	$.LC0, %edi
	call	perror
	.p2align 4,,3
	jmp	.L11
.LBE57:
.LBE67:
	.cfi_endproc
.LFE58:
	.size	lprof_init, .-lprof_init
	.local	num_ctrs
	.comm	num_ctrs,4,4
	.comm	__lp_stats,88,32
.Letext0:
	.section	.debug_loc,"",@progbits
.Ldebug_loc0:
.LLST0:
	.quad	.LFB59-.Ltext0
	.quad	.LCFI0-.Ltext0
	.value	0x2
	.byte	0x77
	.sleb128 8
	.quad	.LCFI0-.Ltext0
	.quad	.LFE59-.Ltext0
	.value	0x2
	.byte	0x77
	.sleb128 16
	.quad	0x0
	.quad	0x0
.LLST1:
	.quad	.LVL0-.Ltext0
	.quad	.LVL2-.Ltext0
	.value	0x1
	.byte	0x53
	.quad	0x0
	.quad	0x0
.LLST2:
	.quad	.LFB58-.Ltext0
	.quad	.LCFI1-.Ltext0
	.value	0x2
	.byte	0x77
	.sleb128 8
	.quad	.LCFI1-.Ltext0
	.quad	.LCFI2-.Ltext0
	.value	0x2
	.byte	0x77
	.sleb128 16
	.quad	.LCFI2-.Ltext0
	.quad	.LCFI3-.Ltext0
	.value	0x2
	.byte	0x77
	.sleb128 24
	.quad	.LCFI3-.Ltext0
	.quad	.LCFI4-.Ltext0
	.value	0x2
	.byte	0x77
	.sleb128 32
	.quad	.LCFI4-.Ltext0
	.quad	.LCFI5-.Ltext0
	.value	0x2
	.byte	0x77
	.sleb128 40
	.quad	.LCFI5-.Ltext0
	.quad	.LCFI6-.Ltext0
	.value	0x2
	.byte	0x77
	.sleb128 48
	.quad	.LCFI6-.Ltext0
	.quad	.LFE58-.Ltext0
	.value	0x3
	.byte	0x77
	.sleb128 128
	.quad	0x0
	.quad	0x0
.LLST3:
	.quad	.LVL3-.Ltext0
	.quad	.LVL4-.Ltext0
	.value	0x1
	.byte	0x55
	.quad	.LVL4-.Ltext0
	.quad	.LVL10-.Ltext0
	.value	0x1
	.byte	0x5e
	.quad	.LVL11-.Ltext0
	.quad	.LFE58-.Ltext0
	.value	0x1
	.byte	0x5e
	.quad	0x0
	.quad	0x0
.LLST4:
	.quad	.LVL5-.Ltext0
	.quad	.LVL8-.Ltext0
	.value	0x1
	.byte	0x53
	.quad	.LVL11-.Ltext0
	.quad	.LVL12-.Ltext0
	.value	0x1
	.byte	0x53
	.quad	0x0
	.quad	0x0
.LLST5:
	.quad	.LVL5-.Ltext0
	.quad	.LVL9-.Ltext0
	.value	0x1
	.byte	0x5d
	.quad	.LVL11-.Ltext0
	.quad	.LVL12-.Ltext0
	.value	0x1
	.byte	0x5d
	.quad	0x0
	.quad	0x0
.LLST6:
	.quad	.LVL6-.Ltext0
	.quad	.LVL7-.Ltext0
	.value	0x1
	.byte	0x5c
	.quad	0x0
	.quad	0x0
	.file 5 "lprof.i"
	.file 6 "/usr/lib/gcc/x86_64-linux-gnu/4.4.3/include/stdarg.h"
	.file 7 "/usr/lib/gcc/x86_64-linux-gnu/4.4.3/include/stddef.h"
	.file 8 "/usr/include/bits/types.h"
	.file 9 "/usr/include/stdio.h"
	.file 10 "/usr/include/libio.h"
	.file 11 "/usr/include/stdint.h"
	.section	.debug_info
	.long	0x76a
	.value	0x2
	.long	.Ldebug_abbrev0
	.byte	0x8
	.uleb128 0x1
	.long	.LASF75
	.byte	0x1
	.long	.LASF76
	.long	.LASF77
	.quad	.Ltext0
	.quad	.Letext0
	.long	.Ldebug_line0
	.uleb128 0x2
	.long	.LASF4
	.byte	0x6
	.byte	0x28
	.long	0x38
	.uleb128 0x3
	.long	0x4b
	.long	0x48
	.uleb128 0x4
	.long	0x48
	.byte	0x0
	.byte	0x0
	.uleb128 0x5
	.byte	0x8
	.byte	0x7
	.uleb128 0x6
	.long	.LASF17
	.byte	0x18
	.byte	0x5
	.byte	0x1
	.long	0x90
	.uleb128 0x7
	.long	.LASF0
	.byte	0x5
	.byte	0x1
	.long	0x90
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.uleb128 0x7
	.long	.LASF1
	.byte	0x5
	.byte	0x1
	.long	0x90
	.byte	0x2
	.byte	0x23
	.uleb128 0x4
	.uleb128 0x7
	.long	.LASF2
	.byte	0x5
	.byte	0x1
	.long	0x97
	.byte	0x2
	.byte	0x23
	.uleb128 0x8
	.uleb128 0x7
	.long	.LASF3
	.byte	0x5
	.byte	0x1
	.long	0x97
	.byte	0x2
	.byte	0x23
	.uleb128 0x10
	.byte	0x0
	.uleb128 0x8
	.byte	0x4
	.byte	0x7
	.long	.LASF7
	.uleb128 0x9
	.byte	0x8
	.uleb128 0x2
	.long	.LASF5
	.byte	0x6
	.byte	0x66
	.long	0x2d
	.uleb128 0x2
	.long	.LASF6
	.byte	0x7
	.byte	0xd3
	.long	0xaf
	.uleb128 0x8
	.byte	0x8
	.byte	0x7
	.long	.LASF8
	.uleb128 0x8
	.byte	0x1
	.byte	0x8
	.long	.LASF9
	.uleb128 0x8
	.byte	0x2
	.byte	0x7
	.long	.LASF10
	.uleb128 0x8
	.byte	0x1
	.byte	0x6
	.long	.LASF11
	.uleb128 0x8
	.byte	0x2
	.byte	0x5
	.long	.LASF12
	.uleb128 0xa
	.byte	0x4
	.byte	0x5
	.string	"int"
	.uleb128 0x8
	.byte	0x8
	.byte	0x5
	.long	.LASF13
	.uleb128 0x2
	.long	.LASF14
	.byte	0x8
	.byte	0x8d
	.long	0xd9
	.uleb128 0x2
	.long	.LASF15
	.byte	0x8
	.byte	0x8e
	.long	0xd9
	.uleb128 0xb
	.byte	0x8
	.long	0xfc
	.uleb128 0x8
	.byte	0x1
	.byte	0x6
	.long	.LASF16
	.uleb128 0x6
	.long	.LASF18
	.byte	0xd8
	.byte	0x9
	.byte	0x2d
	.long	0x2cf
	.uleb128 0xc
	.long	.LASF19
	.byte	0xa
	.value	0x110
	.long	0xd2
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.uleb128 0xc
	.long	.LASF20
	.byte	0xa
	.value	0x115
	.long	0xf6
	.byte	0x2
	.byte	0x23
	.uleb128 0x8
	.uleb128 0xc
	.long	.LASF21
	.byte	0xa
	.value	0x116
	.long	0xf6
	.byte	0x2
	.byte	0x23
	.uleb128 0x10
	.uleb128 0xc
	.long	.LASF22
	.byte	0xa
	.value	0x117
	.long	0xf6
	.byte	0x2
	.byte	0x23
	.uleb128 0x18
	.uleb128 0xc
	.long	.LASF23
	.byte	0xa
	.value	0x118
	.long	0xf6
	.byte	0x2
	.byte	0x23
	.uleb128 0x20
	.uleb128 0xc
	.long	.LASF24
	.byte	0xa
	.value	0x119
	.long	0xf6
	.byte	0x2
	.byte	0x23
	.uleb128 0x28
	.uleb128 0xc
	.long	.LASF25
	.byte	0xa
	.value	0x11a
	.long	0xf6
	.byte	0x2
	.byte	0x23
	.uleb128 0x30
	.uleb128 0xc
	.long	.LASF26
	.byte	0xa
	.value	0x11b
	.long	0xf6
	.byte	0x2
	.byte	0x23
	.uleb128 0x38
	.uleb128 0xc
	.long	.LASF27
	.byte	0xa
	.value	0x11c
	.long	0xf6
	.byte	0x2
	.byte	0x23
	.uleb128 0x40
	.uleb128 0xc
	.long	.LASF28
	.byte	0xa
	.value	0x11e
	.long	0xf6
	.byte	0x2
	.byte	0x23
	.uleb128 0x48
	.uleb128 0xc
	.long	.LASF29
	.byte	0xa
	.value	0x11f
	.long	0xf6
	.byte	0x2
	.byte	0x23
	.uleb128 0x50
	.uleb128 0xc
	.long	.LASF30
	.byte	0xa
	.value	0x120
	.long	0xf6
	.byte	0x2
	.byte	0x23
	.uleb128 0x58
	.uleb128 0xc
	.long	.LASF31
	.byte	0xa
	.value	0x122
	.long	0x30d
	.byte	0x2
	.byte	0x23
	.uleb128 0x60
	.uleb128 0xc
	.long	.LASF32
	.byte	0xa
	.value	0x124
	.long	0x313
	.byte	0x2
	.byte	0x23
	.uleb128 0x68
	.uleb128 0xc
	.long	.LASF33
	.byte	0xa
	.value	0x126
	.long	0xd2
	.byte	0x2
	.byte	0x23
	.uleb128 0x70
	.uleb128 0xc
	.long	.LASF34
	.byte	0xa
	.value	0x12a
	.long	0xd2
	.byte	0x2
	.byte	0x23
	.uleb128 0x74
	.uleb128 0xc
	.long	.LASF35
	.byte	0xa
	.value	0x12c
	.long	0xe0
	.byte	0x2
	.byte	0x23
	.uleb128 0x78
	.uleb128 0xc
	.long	.LASF36
	.byte	0xa
	.value	0x130
	.long	0xbd
	.byte	0x3
	.byte	0x23
	.uleb128 0x80
	.uleb128 0xc
	.long	.LASF37
	.byte	0xa
	.value	0x131
	.long	0xc4
	.byte	0x3
	.byte	0x23
	.uleb128 0x82
	.uleb128 0xc
	.long	.LASF38
	.byte	0xa
	.value	0x132
	.long	0x319
	.byte	0x3
	.byte	0x23
	.uleb128 0x83
	.uleb128 0xc
	.long	.LASF39
	.byte	0xa
	.value	0x136
	.long	0x329
	.byte	0x3
	.byte	0x23
	.uleb128 0x88
	.uleb128 0xc
	.long	.LASF40
	.byte	0xa
	.value	0x13f
	.long	0xeb
	.byte	0x3
	.byte	0x23
	.uleb128 0x90
	.uleb128 0xc
	.long	.LASF41
	.byte	0xa
	.value	0x148
	.long	0x97
	.byte	0x3
	.byte	0x23
	.uleb128 0x98
	.uleb128 0xc
	.long	.LASF42
	.byte	0xa
	.value	0x149
	.long	0x97
	.byte	0x3
	.byte	0x23
	.uleb128 0xa0
	.uleb128 0xc
	.long	.LASF43
	.byte	0xa
	.value	0x14a
	.long	0x97
	.byte	0x3
	.byte	0x23
	.uleb128 0xa8
	.uleb128 0xc
	.long	.LASF44
	.byte	0xa
	.value	0x14b
	.long	0x97
	.byte	0x3
	.byte	0x23
	.uleb128 0xb0
	.uleb128 0xc
	.long	.LASF45
	.byte	0xa
	.value	0x14c
	.long	0xa4
	.byte	0x3
	.byte	0x23
	.uleb128 0xb8
	.uleb128 0xc
	.long	.LASF46
	.byte	0xa
	.value	0x14e
	.long	0xd2
	.byte	0x3
	.byte	0x23
	.uleb128 0xc0
	.uleb128 0xc
	.long	.LASF47
	.byte	0xa
	.value	0x150
	.long	0x32f
	.byte	0x3
	.byte	0x23
	.uleb128 0xc4
	.byte	0x0
	.uleb128 0xd
	.long	.LASF78
	.byte	0xa
	.byte	0xb4
	.uleb128 0x6
	.long	.LASF48
	.byte	0x18
	.byte	0xa
	.byte	0xba
	.long	0x30d
	.uleb128 0x7
	.long	.LASF49
	.byte	0xa
	.byte	0xbb
	.long	0x30d
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.uleb128 0x7
	.long	.LASF50
	.byte	0xa
	.byte	0xbc
	.long	0x313
	.byte	0x2
	.byte	0x23
	.uleb128 0x8
	.uleb128 0x7
	.long	.LASF51
	.byte	0xa
	.byte	0xc0
	.long	0xd2
	.byte	0x2
	.byte	0x23
	.uleb128 0x10
	.byte	0x0
	.uleb128 0xb
	.byte	0x8
	.long	0x2d6
	.uleb128 0xb
	.byte	0x8
	.long	0x103
	.uleb128 0x3
	.long	0xfc
	.long	0x329
	.uleb128 0x4
	.long	0x48
	.byte	0x0
	.byte	0x0
	.uleb128 0xb
	.byte	0x8
	.long	0x2cf
	.uleb128 0x3
	.long	0xfc
	.long	0x33f
	.uleb128 0x4
	.long	0x48
	.byte	0x13
	.byte	0x0
	.uleb128 0xb
	.byte	0x8
	.long	0x345
	.uleb128 0xe
	.long	0xfc
	.uleb128 0x2
	.long	.LASF52
	.byte	0xb
	.byte	0x29
	.long	0xd9
	.uleb128 0x2
	.long	.LASF53
	.byte	0xb
	.byte	0x38
	.long	0xaf
	.uleb128 0x6
	.long	.LASF54
	.byte	0x58
	.byte	0x2
	.byte	0x1d
	.long	0x3a5
	.uleb128 0x7
	.long	.LASF55
	.byte	0x2
	.byte	0x1e
	.long	0xb6
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.uleb128 0x7
	.long	.LASF56
	.byte	0x2
	.byte	0x1f
	.long	0x355
	.byte	0x2
	.byte	0x23
	.uleb128 0x8
	.uleb128 0x7
	.long	.LASF57
	.byte	0x2
	.byte	0x20
	.long	0x355
	.byte	0x2
	.byte	0x23
	.uleb128 0x10
	.uleb128 0x7
	.long	.LASF58
	.byte	0x2
	.byte	0x21
	.long	0x3a5
	.byte	0x2
	.byte	0x23
	.uleb128 0x18
	.byte	0x0
	.uleb128 0x3
	.long	0x34a
	.long	0x3b5
	.uleb128 0x4
	.long	0x48
	.byte	0x7
	.byte	0x0
	.uleb128 0xf
	.long	.LASF79
	.byte	0x2
	.byte	0x2f
	.byte	0x1
	.long	0xd2
	.byte	0x3
	.long	0x3f2
	.uleb128 0x10
	.string	"op"
	.byte	0x2
	.byte	0x2f
	.long	0x90
	.uleb128 0x11
	.long	.LASF59
	.byte	0x2
	.byte	0x2f
	.long	0x90
	.uleb128 0x11
	.long	.LASF60
	.byte	0x2
	.byte	0x30
	.long	0x3f2
	.uleb128 0x10
	.string	"ptr"
	.byte	0x2
	.byte	0x30
	.long	0x97
	.byte	0x0
	.uleb128 0x8
	.byte	0x8
	.byte	0x7
	.long	.LASF61
	.uleb128 0x12
	.byte	0x1
	.long	.LASF65
	.byte	0x3
	.byte	0x4e
	.byte	0x1
	.long	0x97
	.byte	0x3
	.byte	0x1
	.long	0x42e
	.uleb128 0x11
	.long	.LASF62
	.byte	0x3
	.byte	0x4e
	.long	0x97
	.uleb128 0x11
	.long	.LASF63
	.byte	0x3
	.byte	0x4e
	.long	0xd2
	.uleb128 0x11
	.long	.LASF64
	.byte	0x3
	.byte	0x4e
	.long	0xa4
	.byte	0x0
	.uleb128 0x12
	.byte	0x1
	.long	.LASF66
	.byte	0x4
	.byte	0x67
	.byte	0x1
	.long	0xd2
	.byte	0x3
	.byte	0x1
	.long	0x44e
	.uleb128 0x11
	.long	.LASF67
	.byte	0x4
	.byte	0x67
	.long	0x33f
	.uleb128 0x13
	.byte	0x0
	.uleb128 0x14
	.byte	0x1
	.long	.LASF80
	.byte	0x1
	.byte	0x49
	.quad	.LFB59
	.quad	.LFE59
	.long	.LLST0
	.long	0x4a8
	.uleb128 0x15
	.string	"i"
	.byte	0x1
	.byte	0x4a
	.long	0xd2
	.long	.LLST1
	.uleb128 0x16
	.long	0x3b5
	.quad	.LBB12
	.quad	.LBE12
	.byte	0x1
	.byte	0x4c
	.uleb128 0x17
	.long	0x3e6
	.uleb128 0x17
	.long	0x3db
	.uleb128 0x17
	.long	0x3d0
	.uleb128 0x17
	.long	0x3c6
	.byte	0x0
	.byte	0x0
	.uleb128 0x18
	.long	.LASF81
	.byte	0x1
	.byte	0x1e
	.byte	0x1
	.byte	0x1
	.long	0x4e6
	.uleb128 0x10
	.string	"i"
	.byte	0x1
	.byte	0x1e
	.long	0xd2
	.uleb128 0x10
	.string	"b"
	.byte	0x1
	.byte	0x1e
	.long	0x97
	.uleb128 0x10
	.string	"e"
	.byte	0x1
	.byte	0x1e
	.long	0x97
	.uleb128 0x19
	.string	"rc"
	.byte	0x1
	.byte	0x1f
	.long	0xd2
	.uleb128 0x1a
	.long	.LASF68
	.byte	0x1
	.byte	0x20
	.long	0xa4
	.byte	0x0
	.uleb128 0x1b
	.byte	0x1
	.long	.LASF82
	.byte	0x1
	.byte	0x28
	.byte	0x1
	.long	0xd2
	.quad	.LFB58
	.quad	.LFE58
	.long	.LLST2
	.long	0x728
	.uleb128 0x1c
	.string	"num"
	.byte	0x1
	.byte	0x28
	.long	0x90
	.long	.LLST3
	.uleb128 0x13
	.uleb128 0x1d
	.long	.LASF69
	.byte	0x1
	.byte	0x29
	.long	0x99
	.byte	0x3
	.byte	0x91
	.sleb128 -128
	.uleb128 0x15
	.string	"rc"
	.byte	0x1
	.byte	0x2a
	.long	0xd2
	.long	.LLST4
	.uleb128 0x15
	.string	"ctr"
	.byte	0x1
	.byte	0x2a
	.long	0xd2
	.long	.LLST5
	.uleb128 0x1e
	.long	.LASF70
	.byte	0x1
	.byte	0x2b
	.long	0x90
	.long	.LLST6
	.uleb128 0x1f
	.long	0x4a8
	.quad	.LBB34
	.long	.Ldebug_ranges0+0x0
	.byte	0x1
	.byte	0x2f
	.long	0x5b5
	.uleb128 0x17
	.long	0x4c7
	.uleb128 0x17
	.long	0x4be
	.uleb128 0x17
	.long	0x4b5
	.uleb128 0x20
	.long	.Ldebug_ranges0+0x40
	.uleb128 0x21
	.long	0x4d0
	.uleb128 0x21
	.long	0x4da
	.uleb128 0x22
	.long	0x3b5
	.quad	.LBB38
	.long	.Ldebug_ranges0+0x80
	.byte	0x1
	.byte	0x21
	.uleb128 0x17
	.long	0x3e6
	.uleb128 0x17
	.long	0x3db
	.uleb128 0x17
	.long	0x3d0
	.uleb128 0x17
	.long	0x3c6
	.byte	0x0
	.byte	0x0
	.byte	0x0
	.uleb128 0x1f
	.long	0x4a8
	.quad	.LBB43
	.long	.Ldebug_ranges0+0xb0
	.byte	0x1
	.byte	0x30
	.long	0x618
	.uleb128 0x17
	.long	0x4c7
	.uleb128 0x17
	.long	0x4be
	.uleb128 0x17
	.long	0x4b5
	.uleb128 0x20
	.long	.Ldebug_ranges0+0xe0
	.uleb128 0x21
	.long	0x4d0
	.uleb128 0x21
	.long	0x4da
	.uleb128 0x16
	.long	0x3b5
	.quad	.LBB45
	.quad	.LBE45
	.byte	0x1
	.byte	0x21
	.uleb128 0x17
	.long	0x3e6
	.uleb128 0x17
	.long	0x3db
	.uleb128 0x17
	.long	0x3d0
	.uleb128 0x17
	.long	0x3c6
	.byte	0x0
	.byte	0x0
	.byte	0x0
	.uleb128 0x1f
	.long	0x4a8
	.quad	.LBB48
	.long	.Ldebug_ranges0+0x110
	.byte	0x1
	.byte	0x31
	.long	0x67b
	.uleb128 0x17
	.long	0x4c7
	.uleb128 0x17
	.long	0x4be
	.uleb128 0x17
	.long	0x4b5
	.uleb128 0x20
	.long	.Ldebug_ranges0+0x140
	.uleb128 0x21
	.long	0x4d0
	.uleb128 0x21
	.long	0x4da
	.uleb128 0x16
	.long	0x3b5
	.quad	.LBB50
	.quad	.LBE50
	.byte	0x1
	.byte	0x21
	.uleb128 0x17
	.long	0x3e6
	.uleb128 0x17
	.long	0x3db
	.uleb128 0x17
	.long	0x3d0
	.uleb128 0x17
	.long	0x3c6
	.byte	0x0
	.byte	0x0
	.byte	0x0
	.uleb128 0x1f
	.long	0x4a8
	.quad	.LBB53
	.long	.Ldebug_ranges0+0x170
	.byte	0x1
	.byte	0x32
	.long	0x6de
	.uleb128 0x17
	.long	0x4c7
	.uleb128 0x17
	.long	0x4be
	.uleb128 0x17
	.long	0x4b5
	.uleb128 0x20
	.long	.Ldebug_ranges0+0x1a0
	.uleb128 0x21
	.long	0x4d0
	.uleb128 0x21
	.long	0x4da
	.uleb128 0x16
	.long	0x3b5
	.quad	.LBB55
	.quad	.LBE55
	.byte	0x1
	.byte	0x21
	.uleb128 0x17
	.long	0x3e6
	.uleb128 0x17
	.long	0x3db
	.uleb128 0x17
	.long	0x3d0
	.uleb128 0x17
	.long	0x3c6
	.byte	0x0
	.byte	0x0
	.byte	0x0
	.uleb128 0x23
	.long	0x42e
	.quad	.LBB58
	.quad	.LBE58
	.byte	0x1
	.byte	0x38
	.long	0x6ff
	.uleb128 0x17
	.long	0x441
	.byte	0x0
	.uleb128 0x22
	.long	0x3b5
	.quad	.LBB60
	.long	.Ldebug_ranges0+0x1d0
	.byte	0x1
	.byte	0x3a
	.uleb128 0x17
	.long	0x3e6
	.uleb128 0x17
	.long	0x3db
	.uleb128 0x17
	.long	0x3d0
	.uleb128 0x17
	.long	0x3c6
	.byte	0x0
	.byte	0x0
	.uleb128 0x1d
	.long	.LASF71
	.byte	0x1
	.byte	0x1a
	.long	0xd2
	.byte	0x9
	.byte	0x3
	.quad	num_ctrs
	.uleb128 0x24
	.long	.LASF72
	.byte	0x9
	.byte	0x91
	.long	0x313
	.byte	0x1
	.byte	0x1
	.uleb128 0x24
	.long	.LASF73
	.byte	0x9
	.byte	0x92
	.long	0x313
	.byte	0x1
	.byte	0x1
	.uleb128 0x25
	.long	.LASF74
	.byte	0x1
	.byte	0x19
	.long	0x360
	.byte	0x1
	.byte	0x9
	.byte	0x3
	.quad	__lp_stats
	.byte	0x0
	.section	.debug_abbrev
	.uleb128 0x1
	.uleb128 0x11
	.byte	0x1
	.uleb128 0x25
	.uleb128 0xe
	.uleb128 0x13
	.uleb128 0xb
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x1b
	.uleb128 0xe
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x1
	.uleb128 0x10
	.uleb128 0x6
	.byte	0x0
	.byte	0x0
	.uleb128 0x2
	.uleb128 0x16
	.byte	0x0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0x0
	.byte	0x0
	.uleb128 0x3
	.uleb128 0x1
	.byte	0x1
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x1
	.uleb128 0x13
	.byte	0x0
	.byte	0x0
	.uleb128 0x4
	.uleb128 0x21
	.byte	0x0
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2f
	.uleb128 0xb
	.byte	0x0
	.byte	0x0
	.uleb128 0x5
	.uleb128 0x24
	.byte	0x0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3e
	.uleb128 0xb
	.byte	0x0
	.byte	0x0
	.uleb128 0x6
	.uleb128 0x13
	.byte	0x1
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x1
	.uleb128 0x13
	.byte	0x0
	.byte	0x0
	.uleb128 0x7
	.uleb128 0xd
	.byte	0x0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x38
	.uleb128 0xa
	.byte	0x0
	.byte	0x0
	.uleb128 0x8
	.uleb128 0x24
	.byte	0x0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3e
	.uleb128 0xb
	.uleb128 0x3
	.uleb128 0xe
	.byte	0x0
	.byte	0x0
	.uleb128 0x9
	.uleb128 0xf
	.byte	0x0
	.uleb128 0xb
	.uleb128 0xb
	.byte	0x0
	.byte	0x0
	.uleb128 0xa
	.uleb128 0x24
	.byte	0x0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3e
	.uleb128 0xb
	.uleb128 0x3
	.uleb128 0x8
	.byte	0x0
	.byte	0x0
	.uleb128 0xb
	.uleb128 0xf
	.byte	0x0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0x0
	.byte	0x0
	.uleb128 0xc
	.uleb128 0xd
	.byte	0x0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x38
	.uleb128 0xa
	.byte	0x0
	.byte	0x0
	.uleb128 0xd
	.uleb128 0x16
	.byte	0x0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.byte	0x0
	.byte	0x0
	.uleb128 0xe
	.uleb128 0x26
	.byte	0x0
	.uleb128 0x49
	.uleb128 0x13
	.byte	0x0
	.byte	0x0
	.uleb128 0xf
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x27
	.uleb128 0xc
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x20
	.uleb128 0xb
	.uleb128 0x1
	.uleb128 0x13
	.byte	0x0
	.byte	0x0
	.uleb128 0x10
	.uleb128 0x5
	.byte	0x0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0x0
	.byte	0x0
	.uleb128 0x11
	.uleb128 0x5
	.byte	0x0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0x0
	.byte	0x0
	.uleb128 0x12
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0xc
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x27
	.uleb128 0xc
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x20
	.uleb128 0xb
	.uleb128 0x34
	.uleb128 0xc
	.uleb128 0x1
	.uleb128 0x13
	.byte	0x0
	.byte	0x0
	.uleb128 0x13
	.uleb128 0x18
	.byte	0x0
	.byte	0x0
	.byte	0x0
	.uleb128 0x14
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0xc
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x1
	.uleb128 0x40
	.uleb128 0x6
	.uleb128 0x1
	.uleb128 0x13
	.byte	0x0
	.byte	0x0
	.uleb128 0x15
	.uleb128 0x34
	.byte	0x0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x6
	.byte	0x0
	.byte	0x0
	.uleb128 0x16
	.uleb128 0x1d
	.byte	0x1
	.uleb128 0x31
	.uleb128 0x13
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x1
	.uleb128 0x58
	.uleb128 0xb
	.uleb128 0x59
	.uleb128 0xb
	.byte	0x0
	.byte	0x0
	.uleb128 0x17
	.uleb128 0x5
	.byte	0x0
	.uleb128 0x31
	.uleb128 0x13
	.byte	0x0
	.byte	0x0
	.uleb128 0x18
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x27
	.uleb128 0xc
	.uleb128 0x20
	.uleb128 0xb
	.uleb128 0x1
	.uleb128 0x13
	.byte	0x0
	.byte	0x0
	.uleb128 0x19
	.uleb128 0x34
	.byte	0x0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0x0
	.byte	0x0
	.uleb128 0x1a
	.uleb128 0x34
	.byte	0x0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0x0
	.byte	0x0
	.uleb128 0x1b
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0xc
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x27
	.uleb128 0xc
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x1
	.uleb128 0x40
	.uleb128 0x6
	.uleb128 0x1
	.uleb128 0x13
	.byte	0x0
	.byte	0x0
	.uleb128 0x1c
	.uleb128 0x5
	.byte	0x0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x6
	.byte	0x0
	.byte	0x0
	.uleb128 0x1d
	.uleb128 0x34
	.byte	0x0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0xa
	.byte	0x0
	.byte	0x0
	.uleb128 0x1e
	.uleb128 0x34
	.byte	0x0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x6
	.byte	0x0
	.byte	0x0
	.uleb128 0x1f
	.uleb128 0x1d
	.byte	0x1
	.uleb128 0x31
	.uleb128 0x13
	.uleb128 0x52
	.uleb128 0x1
	.uleb128 0x55
	.uleb128 0x6
	.uleb128 0x58
	.uleb128 0xb
	.uleb128 0x59
	.uleb128 0xb
	.uleb128 0x1
	.uleb128 0x13
	.byte	0x0
	.byte	0x0
	.uleb128 0x20
	.uleb128 0xb
	.byte	0x1
	.uleb128 0x55
	.uleb128 0x6
	.byte	0x0
	.byte	0x0
	.uleb128 0x21
	.uleb128 0x34
	.byte	0x0
	.uleb128 0x31
	.uleb128 0x13
	.byte	0x0
	.byte	0x0
	.uleb128 0x22
	.uleb128 0x1d
	.byte	0x1
	.uleb128 0x31
	.uleb128 0x13
	.uleb128 0x52
	.uleb128 0x1
	.uleb128 0x55
	.uleb128 0x6
	.uleb128 0x58
	.uleb128 0xb
	.uleb128 0x59
	.uleb128 0xb
	.byte	0x0
	.byte	0x0
	.uleb128 0x23
	.uleb128 0x1d
	.byte	0x1
	.uleb128 0x31
	.uleb128 0x13
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x1
	.uleb128 0x58
	.uleb128 0xb
	.uleb128 0x59
	.uleb128 0xb
	.uleb128 0x1
	.uleb128 0x13
	.byte	0x0
	.byte	0x0
	.uleb128 0x24
	.uleb128 0x34
	.byte	0x0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x3f
	.uleb128 0xc
	.uleb128 0x3c
	.uleb128 0xc
	.byte	0x0
	.byte	0x0
	.uleb128 0x25
	.uleb128 0x34
	.byte	0x0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x3f
	.uleb128 0xc
	.uleb128 0x2
	.uleb128 0xa
	.byte	0x0
	.byte	0x0
	.byte	0x0
	.section	.debug_pubnames,"",@progbits
	.long	0x3c
	.value	0x2
	.long	.Ldebug_info0
	.long	0x76e
	.long	0x44e
	.string	"lprof_close"
	.long	0x4e6
	.string	"lprof_init"
	.long	0x757
	.string	"__lp_stats"
	.long	0x0
	.section	.debug_aranges,"",@progbits
	.long	0x2c
	.value	0x2
	.long	.Ldebug_info0
	.byte	0x8
	.byte	0x0
	.value	0x0
	.value	0x0
	.quad	.Ltext0
	.quad	.Letext0-.Ltext0
	.quad	0x0
	.quad	0x0
	.section	.debug_ranges,"",@progbits
.Ldebug_ranges0:
	.quad	.LBB34-.Ltext0
	.quad	.LBE34-.Ltext0
	.quad	.LBB64-.Ltext0
	.quad	.LBE64-.Ltext0
	.quad	.LBB42-.Ltext0
	.quad	.LBE42-.Ltext0
	.quad	0x0
	.quad	0x0
	.quad	.LBB36-.Ltext0
	.quad	.LBE36-.Ltext0
	.quad	.LBB41-.Ltext0
	.quad	.LBE41-.Ltext0
	.quad	.LBB35-.Ltext0
	.quad	.LBE35-.Ltext0
	.quad	0x0
	.quad	0x0
	.quad	.LBB38-.Ltext0
	.quad	.LBE38-.Ltext0
	.quad	.LBB37-.Ltext0
	.quad	.LBE37-.Ltext0
	.quad	0x0
	.quad	0x0
	.quad	.LBB43-.Ltext0
	.quad	.LBE43-.Ltext0
	.quad	.LBB65-.Ltext0
	.quad	.LBE65-.Ltext0
	.quad	0x0
	.quad	0x0
	.quad	.LBB44-.Ltext0
	.quad	.LBE44-.Ltext0
	.quad	.LBB47-.Ltext0
	.quad	.LBE47-.Ltext0
	.quad	0x0
	.quad	0x0
	.quad	.LBB48-.Ltext0
	.quad	.LBE48-.Ltext0
	.quad	.LBB66-.Ltext0
	.quad	.LBE66-.Ltext0
	.quad	0x0
	.quad	0x0
	.quad	.LBB49-.Ltext0
	.quad	.LBE49-.Ltext0
	.quad	.LBB52-.Ltext0
	.quad	.LBE52-.Ltext0
	.quad	0x0
	.quad	0x0
	.quad	.LBB53-.Ltext0
	.quad	.LBE53-.Ltext0
	.quad	.LBB67-.Ltext0
	.quad	.LBE67-.Ltext0
	.quad	0x0
	.quad	0x0
	.quad	.LBB54-.Ltext0
	.quad	.LBE54-.Ltext0
	.quad	.LBB57-.Ltext0
	.quad	.LBE57-.Ltext0
	.quad	0x0
	.quad	0x0
	.quad	.LBB60-.Ltext0
	.quad	.LBE60-.Ltext0
	.quad	.LBB63-.Ltext0
	.quad	.LBE63-.Ltext0
	.quad	0x0
	.quad	0x0
	.section	.debug_str,"MS",@progbits,1
.LASF35:
	.string	"_old_offset"
.LASF37:
	.string	"_vtable_offset"
.LASF18:
	.string	"_IO_FILE"
.LASF79:
	.string	"sys_lprof_config"
.LASF30:
	.string	"_IO_save_end"
.LASF12:
	.string	"short int"
.LASF6:
	.string	"size_t"
.LASF40:
	.string	"_offset"
.LASF63:
	.string	"__ch"
.LASF71:
	.string	"num_ctrs"
.LASF19:
	.string	"_flags"
.LASF26:
	.string	"_IO_buf_base"
.LASF77:
	.string	"/home/df2417/sap_sam/lprof-snapshot-r63/src"
.LASF39:
	.string	"_lock"
.LASF17:
	.string	"__va_list_tag"
.LASF56:
	.string	"context_switches"
.LASF31:
	.string	"_markers"
.LASF60:
	.string	"config"
.LASF5:
	.string	"va_list"
.LASF70:
	.string	"conf"
.LASF74:
	.string	"__lp_stats"
.LASF65:
	.string	"memset"
.LASF13:
	.string	"long int"
.LASF62:
	.string	"__dest"
.LASF81:
	.string	"registerCS"
.LASF57:
	.string	"timer_interrupts"
.LASF36:
	.string	"_cur_column"
.LASF0:
	.string	"gp_offset"
.LASF76:
	.string	"lprof.c"
.LASF54:
	.string	"lprof_stats"
.LASF9:
	.string	"unsigned char"
.LASF59:
	.string	"counter"
.LASF11:
	.string	"signed char"
.LASF53:
	.string	"uint64_t"
.LASF61:
	.string	"long long unsigned int"
.LASF1:
	.string	"fp_offset"
.LASF7:
	.string	"unsigned int"
.LASF48:
	.string	"_IO_marker"
.LASF38:
	.string	"_shortbuf"
.LASF69:
	.string	"args"
.LASF21:
	.string	"_IO_read_end"
.LASF23:
	.string	"_IO_write_base"
.LASF47:
	.string	"_unused2"
.LASF58:
	.string	"last"
.LASF20:
	.string	"_IO_read_ptr"
.LASF51:
	.string	"_pos"
.LASF27:
	.string	"_IO_buf_end"
.LASF3:
	.string	"reg_save_area"
.LASF82:
	.string	"lprof_init"
.LASF16:
	.string	"char"
.LASF66:
	.string	"printf"
.LASF49:
	.string	"_next"
.LASF41:
	.string	"__pad1"
.LASF42:
	.string	"__pad2"
.LASF43:
	.string	"__pad3"
.LASF44:
	.string	"__pad4"
.LASF45:
	.string	"__pad5"
.LASF80:
	.string	"lprof_close"
.LASF10:
	.string	"short unsigned int"
.LASF67:
	.string	"__fmt"
.LASF8:
	.string	"long unsigned int"
.LASF24:
	.string	"_IO_write_ptr"
.LASF25:
	.string	"_IO_write_end"
.LASF15:
	.string	"__off64_t"
.LASF2:
	.string	"overflow_arg_area"
.LASF52:
	.string	"int64_t"
.LASF33:
	.string	"_fileno"
.LASF32:
	.string	"_chain"
.LASF14:
	.string	"__off_t"
.LASF29:
	.string	"_IO_backup_base"
.LASF72:
	.string	"stdin"
.LASF55:
	.string	"rdpmc_inprogress"
.LASF34:
	.string	"_flags2"
.LASF46:
	.string	"_mode"
.LASF22:
	.string	"_IO_read_base"
.LASF4:
	.string	"__gnuc_va_list"
.LASF64:
	.string	"__len"
.LASF28:
	.string	"_IO_save_base"
.LASF75:
	.string	"GNU C 4.4.3"
.LASF50:
	.string	"_sbuf"
.LASF73:
	.string	"stdout"
.LASF78:
	.string	"_IO_lock_t"
.LASF68:
	.string	"cs_len"
	.ident	"GCC: (Ubuntu 4.4.3-4ubuntu5) 4.4.3"
	.section	.note.GNU-stack,"",@progbits
