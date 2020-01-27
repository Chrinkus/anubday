#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>

static int callback(void* data, int argc, char** argv, char** columns)
{
	fprintf(stderr, "%s: ", (const char*)data);

	for (int i = 0; i < argc; ++i)
		printf("%s = %s\n", columns[i], argv[i] ? argv[i] : "NULL");

	printf("\n");
	return 0;
}

int main(int argc, char* argv[argc+1])
{
	sqlite3* db;
	int rc = sqlite3_open("test.db", &db);

	if (rc) {
		fprintf(stderr, "Can't open database: %s\n",
				sqlite3_errmsg(db));
		return 0;
	} else {
		fprintf(stderr, "Opened database successfully\n");
	}

	char stmt[] = "SELECT * from COMPANY";

	char* err_msg = NULL;
	const char data[] = "Callback function called";
	rc = sqlite3_exec(db, stmt, callback, (void*)data, &err_msg);

	if (rc != SQLITE_OK) {
		fprintf(stderr, "SQL error: %s\n", err_msg);
		sqlite3_free(err_msg);
	} else {
		fprintf(stdout, "Operation done successfully\n");
	}
	sqlite3_close(db);
	return EXIT_SUCCESS;
}
