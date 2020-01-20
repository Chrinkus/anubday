#include <stdlib.h>
#include <stdio.h>
#include <sqlite3.h>

int main(void)
{
	sqlite3* db;
	int rc = sqlite3_open("test.db", &db);

	if (rc) {
		fprintf(stderr, "Can't open database: %s\n",
				sqlite3_errmsg(db));
		return EXIT_FAILURE;
	} else {
		printf("Opened database successfully\n");
	}

	sqlite3_close(db);
	return EXIT_SUCCESS;
}
