#include <stdlib.h>
#include <stdio.h>
#include <sqlite3.h>

int main(int argc, char* argv[argc+1])
{
	sqlite3* db;
	int rc = sqlite3_open("test.db", &db);

	if (rc) {
		fprintf(stderr, "Can't open database: %s\n",
				sqlite3_errmsg(db));
		return EXIT_FAILURE;
	} else {
		fprintf(stderr, "Opened database successfully\n");
	}
	sqlite3_close(db);
}
