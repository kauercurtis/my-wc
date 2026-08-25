# my-wc
My own version of the Unix command line wc tool.

## Systems Supported

`Linux` - Specifically Ubuntu systems but should work on other distros. 

## Installation

`Clone repo` - Clone the repository into the directory of your choosing.

`./install.sh` - Run the install script. It might prompt for you to enter your user password.

## Usage

`my-wc -[commands] file` - Will output file data depending on commands. See commands in the next section.

`my-wc file` - Will output the file's line count, word count, and byte count.

`[linux command] file | my-wc -[commands]` - Will use standard input instead of a file.

## Commands

`c` - Byte count.

`l` - Line count.

`w` - Word count.

`m` - character count.

