	.text	

	.global test
	.type test, @function
	.global lp
	.global lp_end
test:
	mov $0, %rbx
beg:	mov $1, %rax
	mov $1, %rdx
	mov $1, %rcx
lp:	
loop:	cmp $800000000, %rbx
	je done
	addq $1, %rbx
	cmp $1, %rdx
	jne hit
	cmp $1, %rax
	jne hit
	jmp loop
hit:
lp_end:
	movq %rbx, %rdi
	callq hitClear
	jmp beg
	
done:	ret
	.size	test1, .-test1
	
	.ident	"GCC: (Ubuntu 4.4.3-4ubuntu5) 4.4.3"
	.section	.note.GNU-stack,"",@progbits
	
