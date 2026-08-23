#include "commands.h"

int fd;
char temp[101];
int temp_index = 0;
int temp_len = 0;

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

int
word_processing (char buffer[], int bytes_read)
{
	int word_count = 0;
	for (int i = 0; i < bytes_read; i++)
	{
		if (isblank(buffer[i]) || iscntrl(buffer[i]))
		{
			if (temp_index > 0)
			{
				temp[0] = '\0';
				temp_index = 0;
				word_count++;
			}
		}
		else
		{
			temp[temp_index] = buffer[i];
			temp[temp_index + 1] = '\0';
			temp_index++;
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

int
char_processing (char buffer[], int bytes_read)
{
	int char_count = 0;
	for (int i = 0; i < bytes_read; i++)
	{
		if (temp_len > 1 && temp_index == temp_len - 1)
		{
			temp[0] = '\0';
			temp_index = 0;
			temp_len = 0;
			char_count++;
		}
		else if ((buffer[i] & 0x80) == 0)
		{
			char_count++;
		}
		else if ((buffer[i] & 0xE0) == 0xC0)
		{
			temp_len = 2;
			temp[temp_index] = buffer[i];
			temp_index++;
		}
		else if ((buffer[i] & 0xf0) == 0xE0)
		{
			temp_len = 3;
			temp[temp_index] = buffer[i];
			temp_index++;
		}
		else if ((buffer[i] & 0xF8) == 0xF0)
		{
			temp_len = 4;
			temp[temp_index] = buffer[i];
			temp_index++;
		}
		else
		{
			temp[temp_index] = buffer[i];
			temp_index++;
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
		nb_read = read(fd, buf, 100);
		if (nb_read == -1)
		{
			fprintf(stderr, "Error: Reading error, got -1.");
			break;
		}
		buf[nb_read] = '\0';
		characters += char_processing(buf, nb_read);
	}
	return characters;
}
