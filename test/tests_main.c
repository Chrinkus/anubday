#include <stdlib.h>
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include <string.h>

#include "parse_command.h"

static void read_command_success(void** state)
{
	(void) state; /* unused */
	int res = read_command("help");
	assert_true(res >= 0);
}

static void read_command_fail(void** state)
{
	(void) state; /* unused */
	int res = read_command("breakfast");
	assert_int_equal(res, -1);
}

static void read_user_input_success(void** state)
{
	(void) state; /* unused */
	int n = 7;
	char* args[] = {
		"prog",
		"-f",
		"Joe",
		"-l",
		"Don",
		"-b",
		"1936-02-12",
		NULL,
	};
	user_input* pu = read_user_input(n, args);
	assert_non_null(pu);
	assert_string_equal(pu->first, args[2]);
	assert_string_equal(pu->last, args[4]);
	assert_string_equal(pu->bday, args[6]);

	free(pu);
}

int main(void)
{
	const struct CMUnitTest tests[] = {
		cmocka_unit_test(read_command_success),
		cmocka_unit_test(read_command_fail),
		cmocka_unit_test(read_user_input_success),
	};

	return cmocka_run_group_tests(tests, NULL, NULL);
}
