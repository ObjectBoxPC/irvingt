#include <stdio.h>
#include <stdlib.h>

/**
 * @file
 * "ExitProcess" implementation
 *
 * @copyright Copyright (c) 2016-2017 Philip Chung
 * <https://github.com/philipchungtech/irvingt>
 * All rights reserved.
 * Available under the 2-clause BSD license (refer to `LICENSE.txt`
 * for details).
 */

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