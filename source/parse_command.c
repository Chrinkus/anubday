#include "parse_command.h"

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <stddef.h>
#include <string.h>

const char* commands[] = {
	[add]  = "add",
	[rm]   = "rm",
	[edit] = "edit",
	[show] = "show",
	[help] = "help",
};

int read_command(const char s[static 1])
{
	for (int i = 0; i < num_cmds; ++i)
		if (strcmp(s, commands[i]) == 0)
			return i;
	return -1;
}

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 

user_input* read_user_input(int argc, char* argv[argc+1])
	// Read user input from command line. Can be used by most CRUD ops.
	// While I don't often favour signifying type in a variable name,
	// 'pu' is appropriate since this is user input w/o validation or
	// sanitation.
{
	user_input* pu = (user_input*) malloc(sizeof(user_input));

	int opt;
	while ((opt = getopt(argc, argv, "f:l:b:")) != -1) {
		switch (opt) {
		case 'f':
			strncpy(pu->first, optarg, buf_first);
			break;
		case 'l':
			strncpy(pu->last, optarg, buf_last);
			break;
		case 'b':
			strncpy(pu->bday, optarg, buf_bday);
			break;
		default:
			fprintf(stderr, "Unknown argument: %c\n", opt);
			return NULL;
		}
	}
	return pu;
}
