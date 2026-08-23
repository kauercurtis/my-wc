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
extern int temp_len;

int
open_file (char file_name[]);

int
close_file ();

int
byte_count ();

int
line_count ();

int
word_count ();

int
word_processing (char buffer[], int bytes_read);

int
character_count ();

int
char_processing (char buffer[], int bytes_read);

#endif /* COMMANDS_H */
