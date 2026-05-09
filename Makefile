CC = gcc
AS = ./i686-elf-as
LD = ld

CFLAGS = -O2 -m32 -ffreestanding
LDFLAGS = -m elf_i386 -T link.ld

OBJ = \
    bin/boot.o \
    bin/string.o \
    bin/stdio.o \
    bin/tty.o \
    bin/vbe.o \
    bin/ppm.o \
    bin/ramfs_disk.o \
    bin/voidfs.o \
    bin/kernel.o

all: bin/osbuild.iso

bin/boot.o: src/boot.s
	$(AS) -W $< -o $@

bin/string.o: src/lib/string.c
	$(CC) $(CFLAGS) -c $< -o $@

bin/stdio.o: src/lib/stdio.c
	$(CC) $(CFLAGS) -c $< -o $@

bin/tty.o: src/drivers/tty.c
	$(CC) $(CFLAGS) -c $< -o $@

bin/vbe.o: src/drivers/vbe.c
	$(CC) $(CFLAGS) -c $< -o $@

bin/ppm.o: src/gfx/ppm.c
	$(CC) $(CFLAGS) -c $< -o $@

bin/ramfs_disk.o: src/fs/ramfs_disk.c
	$(CC) $(CFLAGS) -c $< -o $@

bin/voidfs.o: src/fs/voidfs.c
	$(CC) $(CFLAGS) -c $< -o $@

bin/kernel.o: src/kernel.c
	$(CC) $(CFLAGS) -c $< -o $@

grub/boot/osbuild.bin: $(OBJ)
	$(LD) $(LDFLAGS) -o $@ $(OBJ)

bin/osbuild.iso: grub/boot/osbuild.bin
	grub-mkrescue -o $@ grub/

clean:
	rm -f bin/*.o grub/boot/osbuild.bin bin/osbuild.iso
    