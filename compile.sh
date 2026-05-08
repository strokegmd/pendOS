#!/bin/bash

./i686-elf-as -W src/boot.s -o bin/boot.bin
gcc -O2 -m32 -c src/lib/string.c -o bin/string.bin -ffreestanding
gcc -O2 -m32 -c src/drivers/tty.c -o bin/tty.bin -ffreestanding
gcc -O2 -m32 -c src/kernel.c -o bin/kernel.bin -ffreestanding
ld -m elf_i386 -T link.ld -o grub/boot/osbuild.bin bin/boot.bin bin/string.bin bin/tty.bin bin/kernel.bin
grub-mkrescue -o bin/osbuild.iso grub/
