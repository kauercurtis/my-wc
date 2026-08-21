#ifndef COMMANDS_H
#define COMMANDS_H

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

extern int fd;

int
byte_count (char filename[]);

int
line_count (char filename[]);

#endif /* COMMANDS_H */
