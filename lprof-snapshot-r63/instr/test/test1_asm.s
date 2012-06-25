	.text	

	.global test1
	.type test1, @function
test1:
	mov $0, %rax
lp:	cmp $80000000, %rax
	je done
	addq $1, %rax
	jmp lp
	
	call foo
done:	ret
	.size	test1, .-test1
	
	.global foo
	.type foo, @function
foo:
	nop
	nop
	ret

	.size	foo, .-foo

	
	.ident	"GCC: (Ubuntu 4.4.3-4ubuntu5) 4.4.3"
	.section	.note.GNU-stack,"",@progbits
	
