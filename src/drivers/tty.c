#include "../include/drivers/tty.h"
#include "../include/lib/string.h"

uint8_t *vidmem = (uint8_t*) VGA_MEMORY;
tty_cursor_t cursor = { 0, 0, TTY_COLOR_LIGHT_GREY };

void tty_init(void)
{
    tty_clear();
}

tty_color_t tty_get_color(tty_color_t fg, tty_color_t bg)
{
    return fg | bg << 4;
}

void tty_clear(void)
{
    for (size_t i = 0; i < VGA_WIDTH * VGA_HEIGHT * 2; i += 2)
    {
        vidmem[i] = ' ';
        vidmem[i+1] = cursor.color;
    }
}

void tty_putchar(char c)
{
    uint8_t position = (cursor.y * VGA_WIDTH + cursor.x) * 2;

    if (c == '\n') 
    {
        cursor.x = 0;
        cursor.y++;
    }
    else 
    {
        vidmem[position] = c;
        cursor.x++;
    }
}

void tty_write_string(const char *string)
{
    for (size_t i = 0; i < strlen(string); i++)
    {
        tty_putchar(string[i]);
    }
}
