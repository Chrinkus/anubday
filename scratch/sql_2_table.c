#include <stdlib.h>
#include <stdio.h>
#include <sqlite3.h>

static int callback(void* not_used, int argc, char** argv, char** az_col_name)
{
	for (int i = 0; i < argc; ++i)
		printf("%s = %s\n", az_col_name[i], argv[i] ? argv[i] : "NULL");
	printf("\n");
	return 0;
}

int main(int argc, char* argv[argc+1])
{
	sqlite3* db;
	char* z_err_msg = NULL;

	int rc = sqlite3_open("test.db", &db);

	if (rc) {
		fprintf(stderr, "Can't open database: %s\n",
				sqlite3_errmsg(db));
		return EXIT_FAILURE;
	} else {
		fprintf(stderr, "Opened database successfully\n");
	}

	/* Create SQL statement */
	char sql[] = "CREATE TABLE COMPANY("		\
	       "ID INT PRIMARY KEY	NOT NULL,"	\
	       "NAME		TEXT	NOT NULL,"	\
	       "AGE		INT	NOT NULL,"	\
	       "ADDRESS		CHAR(50),"		\
	       "SALARY		REAL);";

	rc = sqlite3_exec(db, sql, callback, NULL, &z_err_msg);

	if (rc != SQLITE_OK) {
		fprintf(stderr, "SQL error: %s\n", z_err_msg);
		sqlite3_free(z_err_msg);
	} else {
		fprintf(stdout, "Table created successfully\n");
	}

	sqlite3_close(db);
	return EXIT_SUCCESS;
}
