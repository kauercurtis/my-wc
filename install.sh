#!/bin/sh

gcc commands.c main.c -o my-wc
sudo cp my-wc /usr/bin/my-wc
