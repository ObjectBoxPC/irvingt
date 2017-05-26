#This file is part of IrvingT <https://github.com/philipchungtech/irvingt>
#Copyright (c) 2016-2017 Philip Chung. All rights reserved.
#Available under the 2-clause BSD license (refer to `LICENSE.txt` for details)

.data

ret_val: .int 0
ret_extra: .int 0

.text

.globl CloseFile
.type CloseFile, @function

CloseFile:
	pushal
	pushfl

	pushl %eax
	call CloseFile_Real
	addl $4, %esp

	movl %eax, ret_val
	popfl
	popal
	movl ret_val, %eax

	ret

.globl CreateOutputFile
.type CreateOutputFile, @function

CreateOutputFile:
	pushal
	pushfl

	pushl %edx
	call CreateOutputFile_Real
	addl $4, %esp

	movl %eax, ret_val
	popfl
	popal
	movl ret_val, %eax

	ret

#ifndef IRVINGT_HAVE_ALONG
.globl Clrscr
.type Clrscr, @function

Clrscr:
	pushal
	pushfl

	call Clrscr_Real

	popfl
	popal

	ret
#endif

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
.globl DumpMem
.type DumpMem, @function

DumpMem:
	pushal
	pushfl

	pushl %ebx
	pushl %ecx
	pushl %esi
	call DumpMem_Real
	addl $12, %esp

	popfl
	popal

	ret
#endif

#ifndef IRVINGT_HAVE_ALONG
.globl Delay
.type Delay, @function

Delay:
	pushal
	pushfl

	pushl %eax
	call Delay_Real
	addl $4, %esp

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

.globl OpenInputFile
.type OpenInputFile, @function

OpenInputFile:
	pushal
	pushfl

	pushl %edx
	call OpenInputFile_Real
	addl $4, %esp

	movl %eax, ret_val
	popfl
	popal
	movl ret_val, %eax

	ret

.globl ReadFromFile
.type ReadFromFile, @function

ReadFromFile:
	pushal
	pushfl

	pushl $ret_extra
	pushl %ecx
	pushl %edx
	pushl %eax
	call ReadFromFile_Real
	addl $16, %esp

	movl %eax, ret_val
	popfl
	popal
	movl ret_val, %eax
	btl $0, ret_extra

	ret

.globl StrLength
.type StrLength, @function

StrLength:
	pushal
	pushfl

	pushl %edx
	call StrLength_Real
	addl $4, %esp

	movl %eax, ret_val
	popfl
	popal
	movl ret_val, %eax

	ret

.globl WaitMsg
.type WaitMsg, @function

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

.globl WriteToFile
.type WriteToFile, @function

WriteToFile:
	pushal
	pushfl

	pushl %ecx
	pushl %edx
	pushl %eax
	call WriteToFile_Real
	addl $12, %esp

	mov %eax, ret_val
	popfl
	popal
	mov ret_val, %eax

	ret