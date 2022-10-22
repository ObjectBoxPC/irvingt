#include "irvingt-funcs.h"
#include <setjmp.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <cmocka.h>

struct register_state {
	int eax;
	int ebx;
	int ecx;
	int edx;
};

void irvingt_test_call(void (*irvingt_func)(void), struct register_state* registers);

static void StrLength_can_compute(void** state) {
	struct register_state* registers = *state;
	const char* str = "test";

	registers->edx = (int) str;
	irvingt_test_call(&StrLength, registers);
	assert_int_equal(strlen(str), registers->eax);
}

int main(void) {
	struct register_state registers = { 0 };
	const struct CMUnitTest tests[] = {
		cmocka_unit_test_prestate(StrLength_can_compute, &registers),
	};

	cmocka_run_group_tests(tests, NULL, NULL);
	return 0;
}
