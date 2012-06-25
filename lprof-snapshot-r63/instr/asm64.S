.text
	
	.global dummy_nocall_end
dummy_nocall_end:
	retq

	.global __func_info
__func_info:
	nop

	.global __stats
__stats:
	nop

# Locations in stats struct
#define inprog  (__stats+0)	
#define	ctxt_sw (__stats+8)
#define	ints    (__stats+16)
#define	gpcount (__stats+32)

# Offsets into Result struct
#define	pcount    (__func_info+16)
#define	ccount    (__func_info+24)
#define	icount    (__func_info+32)
#define int_count (__func_info+40)
#define cs_count  (__func_info+48)

	.global func_entry64
	.global func_entry64_cs_begin
	.global func_entry64_cs_end
func_entry64:
	#  Push registers we are going to destroy
 	push	%rax
	push	%rcx
	push	%rdx

	# Update callee's call and inc counts
	addq    $1, ccount

	#Reset context switch and interrupt counters
	movq	$0, ctxt_sw
	movq	$0, ints

	mfence

	# Configure for RDPMC, sample, and join to 64-bit
func_entry64_cs_begin:			# Begin critical section
	mov	$1,   %rcx
	nop
	nop
	shl	$32,  %rdx
	orq	%rax, %rdx

	# Set the global counter
	movq	%rdx, gpcount
func_entry64_cs_end:			# End critical section

	pop	%rdx
	pop	%rcx
	pop	%rax

	#Snippet end
	callq   dummy_nocall_end
	

	.global func_rentry64
	.global func_rentry64_cs_begin
	.global func_rentry64_cs_end
func_rentry64:
	mfence
	#  Push registers we are going to destroy
 	push	%rax
	push	%rcx
	push	%rdx

	#Reset context switch and interrupt counters
	movq	$0, ctxt_sw
	movq	$0, ints

	# Configure for RDPMC, sample, and join to 64-bit
func_rentry64_cs_begin:			# Begin critical section
	mov	$1,   %rcx
	nop
	nop
	shl	$32,  %rdx
	orq	%rax, %rdx

	# Subtract global counter
	movq	%rdx, gpcount
func_rentry64_cs_end:			# End critical section	

	pop	%rdx
	pop	%rcx
	pop	%rax

	#Snippet end
	callq   dummy_nocall_end

	
	.global func_exit64
	.global func_exit64_cs_begin
	.global func_exit64_cs_end
func_exit64:
	mfence

	#  Push registers we are going to destroy
 	push	%rax
	push	%rcx
	push	%rdx
	
	# Configure for RDPMC, sample, and join to 64-bit
func_exit64_cs_begin:			# Begin critical section
	mov	$1,   %rcx
	nop
	nop
	shl	$32,  %rdx
	orq	%rax, %rdx

	# Subtract global counter
	subq	gpcount, %rdx
func_exit64_cs_end:			# End critical section	

	# Update caller's stats
	addq	%rdx, pcount		# Increment caller's pcount
	
	# Increment the various counters
	addq	$1, icount
	movq	ints, %rdx
	addq	%rdx, int_count
	movq	ctxt_sw, %rdx
	addq	%rdx, cs_count

	# Pop back used values
	pop	%rdx
	pop	%rcx
	pop	%rax

	#Snippet end
	callq   dummy_nocall_end
