.text

#ifndef IRVINGT_HAVE_ALONG
.globl Crlf
.type Crlf, @function

Crlf:
	pushal
	pushfl

	call Crlf_Real

	popfl
	popal

	ret
#endif

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

#ifndef IRVINGT_HAVE_ALONG
.globl WriteChar
.type WriteChar, @function

WriteChar:
	pushal
	pushfl

	#Push the entire EAX for alignment reasons
	pushl %eax
	call WriteChar_Real
	addl $4, %esp

	popfl
	popal

	ret
#endif

#ifndef IRVINGT_HAVE_ALONG
.globl WriteDec
.type WriteDec, @function

WriteDec:
	pushal
	pushfl

	pushl %eax
	call WriteDec_Real
	addl $4, %esp

	popfl
	popal

	ret
#endif

#ifndef IRVINGT_HAVE_ALONG
.globl WriteHex
.type WriteHex, @function

WriteHex:
	pushal
	pushfl

	pushl %eax
	call WriteHex_Real
	addl $4, %esp

	popfl
	popal

	ret
#endif

#ifndef IRVINGT_HAVE_ALONG
.globl WriteInt
.type WriteInt, @function

WriteInt:
	pushal
	pushfl

	pushl %eax
	call WriteInt_Real
	addl $4, %esp

	popfl
	popal

	ret
#endif

#ifndef IRVINGT_HAVE_ALONG
.globl WriteString
.type WriteString, @function

WriteString:
	pushal
	pushfl

	pushl %edx
	call WriteString_Real
	addl $4, %esp

	popfl
	popal

	ret
#endif