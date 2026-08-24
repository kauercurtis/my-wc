/**
	commands.c - Implementation file for commands.h
**/

#include "commands.h"

int FD;
int TEMP_INDEX = 0;
int TEMP_LEN = 0;

int
open_file (char file_name[])
{
	FD = open(file_name, O_RDONLY);
	if (FD < 0)
	{
		fprintf(stderr, "Error: File could not be opened, got %d.\n", FD);
		return -1;
	}
	return 0;
}

int
close_file ()
{
	int close_status = close(FD);
	if (close_status < 0)
	{
		fprintf(stderr, "Error: File descriptor could not be closed appropriately, got %d.\n", close_status);
		return -1;
	}
	return 0;
}

int
byte_count ()
{
	int bytes = 0;
	bytes = lseek(FD, 0, SEEK_END);
	lseek(FD, 0, SEEK_SET);
	return bytes;
}

int
line_count ()
{
	int lines = 0;
	char buf[100 + 1];
	int nb_read = -1;
	while (nb_read != 0)
	{
		nb_read = read(FD, buf, 100);
		if (nb_read == -1)
		{
			fprintf(stderr, "Error: Reading error, got -1.");
			break;
		}
		buf[nb_read] = '\0';
		for (int i = 0; i < nb_read; i++)
		{
			if (buf[i] == '\n')
			{
				lines++;
			}
		}
	}
	lseek(FD, 0, SEEK_SET);
	return lines;
}

int
word_processing (char buffer[], int bytes_read)
{
	int word_count = 0;
	for (int i = 0; i < bytes_read; i++)
	{
		if (isblank(buffer[i]) || iscntrl(buffer[i]))
		{
			if (TEMP_INDEX > 0)
			{
				TEMP_INDEX = 0;
				word_count++;
			}
		}
		else
		{
			TEMP_INDEX++;
		}
	}
	return word_count;
}

int
word_count ()
{

	int words = 0;
	char buf[100 + 1];
	int nb_read = -1;
	while (nb_read != 0)
	{
		nb_read = read(FD, buf, 100);
		if (nb_read == -1)
		{
			fprintf(stderr, "Error: Reading error, got -1.");
			break;
		}
		buf[nb_read] = '\0';
		words += word_processing(buf, nb_read);
	}
	lseek(FD, 0, SEEK_SET);
	return words;
}

int
char_processing (char buffer[], int bytes_read)
{
	int char_count = 0;
	for (int i = 0; i < bytes_read; i++)
	{
		if (TEMP_LEN > 1 && TEMP_INDEX == TEMP_LEN - 1)
		{
			TEMP_INDEX = 0;
			TEMP_LEN = 0;
			char_count++;
		}
		else if ((buffer[i] & 0x80) == 0)
		{
			char_count++;
		}
		else if ((buffer[i] & 0xE0) == 0xC0)
		{
			TEMP_LEN = 2;
			TEMP_INDEX++;
		}
		else if ((buffer[i] & 0xf0) == 0xE0)
		{
			TEMP_LEN = 3;
			TEMP_INDEX++;
		}
		else if ((buffer[i] & 0xF8) == 0xF0)
		{
			TEMP_LEN = 4;
			TEMP_INDEX++;
		}
		else
		{
			TEMP_INDEX++;
		}
	}
	return char_count;
}

int
character_count ()
{
	int characters = 0;
	char buf[100 + 1];
	int nb_read = -1;
	while (nb_read != 0)
	{
		nb_read = read(FD, buf, 100);
		if (nb_read == -1)
		{
			fprintf(stderr, "Error: Reading error, got -1.");
			break;
		}
		buf[nb_read] = '\0';
		characters += char_processing(buf, nb_read);
	}
	lseek(FD, 0, SEEK_SET);
	return characters;
}
