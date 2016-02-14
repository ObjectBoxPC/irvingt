# IrvingT

IrvingT is a port of the Irvine32 library, used in *Assembly Language for x86 Processors* by Kip Irvine, for Unix-like systems (Linux, BSD, etc.). This library is one piece of the puzzle of working with programs in the textbook on Unix-like systems. (For the full puzzle, read `PUZZLE.md`.)

Unlike [Along32](https://sourceforge.net/projects/jwasm/), a Linux port of Irvine32, IrvingT uses the C standard library, rather than system calls, so it is portable to other Unix-like systems. Also, IrvingT provides an emulation of the Windows `ExitProcess` function, which is required by the `exit` macro in Irvine32.

## Compiling

Simply run `make` to get a static library called `irvingt.a` in the current directory.

### Irving/Along

Even though one goal of IrvingT is to overcome the portability problems of Along32, you can combine IrvingT and Along32 into "Irving/Along." In this case, IrvingT will supply only those functions that are not provided by Along32.

An additional makefile, `Makefile-IrvingAlong`, is provided for this purpose. Edit the file and change the Along32 source directory. Then run `make -f Makefile-IrvingAlong` to get a static library called `irvingalong.a` in the current directory.

## Tested Environments

IrvingT has been tested on the following platforms with GCC and Clang:

* x86-64 GNU/Linux (with 32-bit development files, sometimes called "multilib")
* x86 FreeBSD
* x86 OpenBSD
