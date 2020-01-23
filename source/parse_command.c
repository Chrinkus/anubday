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

void read_show_opts(int argc, char* argv[argc+1])
{
	user_input* pu = read_user_input(argc, argv);
	if (!pu) {
		fprintf(stderr, "read_user_input(): NULL malloc\n");
		exit(EXIT_FAILURE);
	}

	printf("First name: %s\n", pu->first);
	printf("Last name: %s\n", pu->last);
	printf("Birthday: %s\n", pu->bday);
	printf("\n");
	printf("Is this correct? (y/n)\n");
	printf("> ");
	int c = getchar();
	if (c == 'y')
		printf("Okay!\n");
	else
		printf("Nevermind..\n");
}

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 

user_input* read_user_input(int argc, char* argv[argc+1])
{
	// Consider moving malloc and memset to separate 'create' function
	user_input* pu = (user_input*) malloc(sizeof(user_input));
	if (!pu) {
		fprintf(stderr, "read_user_input(): NULL malloc\n");
		return NULL;
	}
	memset(pu->first, '\0', buf_first);	// memset vs pu->first[0] = '\0'
	memset(pu->last, '\0', buf_last);
	memset(pu->bday, '\0', buf_bday);

	optind = 1;		// reset to first argument
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
		case '?':
			fprintf(stderr, "Unexpected argument: %c\n", opt);
			return NULL;
		default:
			fprintf(stderr, "Should never get here: %c\n", opt);
			return NULL;
		}
	}
	return pu;
}
