#include "include/grub/multiboot.h"
#include "include/drivers/tty.h"
#include "include/fs/voidfs.h"

void kmain(multiboot_info_t *mbinfo) 
{
    tty_init();
    voidfs_read();
}
