#include "../include/gfx/ppm.h"

void ppm_render(uint8_t *data, uint32_t xOffset, uint32_t yOffset)
{
    // TODO: parse them from ppm through itoa
    uint32_t width = 800;
    uint32_t height = 600;
    size_t index = 0;

    for (size_t y = 0; y < height; y++)
    {
        for (size_t x = 0; x < width; x++)
        {
            uint32_t color = vbe_hex_from_rgb((rgb_pixel_t) { data[index], data[index+1], data[index+2] });
            vbe_putpixel(x + xOffset, y + yOffset, color);

            index += 4;
        }
    }
}
