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

/*
	open_file - Opens the file in arg1: file_name[] and assigns it to FD.
	Returns -1 if it has an issue attempting to open the file.
	Returns 0 if the file is successfully opened.
*/
int
open_file (char file_name[]);

/*
	close_file - Closes the file associated with FD.
	Returns -1 if it has an issue attempting to close the file associated with FD.
	Returns 0 if the file is successfully closed.
*/
int
close_file ();

/*
	byte_count - Returns the number of bytes read using read() from the unistd.h library, from the file descriptor FD.
	Returns -1 if there is an error reading from the file descriptor, FD.
*/
int
byte_count ();

/*
	line_count - Returns the number of lines read using read() from the unistd.h library, from the file descriptor FD.
	Returns -1 if there is an error reading from the file descriptor, FD.
*/
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

int
open_stream_input();

int
close_stream_input();
#endif /* COMMANDS_H */
