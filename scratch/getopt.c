/*
 * playing with getopt()
 *
 * checking behaviours with various options and arguments
 */
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>		// this or 0 and 1?

enum cmds { add, show, edit, rm, num_cmds };

const char* commands[] = {
	[add]  = "add",
	[show] = "show",
	[edit] = "edit",
	[rm]   = "rm",
};

bool read_opts(int argc, char* argv[argc+1])
{
	int opt;
	while ((opt = getopt(argc, argv, "l:a:d:")) != -1) {
		switch (opt) {
		case 'l':
			puts("long");
			break;
		case 'a':
			puts("all");
			break;
		case 'd':
			puts("directory");
			break;
		case '?':
			fprintf(stderr, "Error: Unknown flag\n", opt);
			return false;
		default:
			fprintf(stderr, "Error: Unregistered flag %c\n", opt);
			return false;
		}
	}
	return true;
}

int main(int argc, char* argv[argc+1])
{
	if (argc == 1) {
		puts("No options");
		return EXIT_SUCCESS;
	}

	for (int i = 0; i < num_cmds; ++i) {
		if (strcmp(argv[1], commands[i]) == 0) {
			printf("Command %s. Checking for options..\n", argv[1]);
			read_opts(--argc, ++argv);
			return EXIT_SUCCESS;
		}
	}

	if (!read_opts(argc, argv))
		return EXIT_FAILURE;

	return EXIT_SUCCESS;
}
