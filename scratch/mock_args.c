/*
 * trying to mock argv
 */
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

int read_args(int argc, char* argv[argc+1])
{
	int opt;
	while ((opt = getopt(argc, argv, "abc:")) != -1) {
		switch (opt) {
		case 'a':
			puts("alpha");
			break;
		case 'b':
			puts("bravo");
			break;
		case 'c':
			printf("charlie: %s\n", optarg);
			break;
		case '?':
			fprintf(stderr, "Unknown option\n");
			return 1;
		default:
			fprintf(stderr, "Unexpected Error\n");
			return 2;
		}
	}
	return 0;
}

//int main(int argc, char* argv[argc+1])
int main(void)
{
	/*
	if (argc == 1) {
		printf("No args\n");
		return EXIT_SUCCESS;
	}

	int res = read_args(argc, argv);
	printf("read_args result: %d\n", res);
	*/
	char* ac1[] = {
		"prog",
		"-ab",
		NULL,
	};
	int n1 = 2;
	int res1 = read_args(n1, ac1);
	printf("read_args result 1: %d, optind: %d\n", res1, optind);

	char* ac2[] = {
		"prog",
		"-a",
		"-c",
		"christmas",
		"-b",
		NULL,
	};
	int n2 = 5;
	optind = 1;
	int res2 = read_args(n2, ac2);
	printf("read_args result 2: %d, optind: %d\n", res2, optind);
	printf("read_args result 2: %d\n", res2);

	char* ac3[] = {
		"prog",
		"-a",
		"-d",
		"dingo",
		"-c",
		"cain",
		NULL,
	};
	int n3 = 6;
	optind = 1;
	int res3 = read_args(n3, ac3);
	printf("read_args result 3: %d, optind: %d\n", res3, optind);

	return EXIT_SUCCESS;
}
