#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int
main (int argc, char *argv[])
{
	if (argc < 2)
	{
		fprintf(stderr, "Error: Expected 1 argument, but got %d.\n", argc - 1);
		fprintf(stderr, "Usage: %s <file name> or %s <command> <file name>\n", argv[0], argv[0]);
		return EXIT_FAILURE;
	}
	if (argc > 2)
	{
		char starting_character = argv[1][0];
		if (starting_character == '-')
		{
			int case_c = strcmp(argv[1], "-c");
			int case_l = strcmp(argv[1], "-l");
			int case_w = strcmp(argv[1], "-w");
			int case_m = strcmp(argv[1], "-m");
			switch (0)
			{
				case case_c:
					printf("-c case.\n");
					break;
				case case_l:
					printf("-l case.\n");
					break;
				case case_w:
					printf("-w case.\n");
					break;
				case case_m:
					printf("-m case.\n");
					break;
				default:
					fprintf(stderr, "Error: Expected valid command argument, but got %s.\n", argv[1]);
					fprintf(stderr, "Usage: -c for number of bytes, -l for number of lines, -w for number of words, or -m for number of characters\n");
					return EXIT_FAILURE;
			}
		}
		else
		{
			fprintf(stderr, "Error: Expected command to start with -, but got %c.\n", argv[1][0]);
			fprintf(stderr, "Usage: %s -<command> <file name>\n", argv[0]);
			return EXIT_FAILURE;
		}
	}
	else
	{
		printf("No command entered. File only.");
	}
	return EXIT_SUCCESS;
}
