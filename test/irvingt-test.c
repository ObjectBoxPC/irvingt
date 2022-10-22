#include "irvingt-funcs.h"
#include <setjmp.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <cmocka.h>

#define IRVINGT_TEST_PATH_MAX 1024

struct register_state {
	int eax;
	int ebx;
	int ecx;
	int edx;
};

struct test_state {
	struct register_state registers;
	char tmp_dir[IRVINGT_TEST_PATH_MAX];
};

void irvingt_test_call(void (*irvingt_func)(void), struct register_state* registers);

static int setup(void** state) {
	struct test_state* new_state;
	struct register_state registers = { 0 };
	char tmp_dir[IRVINGT_TEST_PATH_MAX] = "/tmp/irvingt_testXXXXXX";

	if (!mkdtemp(tmp_dir)) {
		return -1;
	}

	new_state = malloc(sizeof(*new_state));
	if (!new_state) {
		rmdir(tmp_dir);
		return -1;
	}

	memcpy(&new_state->registers, &registers, sizeof(registers));
	memcpy(&new_state->tmp_dir, &tmp_dir, sizeof(tmp_dir));
	*state = new_state;
	return 0;
}

static int teardown(void** state) {
	struct test_state* test_state = *state;

	rmdir(test_state->tmp_dir);
	free(test_state);
	return 0;
}

static void StrLength_can_compute(void** state) {
	struct test_state* test_state = *state;
	const char* str = "test";

	test_state->registers.edx = (int) str;
	irvingt_test_call(&StrLength, &test_state->registers);
	assert_int_equal(strlen(str), test_state->registers.eax);
}

int main(void) {
	struct register_state registers = { 0 };
	const struct CMUnitTest tests[] = {
		cmocka_unit_test_prestate(StrLength_can_compute, &registers),
	};

	cmocka_run_group_tests(tests, setup, teardown);
	return 0;
}
