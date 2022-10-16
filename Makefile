#C compiler
CC=gcc

#Result file
TARGET=irvingt.a

#Archive creator
AR=ar

#Objects to compile
OBJS=irvingt.o irvingt-real.o irvingt-proc.o

#C compiler flags
CFLAGS=-m32 -Wall -Wextra -std=gnu89 -O2 -g

all: $(TARGET)

$(TARGET): $(OBJS)
	$(AR) rcs $(TARGET) $(OBJS)

.SUFFIXES: .c .S .o

.c.o:
	$(CC) -c $(CFLAGS) -o $@ $<

.S.o:
	$(CC) -c $(CFLAGS) -o $@ $<

.PHONY: clean

clean:
	rm -f $(TARGET) $(OBJS)
