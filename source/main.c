/*
 * Anubday
 *
 * Chris Schick, 2020
 */
#include <stdlib.h>
#include <stdio.h>

#include "parse_command.h"

//extern const char* commands[num_cmds];

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
	} else {
		printf("You want to '%s' some data\n", commands[res]);
	}

	return EXIT_SUCCESS;
}
