/*
 * Anubday
 *
 * Chris Schick, 2020
 */
#include <stdlib.h>
#include <stdio.h>

#include "parse_command.h"

int main(int argc, char* argv[argc+1])
{
	// no args, just print today's birthdays
	if (argc == 1) {
		printf("You want all birthdays for today\n");
		return EXIT_SUCCESS;
	}

	// check for 'word' arguments
	int res = read_command(argv[1]);
	if (res < 0) {
		fprintf(stderr, "Unknown command: %s\n", argv[1]);
		return EXIT_FAILURE;
	}

	switch (res) {
	case show:
		read_show_opts(--argc, ++argv);
		break;
	default:
		printf("You selected '%s'\n", commands[res]);
		break;
	}

	return EXIT_SUCCESS;
}
