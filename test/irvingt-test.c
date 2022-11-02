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

char* make_test_file_path(char* test_file_path, const char* test_dir, const char* file_name) {
	if (strlen(test_dir) + strlen(file_name) + 2 > IRVINGT_TEST_PATH_MAX) {
		fail_msg("Test file path is too long");
		return NULL;
	}

	strcpy(test_file_path, test_dir);
	strcat(test_file_path, "/");
	strcat(test_file_path, file_name);

	return test_file_path;
}

static int setup(void** state) {
	struct test_state* new_state;
	struct register_state registers = { 0 };
	char tmp_dir[IRVINGT_TEST_PATH_MAX];
	const char* tmp_dir_base = getenv("TMPDIR");

	if (!tmp_dir_base || strlen(tmp_dir_base) == 0) {
		tmp_dir_base = "/tmp";
	}

	if (!make_test_file_path(tmp_dir, tmp_dir_base, "irvingt_testXXXXXX")) {
		return -1;
	}

	if (!mkdtemp(tmp_dir)) {
		fail_msg("Cannot create temporary directory");
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

static void CreateOutputFile_can_create(void** state) {
	struct test_state* test_state = *state;
	char test_file_path[IRVINGT_TEST_PATH_MAX];

	if (!make_test_file_path(test_file_path, test_state->tmp_dir, "test.txt")) {
		return;
	}

	test_state->registers.edx = (int) &test_file_path;
	test_state->registers.eax = 0;
	irvingt_test_call(&CreateOutputFile, &test_state->registers);

	assert_int_not_equal(0, test_state->registers.eax);
	assert_int_equal(0, access(test_file_path, F_OK));

	irvingt_test_call(&CloseFile, &test_state->registers);
	unlink(test_file_path);
}

static void StrLength_can_compute(void** state) {
	struct test_state* test_state = *state;
	const char* str = "test";

	test_state->registers.edx = (int) str;
	irvingt_test_call(&StrLength, &test_state->registers);
	assert_int_equal(strlen(str), test_state->registers.eax);
}

int main(void) {
	const struct CMUnitTest tests[] = {
		cmocka_unit_test(CreateOutputFile_can_create),
		cmocka_unit_test(StrLength_can_compute),
	};

	return !!cmocka_run_group_tests(tests, setup, teardown);
}
