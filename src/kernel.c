#include "include/grub/multiboot.h"
#include "include/drivers/tty.h"
#include "include/lib/stdio.h"

void kmain(multiboot_info_t *mbinfo) 
{
    tty_init();
    printf("%s%c%s", "hi thats printf", '\n', "newline!!");
}
