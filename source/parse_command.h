#pragma once

enum Cmds { add, rm, edit, show, help, num_cmds };

extern const char* commands[num_cmds];

int read_command(const char s[static 1]);

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 

enum Buf_lengths { buf_first = 24, buf_last = 24, buf_bday = 11 };

typedef struct User_input user_input;
struct User_input {
	char first[buf_first];
	char last[buf_last];
	char bday[buf_bday];
};

user_input* read_user_input(int argc, char* argv[argc+1]);
