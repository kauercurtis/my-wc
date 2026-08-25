#!/bin/sh

gcc commands.c main.c -o my-wc
cp my-wc /usr/bin/my-wc
