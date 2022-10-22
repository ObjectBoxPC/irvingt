#C compiler
CC=gcc

#Result file
TARGET=irvingt.a

#Test executable
TEST_TARGET=test/irvingt-test.bin

#Archive creator
AR=ar

#Objects to compile
OBJS=irvingt.o irvingt-real.o irvingt-proc.o

#Objects to compile for testing
TEST_OBJS=test/irvingt-test.o test/irvingt-test-call.o

#C compiler flags
CFLAGS=-m32 -Wall -Wextra -std=c99 -pedantic -O2 -g -D_POSIX_C_SOURCE=199309L

#Linking flags for testing
TEST_LINKFLAGS=-m32 -z noexecstack -lcmocka

all: $(TARGET)

$(TARGET): $(OBJS)
	$(AR) rcs $(TARGET) $(OBJS)

$(TEST_TARGET): $(OBJS) $(TEST_OBJS)
	$(CC) -o $@ $(OBJS) $(TEST_OBJS) $(TEST_LINKFLAGS)

.SUFFIXES: .c .S .o

.c.o:
	$(CC) -c $(CFLAGS) -o $@ $<

.S.o:
	$(CC) -c $(CFLAGS) -o $@ $<

.PHONY: clean test

clean:
	rm -f $(TARGET) $(TEST_TARGET) $(OBJS) $(TEST_OBJS)

test: $(TEST_TARGET)
	$(TEST_TARGET)
