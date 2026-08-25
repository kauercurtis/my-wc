/**
	main.c - Primary driver file for execution.
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
char FILE_NAME[256];

/*
	print_file_data - Prints LINES, WORDS, CHARACTERS, and BYTES in this order followed by the filename.
	The order of the values printed is altered if a value is == -1.
	Example: If LINES == -1, then the order printed is [WORDS] [CHARACTERS] [BYTES] [filename].
*/
void
print_file_data ();

/*
	parse_argument_commands - Parses commands using the getopt function defined in unistds.h and executes accordingly by calling functions defined by commands.h.
	Returns 1 if a command != l, w, m, or c.
	Returns 0 on success.
*/
int
parse_argument_commands (int arg_count, char *arguments[]);

/*
	main.c - Main driver function for program.
	Returns EXIT_FAILURE on the following conditions: insufficient # of arguments, unable to successfully open file, incorrect commands, and unable to successfully close file.
	Returns EXIT_SUCCESS if all of the EXIT_FAILURE conditions are false.
*/
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
			strcpy(FILE_NAME, argv[2]);
			if (parse_argument_commands(argc, argv) == -1)
			{
				return EXIT_FAILURE;
			}
		    print_file_data();
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
	else if (argc == 2 && argv[1][0] == '-')
	{
		char starting_character = argv[1][0];
		if (starting_character == '-')
		{
		   	if (open_stream_input() == -1)
			{
				fprintf(stderr, "Error: Error opening standard input, got -1.\n");
				return EXIT_FAILURE;
			}
			if (parse_argument_commands(argc, argv) == -1)
			{
				return EXIT_FAILURE;
			}
			print_file_data();
			if (close_stream_input() == -1)
			{
				fprintf(stderr, "Error: Error closing stdin, got -1.\n");
				return EXIT_FAILURE;
			}
		}
		else
		{
			fprintf(stderr, "Error: Expected command to start with -, but got %c.\n", argv[1][0]);
			fprintf(stderr, "Usage: | %s -<command>\n", argv[0]);
			return EXIT_FAILURE;
		}
	}
	else
	{
		if (open_file(argv[1]) == -1)
		{
			fprintf(stderr, "Error: Error opening %s, got -1.\n", argv[1]);
			return EXIT_FAILURE;
		}
		strcpy(FILE_NAME, argv[1]);
		BYTES = byte_count ();
		LINES = line_count ();
		WORDS = word_count ();
		print_file_data();
		if (close_file() == -1)
		{
			fprintf(stderr, "Error: Error closing %s, got -1.\n", argv[1]);
			return EXIT_FAILURE;
		}
	}
	return EXIT_SUCCESS;
}

int
parse_argument_commands (int arg_count, char *arguments[])
{
	int opt = 0;
	while ((opt = getopt(arg_count, arguments, "clwm")) != -1)
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
				fprintf(stderr, "Usage: %s [-c], [-l], [-w], [-m] [file]\n", arguments[0]);
				return -1;
		}
	}
	return 0;
}

void
print_file_data ()
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
	if (sizeof(FILE_NAME) != 0)
	{
		printf("%s\n", FILE_NAME);
	}
	else
	{
		printf("\n");
	}
}
