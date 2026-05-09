#include "include/grub/multiboot.h"
#include "include/drivers/tty.h"
#include "include/drivers/vbe.h"
#include "include/fs/voidfs.h"
#include "include/gfx/ppm.h"

void kmain_tty(multiboot_info_t *mbinfo)
{
    for(;;)
    {

    }
}

void kmain_vbe(multiboot_info_t *mbinfo)
{
    vbe_init(mbinfo);

    uint8_t *data = voidfs_read_file("wallpaper.ppm");
    ppm_render(data, 0, 0);
}

void kmain(multiboot_info_t *mbinfo) 
{
    if (mbinfo->framebuffer_width == VGA_WIDTH) 
    {
        return kmain_tty(mbinfo);
    }

    return kmain_vbe(mbinfo);
}
