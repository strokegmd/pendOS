#!/bin/bash

i686-elf-gcc -c main.c -o shell.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
i686-elf-gcc -T link.ld -o shell -ffreestanding -O2 -nostdlib shell.o -lgcc
