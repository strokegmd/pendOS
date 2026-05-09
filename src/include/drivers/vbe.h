#ifndef __VBE_H
#define __VBE_H

#include <stdint.h>
#include "../grub/multiboot.h"

typedef struct 
{
    uint8_t r;
    uint8_t g;
    uint8_t b;
} rgb_pixel_t;

uint32_t vbe_hex_from_rgb(rgb_pixel_t pixel);
void vbe_init(multiboot_info_t *mbinfo);
void vbe_putpixel(uint16_t x, uint16_t y, uint32_t color);
void vbe_rect(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint32_t color);

#endif
