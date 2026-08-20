#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "commands.h"
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
			int opt = 0;
			// char filename[260];
			// strcpy(filename, argv[2]);
		       	while ((opt = getopt(argc, argv, "clwm")) != -1)
			{
				switch (opt)
				{
					case 'c':
						byte_count (argv[2]);
						break;
					case 'l':
						printf("-l case.\n");
						break;
					case 'w':
						printf("-w case.\n");
						break;
					case 'm':
						printf("-m case.\n");
						break;
					default:
						fprintf(stderr, "Usage: %s [-c], [-l], [-w], [-m] [file]\n", argv[0]);
						return EXIT_FAILURE;
				}
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
