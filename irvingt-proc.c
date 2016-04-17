#include <stdio.h>
#include <stdlib.h>

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