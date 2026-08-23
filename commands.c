#include "commands.h"

int fd;
char temp[101];
int temp_index = 0;

int
open_file (char file_name[])
{
	fd = open(file_name, O_RDONLY);
	if (fd < 0)
	{
		fprintf(stderr, "Error: File could not be opened, got %d.\n", fd);
		return -1;
	}
	return 0;
}

int
close_file ()
{
	int close_status = close(fd);
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
	bytes = lseek(fd, 0, SEEK_END);
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
		nb_read = read(fd, buf, 100);
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
	return lines;
}

// buffer has 101 characters (including null terminator)
// Objective: Count the words in the buffer
int
word_processing (char buffer[], int bytes_read)
{
	int word_count = 0;
	for (int i = 0; i < bytes_read; i++)
	{
		/*
		if (!isgraph((unsigned char)buffer[i]) &&
    		!isblank((unsigned char)buffer[i]) &&
    		!iscntrl((unsigned char)buffer[i]))
		{
    		printf("Unexpected byte: %d\n", (unsigned char)buffer[i]);
		}
		*/
		// if (isalnum((unsigned char)buffer[i]) || ispunct(buffer[i]))
		if (isgraph(buffer[i]))
		{
			temp[temp_index] = buffer[i];
			temp[temp_index + 1] = '\0';
			// printf("%c\n", buffer[i]);
			temp_index++;
		}
		else if (isblank(buffer[i]) || iscntrl(buffer[i]))
		{
			if (temp_index > 0)
			{
				//printf("%s\n", temp);
				temp[0] = '\0';
				temp_index = 0;
				word_count++;
			}
			// char refresh[bytes_read];
			// printf("%s\n", temp);
			// strcpy(temp, refresh);
			// temp[0] = '\0';
			// word_count++;
			// curr_index = 0;
		}
		else
		{
			temp[temp_index] = buffer[i];
			temp[temp_index + 1] = '\0';
			temp_index++;
		}
		/*
		if ((isblank(buffer[i]) || buffer[i] == '\n' || buffer[i] == '\0') && ((sizeof(temp) / sizeof(char)) > 0) && buffer[i])
		{
			curr_index = 0;
			char refresh[bytes_read];
			strcpy(temp, refresh);
			temp[0] = '\0';
			word_count++;
		}
		else if (!isblank(buffer[i]) && buffer[i] != '\n')
		{
			temp[curr_index] = buffer[i];
			temp[curr_index + 1] = '\0';
			curr_index++;
			// printf("%s\n", temp);
			printf("%c\n", buffer[i]);
		}
		*/
	}
	// printf("%s\n", buffer);
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
		nb_read = read(fd, buf, 100);
		if (nb_read == -1)
		{
			fprintf(stderr, "Error: Reading error, got -1.");
			break;
		}
		buf[nb_read] = '\0';
		words += word_processing(buf, nb_read);
	}
	return words;
}
