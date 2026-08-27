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

/*
	word_count - Returns the number of words read from the file descriptor FD and uses word_processing for counting individual words.
	Returns -1 if there is an error reading from the file descriptor, FD.
*/
int
word_count ();

/*
	word_processing - Returns the number of words in arg1: buffer[].
	Detects the end of a word if it encounters a blank or control character.
	If arg1: buffer[] ends in a alphanumeric or punctutation character, the current word length is stored in TEMP_INDEX.
*/
int
word_processing (char buffer[], int bytes_read);

/*
	character_count - Returns the number of characters read from the file descriptor FD and uses char_processing for counting individual characters.
	Returns -1 if there is an error reading from the file descriptor, FD.
*/
int
character_count ();

/*
	char_processing - Returns the number of characters in arg1: buffer[].
	Detects the starting byte of a character to determine the character's length and stores it in in TEMP_LEN.
*/
int
char_processing (char buffer[], int bytes_read);

/*
	open_stream_input - Opens standard input and assigns it to FD.
	Returns -1 if it has an issue attempting to open standard input.
	Returns 0 if standard input is successfully opened.
*/
int
open_stream_input();

/*
	close_file - Closes standard input associated with FD.
	Returns -1 if it has an issue attempting to close standard input associated with FD.
	Returns 0 if standard input is successfully closed.
*/
int
close_stream_input();
#endif /* COMMANDS_H */
