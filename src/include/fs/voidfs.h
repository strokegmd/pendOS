#ifndef __VOIDFS_H
#define __VOIDFS_H

#include <stdbool.h>
#include <stdint.h>

typedef struct
{
    bool is_directory;
    char *path;
    uint8_t *content;
} voidfs_entry_t;

uint8_t *voidfs_read_file(char *filepath);

#endif
