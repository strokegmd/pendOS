#include "include/grub/multiboot.h"
#include "include/drivers/tty.h"

void kmain(multiboot_info_t *mbinfo) 
{
    tty_init();
    tty_write_string("hi thats some string\n\neven with newlines support!");
}
