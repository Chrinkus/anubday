#include <stdlib.h>
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include <string.h>

#include <stdio.h>

#include "parse_command.h"

static void read_command_success(void** state)
{
	(void) state;	/* unused */
	int res = read_command("help");
	assert_true(res >= 0);
}

static void read_command_fail(void** state)
{
	(void) state;	/* unused */
	int res = read_command("breakfast");
	assert_int_equal(res, -1);
}

static void read_user_input_success(void** state)
{
	(void) state;	/* unused */
	int n = 7;
	char* args[] = {
		"prog",
		"-f",
		"Joe",
		"-l",
		"Don",
		"-b",
		"1936-02-12",
		NULL,		// real argv is NULL terminated(?)
	};
	user_input* pu = read_user_input(n, args);
	assert_non_null(pu);
	assert_string_equal(pu->first, "Joe");
	assert_string_equal(pu->last, "Don");
	assert_string_equal(pu->bday, "1936-02-12");
	free(pu);
}

static void read_user_input_partial(void** state)
{
	(void) state;	/* unused */
	int n = 5;
	char* args[] = {
		"prog",
		"-f",
		"Edward",
		"-b",
		"1947-02-24",
		NULL,
	};
	user_input* pu = read_user_input(n, args);
	assert_non_null(pu);
	assert_string_equal(pu->first, "Edward");
	assert_string_equal(pu->last, "");
	assert_string_equal(pu->bday, "1947-02-24");
	free(pu);
}

static void read_user_input_fail(void** state)
{
	(void) state;	/* unused */
	int n = 7;
	char* args[] = {
		"prog",
		"-f",
		"Richard",
		"-k",		// unregistered flag, should read as '?'
		"Whitman"
		"-b",
		"1926-06-01",
		NULL,
	};
	user_input* pu = read_user_input(n, args);
	assert_null(pu);
	free(pu);
}

int main(void)
{
	const struct CMUnitTest tests[] = {
		cmocka_unit_test(read_command_success),
		cmocka_unit_test(read_command_fail),
		cmocka_unit_test(read_user_input_success),
		cmocka_unit_test(read_user_input_partial),
		cmocka_unit_test(read_user_input_fail),
	};

	return cmocka_run_group_tests(tests, NULL, NULL);
}
