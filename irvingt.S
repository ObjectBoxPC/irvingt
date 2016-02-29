#This file is part of IrvingT <https://bitbucket.org/philipchungtech/irvingt>
#Copyright (c) 2016 Philip Chung. All rights reserved.
#Available under the 2-clause BSD license (refer to `LICENSE.txt` for details)

.data

ret_val: .int

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

.globl StrLength
.type StrLength, @function

StrLength:
	pushfl
	pushal

	pushl %edx
	call StrLength_Real
	addl $4, %esp

	movl %eax, ret_val
	popal
	popfl
	movl ret_val, %eax

	ret

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