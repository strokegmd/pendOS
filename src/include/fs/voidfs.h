#ifndef __VOIDFS_H
#define __VOIDFS_H

#include <stdbool.h>
#include <stdint.h>

typedef struct
{
    bool is_directory;
    char *path;
    char *content;
} voidfs_entry_t;

void voidfs_read(void);

#endif
