.text

#ifndef IRVINGT_HAVE_ALONG
.globl DumpRegs
.type DumpRegs, @function

DumpRegs:
	pushal
	pushfl

	#Save return address (EIP) from stack
	#Nine 32-bit registers were pushed after the return address
	pushl 36(%esp)

	call DumpRegs_Real

	#Remove return address from stack
	addl $4, %esp

	popfl
	popal

	ret
#endif

.globl WaitMsg
.type WaitMsg, STT_FUNC

WaitMsg:
	pushal
	pushfl

	call WaitMsg_Real

	popfl
	popal

	ret