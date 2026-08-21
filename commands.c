#include "commands.h"

int fd;

int
byte_count (char filename[])
{
	int bytes = 0;
	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		fprintf(stderr, "Error: File could not be opened.\n");
	}
	else
	{
		bytes = lseek(fd, 0, SEEK_END);
	}
	int close_status = close(fd);
	if (close_status < 0)
	{
		fprintf(stderr, "Error: File descriptor could not be closed appropriately.\n");
	}
	return bytes;
}

int
line_count (char filename[])
{
	fd = open(filename, O_RDONLY);
	int lines = 0;
	if (fd < 0)
	{
		fprintf(stderr, "Error: File could not be opened.\n");
	}
	else{
		char buf[100 + 1];
		int nb_read = -1;
		while (nb_read != 0)
		{
			nb_read = read(fd, buf, 100);
			if (nb_read == -1)
			{
				fprintf(stderr, "Error: Reading error.\n");
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
	}
	close(fd);
	return lines;
}
