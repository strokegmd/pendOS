#include "../include/drivers/vbe.h"

uint32_t *framebuffer;
uint32_t pitch;

uint32_t vbe_hex_from_rgb(rgb_pixel_t pixel)
{
    return (pixel.r << 16) | (pixel.g << 8) | pixel.b;
}

void vbe_init(multiboot_info_t *mbinfo)
{
    framebuffer = (uint32_t *) (uintptr_t) mbinfo->framebuffer_addr;
    pitch = mbinfo->framebuffer_pitch / sizeof(uint32_t);
}

void vbe_putpixel(uint16_t x, uint16_t y, uint32_t color)
{
    framebuffer[y * pitch + x] = color;
}

void vbe_rect(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint32_t color) 
{
    for (uint16_t i = x; i < x + width; i++) 
    {
        for (uint16_t j = y; j < y + height; j++) 
        {
            vbe_putpixel(i, j, color);
        }
    }
}
