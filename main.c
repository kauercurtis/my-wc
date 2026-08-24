/**
	main.c - Primary driver file for execution.
	Returns EXIT_FAILURE on the following conditions: insufficient # of arguments, unable to successfully open file, incorrect commands, and unable to successfully close file.
	Returns EXIT_SUCCESS if all of the EXIT_FAILURE conditions are false.
**/

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "commands.h"
#include <string.h>

int BYTES = -1;
int LINES = -1;
int WORDS = -1;
int CHARS = -1;

/*
	print_file_data - Prints LINES, WORDS, CHARACTERS, and BYTES in this order followed by the filename.
	The order of the values printed is altered if a value is == -1.
	Example: If LINES == -1, then the order printed is WORDS, CHARACTERS, BYTES, and the filename.
*/
void
print_file_data();

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
		   	if (open_file(argv[2]) == -1)
			{
				fprintf(stderr, "Error: Error opening %s, got -1.\n", argv[2]);
				return EXIT_FAILURE;
			}
			int opt = 0;
		    while ((opt = getopt(argc, argv, "clwm")) != -1)
			{
				switch (opt)
				{
					case 'c':
						BYTES = byte_count ();
						break;
					case 'l':
						LINES = line_count ();
						break;
					case 'w':
						WORDS = word_count ();
						break;
					case 'm':
						CHARS = character_count ();
						break;
					default:
						fprintf(stderr, "Usage: %s [-c], [-l], [-w], [-m] [file]\n", argv[0]);
						return EXIT_FAILURE;
				}
			}
			print_file_data(argv[2]);
			if (close_file() == -1)
			{
				fprintf(stderr, "Error: Error closing %s, got -1.\n", argv[2]);
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
		if (open_file(argv[1]) == -1)
		{
			fprintf(stderr, "Error: Error opening %s, got -1.\n", argv[2]);
			return EXIT_FAILURE;
		}
		BYTES = byte_count ();
		LINES = line_count ();
		WORDS = word_count ();
		print_file_data(argv[1]);
		if (close_file() == -1)
		{
			fprintf(stderr, "Error: Error closing %s, got -1.\n", argv[2]);
			return EXIT_FAILURE;
		}
	}
	return EXIT_SUCCESS;
}

void
print_file_data(char file_name[])
{
	if (LINES != -1)
	{
		printf("%d ", LINES);
	}
	if (WORDS != -1)
	{
		printf("%d ", WORDS);
	}
	if (CHARS != -1)
	{
		printf("%d ", CHARS);
	}
	if (BYTES != -1)
	{
		printf("%d ", BYTES);
	}
	printf("%s\n", file_name);
}
