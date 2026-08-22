#ifndef COMMANDS_H
#define COMMANDS_H

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <ctype.h>
#include <string.h>

extern int fd;
extern char temp[101];
extern int temp_index;

int
byte_count (char filename[]);

int
line_count (char filename[]);

int
word_count (char filename[]);

int
word_processing (char buffer[], int bytes_read);

#endif /* COMMANDS_H */
