#include "commands.h"

int
byte_count (char filename[])
{
	int bytes = 0;
	int fd = open(filename, O_RDONLY);
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
