#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include <stddef.h>

/**
 * @file
 * "Real" IrvingT functions.
 * These functions do most of the work. They have names of the form
 * `[Irvine32 function]_Real`. The functions with the actual names from Irvine32
 * are in `irvingt.S`. Those simply save the registers and flags, and
 * transform the parameters passed in registers into the cdecl calling
 * convention, which is standard in Unix-like systems for C functions.
 *
 * For convenience, all the documentation is in this file. Each parameter lists
 * the register in which it should be passed.
 *
 * @copyright Copyright (c) 2016 Philip Chung
 * <https://bitbucket.org/philipchungtech/irvingt>
 * All rights reserved.
 * Available under the 2-clause BSD license (refer to `LICENSE.txt`
 * for details).
 */

/**
 * Advance to the next line in the terminal by writing a newline.
 */
#ifndef IRVINGT_HAVE_ALONG
void Crlf_Real(void) {
	puts("");
}
#endif

/**
 * Display memory contents, organized in byte, word, or doubleword units.
 * @param addr (ESI) Memory address
 * @param count (ECX) Number of units to display
 * @param size (EBX) Unit size (1 = byte, 2 = word, 4 = doubleword)
 */
#ifndef IRVINGT_HAVE_ALONG
void DumpMem_Real(void* addr, unsigned int count, unsigned int size) {
	unsigned int* data_dword = addr;
	unsigned short* data_word = addr;
	unsigned char* data_byte = addr;
	unsigned int i;

	puts("");
	printf("Dump of offset %.8X\n", (int) addr);
	puts("-------------------------------");
	switch(size) {
	case 4:
		for(i = 0; i < count; i++) {
			printf("%.8X  ", data_dword[i]);
		}
		break;
	case 2:
		for(i = 0; i < count; i++) {
			printf("%.4X ", data_word[i]);
		}
		break;
	case 1:
		/* Bytes are the default */
	default:
		for(i = 0; i < count; i++) {
			printf("%.2X ", data_byte[i]);
			if((i + 1) % 16 == 0) {
				puts("");
			}
		}
	}
	puts("");
}
#endif

/**
 * Pause the program temporarily.
 * @param msecs (EAX) Time to pause for, in milliseconds
 */
#ifndef IRVINGT_HAVE_ALONG
void Delay_Real(unsigned int msecs) {
	struct timespec spec;

	spec.tv_sec = msecs / 1000;
	spec.tv_nsec = (msecs % 1000) * 1000;
	nanosleep(&spec, NULL);
}
#endif

/**
 * Display the contents of the registers and selected flags.
 * The ordering of parameters is due to the order in which the PUSHAD
 * instruction pushes the registers. This function steals those values and uses
 * them as parameters.
 * @param eip, efl, edi, esi, ebp, esp, ebx, edx, ecx, eax Registers
 */
#ifndef IRVINGT_HAVE_ALONG
void DumpRegs_Real(int eip, int efl, int edi, int esi, int ebp, int esp, int ebx, int edx, int ecx, int eax) {
	int cf, sf, zf, of, af, pf;

	/* Extract flags */
	cf = !!(efl & (1 << 0));
	sf = !!(efl & (1 << 7));
	zf = !!(efl & (1 << 6));
	of = !!(efl & (1 << 11));
	af = !!(efl & (1 << 4));
	pf = !!(efl & (1 << 2));

	/* Print */
	puts("");
	printf("  EAX=%.8X  EBX=%.8X  ECX=%.8X  EDX=%.8X\n", eax, ebx, ecx, edx);
	printf("  ESI=%.8X  EDI=%.8X  EBP=%.8X  ESP=%.8X\n", esi, edi, ebp, esp);
	printf(
		"  EIP=%.8X  EFL=%.8X  CF=%d  SF=%d  ZF=%d  OF=%d  AF=%d  PF=%d\n",
		eip, efl, cf, sf, zf, of, af, pf
	);
	puts("");
}
#endif

/**
 * Exit the program with the given status.
 * This function is not part of Irvine32; it is a Windows API function. However,
 * it is included because Irvine32 uses it as part of its "exit" macro.
 * @param status Status code
 */
void ExitProcess(int status) {
	puts("Exit");
	exit(status);
}

#ifndef IRVINGT_HAVE_ALONG
/**
 * Read an unsigned integer.
 * @param carry (CF: least significant bit) Set if the integer is empty,
 * consists of only blanks, or is too large to fit in a doubleword;
 * cleared otherwise.
 * @return (EAX) The integer read, or zero on error
 * @note Not all errors cause the carry flag to be set.
 */
unsigned int ReadDec_Real(int* carry) {
	int c;
	char num_str[21]; /* All 32-bit integers can fit into less than 20 chars.*/

	while((c = getchar()) != EOF && c != '\n' && isspace(c)) {
		/* Skip spaces */
	}
	if(c == '\n' || c == EOF) {
		/* End of empty line or line consisting of only spaces */
		*carry = 1;
		return 0;
	} else {
		ungetc(c, stdin);
		if(scanf("%20[0123456789]*[^\n]%*1[\n]", num_str) == 1) {
			/* Got an unsigned integer */
			int errno_old = errno;
			unsigned long num;

			num = strtoul(num_str, NULL, 10);
			if(errno == ERANGE) {
				*carry = 1;
				num = 0;
			} else {
				*carry = 0;
			}
			errno = errno_old;
			return num;
		} else {
			/* Did not get an unsigned integer */
			/* Ignore the rest of the line */
			scanf("%*[^\n]%*1[\n]");
			*carry = 0;
			return 0;
		}
	}
}
#endif

/**
 * Find the length of a null-terminated string.
 * @param str (EDX) String
 * @return (EAX) Length
 */
unsigned int StrLength_Real(const char* str) {
	return (unsigned int) strlen(str);
}

/**
 * Pause the program and wait for user input.
 */
void WaitMsg_Real(void) {
	puts("Press Enter to continue...");
	getchar();
}

/**
 * Output a character.
 * @param c (AL) Character to write.
 * @note The argument is an `int` rather than a `char` because in reality
 * the entirety of EAX is passed to this function because of alignment
 * requirements.
 */
#ifndef IRVINGT_HAVE_ALONG
void WriteChar_Real(unsigned int c) {
	unsigned char c_real = c & 0xFF;
	printf("%c", c_real);
	fflush(stdout);
}
#endif

/**
 * Output an unsigned 32-bit integer in decimal.
 * @param x (EAX) Integer to write
 */
#ifndef IRVINGT_HAVE_ALONG
void WriteDec_Real(unsigned int x) {
	printf("%u", x);
	fflush(stdout);
}
#endif

/**
 * Output an unsigned 32-bit integer in hexadecimal.
 * @param x (EAX) Integer to write
 */
#ifndef IRVINGT_HAVE_ALONG
void WriteHex_Real(unsigned int x) {
	printf("%.8X", x);
	fflush(stdout);
}
#endif

/**
 * Output a signed 32-bit integer in decimal with leading sign.
 * @param x (EAX) Integer to write
 */
#ifndef IRVINGT_HAVE_ALONG
void WriteInt_Real(unsigned int x) {
	printf("%+d", x);
	fflush(stdout);
}
#endif

/**
 * Output a null-terminated string.
 * @param str (EDX) Starting address of string to output
 */
#ifndef IRVINGT_HAVE_ALONG
void WriteString_Real(const char* str) {
	printf("%s", str);
	fflush(stdout);
}
#endif