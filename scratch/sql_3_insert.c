#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>

static int callback(void* unused, int argc, char** argv, char** columns)
{
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
		return EXIT_SUCCESS;
	} else {
		fprintf(stderr, "Opened database successfully\n");
	}

	char stmt[] = "INSERT INTO COMPANY (ID,NAME,AGE,ADDRESS,SALARY) " \
		      "VALUES (1, 'Paul', 32, 'California', 20000.00 ); " \
		      "INSERT INTO COMPANY (ID,NAME,AGE,ADDRESS,SALARY) " \
		      "VALUES (2, 'Allen', 25, 'Texas', 15000.00 ); "	  \
		      "INSERT INTO COMPANY (ID,NAME,AGE,ADDRESS,SALARY) " \
		      "VALUES (3, 'Teddy', 23, 'Norway', 20000.00 ); "	  \
		      "INSERT INTO COMPANY (ID,NAME,AGE,ADDRESS,SALARY) " \
		      "VALUES (4, 'Mark', 25, 'Richmond', 65000.00 );";

	char* err_msg = NULL;
	rc = sqlite3_exec(db, stmt, callback, 0, &err_msg);

	if (rc != SQLITE_OK) {
		fprintf(stderr, "SQL error: %s\n", err_msg);
		sqlite3_free(err_msg);
	} else {
		fprintf(stdout, "Records created successfully\n");
	}
	sqlite3_close(db);
	return EXIT_SUCCESS;
}
