#include "include/grub/multiboot.h"
#include "include/drivers/tty.h"
#include "include/drivers/vbe.h"
#include "include/fs/voidfs.h"
#include "include/gfx/ppm.h"
#include "include/drivers/ps2/keyboard.h"
#include "include/lib/stdio.h"
#include "include/cpu/gdt.h"
#include "include/cpu/idt.h"
#include "include/cpu/system.h"

void kmain_tty(multiboot_info_t *mbinfo)
{
    gdt_init();
    idt_init();
    interrupt_enable_all();
    keyboard_init();

    for(;;)
    {
        char key = keyboard_get_key();
        if (key) tty_putchar(key);
    }
}

void kmain_vbe(multiboot_info_t *mbinfo)
{
    vbe_init(mbinfo);

    for (;;)
    {
        vbe_rect(0, 0, 800, 600, 0xFFFFFF);
    }
}

void kmain(multiboot_info_t *mbinfo) 
{
    if (mbinfo->framebuffer_width == VGA_WIDTH) 
    {
        return kmain_tty(mbinfo);
    }

    return kmain_vbe(mbinfo);
}
