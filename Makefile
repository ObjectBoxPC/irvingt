#C compiler
CC=gcc

#Result file
TARGET=irvingt.a

#Archive creator
AR=ar

#Objects to compile
OBJS=irvingt.o irvingt-real.o

#C compiler flags
CFLAGS=-m32 -Wall -Wextra -std=gnu90 -O2 -g

all: $(TARGET)

$(TARGET): $(OBJS)
	$(AR) rcs $(TARGET) $(OBJS)

.SUFFIXES: .c .o

.c.o:
	$(CC) -c $(CFLAGS) -o $@ $<

.S.o:
	$(CC) -c $(CFLAGS) -o $@ $<

.PHONY: clean

clean:
	rm -f $(TARGET) $(OBJS)
