#include "commands.h"

void
byte_count (char filename[])
{
	printf("%s\n", filename);
	int fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		fprintf(stderr, "Error: File could not be opened.\n");
	}
	else
	{
		int bytes = 0;
		bytes = lseek(fd, 0, SEEK_END);
		printf("%d\n", bytes);
	}
	int close_status = close(fd);
	if (close_status < 0)
	{
		fprintf(stderr, "Error: File descriptor could not be closed appropriately.\n");
	}
	return;
}
