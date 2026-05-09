#include "../include/fs/voidfs.h"
#include "../include/lib/stdio.h"
#include "../include/fs/ramfs_disk.h"

uint8_t *voidfs_read_file(char *filepath)
{
    // TODO: path is unused
    bool is_directory = disk[0];
    char *path = (char*)&disk[1];
    uint8_t *content = path + strlen(path) + 1;

    return content;
}
