#include <stdio.h>
#include <stdlib.h>

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
 */

/**
 * Integer representing an invalid file handle (`INVALID_HANDLE_VALUE`
 * in Irvine32).
 * @see CreateOutputFile_Real
 */
const int IRVINGT_INVALID_HANDLE = -1;

/**
 * Close a file handle.
 * @param handle (EAX) Handle to close
 * @return (EAX) Nonzero if the file was closed successfully, zero otherwise
 * @see CreateOutputFile_Real
 */
int CloseFile_Real(int handle) {
	if((handle != IRVINGT_INVALID_HANDLE) && (!fclose((FILE*) handle))) {
		return 1;
	} else {
		return 0;
	}
}

/**
 * Create a file for output.
 * @param filename (EDX) Filename as a null-terminated string
 * @return (EAX) File handle, or `INVALID_HANDLE_VALUE` if the file could not
 * be created
 * @see WriteToFile_Real, CloseFile_Real
 */
int CreateOutputFile_Real(const char* filename) {
	FILE* file = fopen(filename, "wb");
	if(file) {
		return (int) file;
	} else {
		return IRVINGT_INVALID_HANDLE;
	}
}

/**
 * Advance to the next line in the terminal by writing a newline.
 */
#ifndef IRVINGT_HAVE_ALONG
void Crlf_Real(void) {
	puts("");
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

/**
 * Write data to a file.
 * @param handle (EAX) File handle
 * @param buf (EDX) Buffer
 * @param count (ECX) Number of bytes to write
 * @return (EAX) Number of bytes written, or zero if an error occurred
 */
unsigned int WriteToFile_Real(FILE* handle, const char* buf, unsigned int count) {
	return (unsigned int) fwrite(buf, 1, count, handle);
}