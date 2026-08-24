/**
	commands.h - Header interface file for processing commands.
	Implementation file: commands.c
**/

#ifndef COMMANDS_H
#define COMMANDS_H

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <ctype.h>
#include <string.h>

extern int FD;
extern int TEMP_INDEX;
extern int TEMP_LEN;

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
