# The Puzzle

*Assembly Language for x86 Processors* by Kip Irvine is centered around Microsoft Windows and MASM. However, with some effort, it is possible to assemble programs in the textbook unmodified on Unix-like systems.

## Part A: Obtain a MASM-Compatible Assembler

The only such assembler I could find is [JWasm](https://sourceforge.net/projects/jwasm/).

A Linux binary is provided, so you can use it right away on a Linux system. On other systems, you will have to compile it yourself.

### Compile JWasm

1. Download the source code. (Updated source code seems to be on [GitHub](https://github.com/JWasm/JWasm).)
2. Install a suitable compiler (GCC or Clang), if one is not already installed.
3. Install GNU make. The `make` provided on BSD systems will likely not work because the makefiles rely on GNU extensions. On FreeBSD and OpenBSD, GNU make is provided as a package called `gmake`.
4. If you use Clang, edit the `GccUnix.mak` file and change the line:

		CC = gcc

	to:

		CC = clang

5. Run `make -f GccUnix.mak`. (Replace `make` with `gmake` if necessary.) The compiled binary will appear in the `GccUnixR` directory.

## Part B: Compile IrvingT

Instructions are in `README.md`.

## Part C: Download the Irvine32 Include Files

Go to the [regular download page](http://kipirvine.com/asm/examples/index.htm) and download the files for the *5th Edition, using Visual Studio 2008*. This is the last version that is provided in a ZIP file rather than an MSI installer, and it should still work.

If you really want the latest version, you can use `msiextract` from [msitools](https://wiki.gnome.org/msitools), available in the repositories of some GNU/Linux distributions. If your system does not provide msitools, you can compile it yourself, but I'd suggest that you not go through the hassle.

## Part D: Change the Irvine32 Include Files

In the `SmallWin.inc` file provided with Irvine32, change the line:

	.MODEL flat, stdcall

to:

	.MODEL flat, c

## Part E: Assemble MASM Files

Run JWasm with the options `-I[Irvine32 directory] -zcw -elf`:

	jwasm -I[Irvine32 directory] -zcw -elf [ASM file]

(This assumes you have JWasm in your `PATH`.)

(Strangely, the `-I` option is not in the manual, but it is in the option listing from `jwasm -?`.)

## Part F: Link the Files with IrvingT

Use a C compiler such as GCC or Clang to link. The ensures that the C standard library is linked properly:

	gcc -o [output file] [ASM file] [IrvingT static library]