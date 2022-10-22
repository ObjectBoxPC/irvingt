.globl irvingt_test_call
.type irvingt_test_call, @function

irvingt_test_call:
	pushal

	movl 40(%esp), %eax

	movl 12(%eax), %edx
	movl 8(%eax), %ecx
	movl 4(%eax), %ebx
	movl (%eax), %eax

	call *36(%esp)

	pushl %eax
	pushl %ebx
	pushl %ecx
	pushl %edx

	movl 56(%esp), %eax

	popl 12(%eax)
	popl 8(%eax)
	popl 4(%eax)
	popl (%eax)

	popal
	ret