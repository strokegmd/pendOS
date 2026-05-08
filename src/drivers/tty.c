#include "../include/drivers/tty.h"
#include "../include/lib/string.h"

uint16_t *vidmem = (uint16_t *) VGA_MEMORY;
tty_cursor_t cursor = { 0, 0, TTY_COLOR_LIGHT_GRAY };

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
    for (size_t i = 0; i < VGA_WIDTH * VGA_HEIGHT; i++)
    {
        vidmem[i] = (cursor.color << 8) | ' ';
    }
}

void tty_putchar(char c)
{
    uint16_t position = (cursor.y * VGA_WIDTH + cursor.x);

    if (c == '\n') 
    {
        cursor.x = 0;
        cursor.y++;
    }
    else 
    {
        vidmem[position] = (cursor.color << 8) | c;
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

void tty_set_color(tty_color_t fg, tty_color_t bg)
{
    cursor.color = tty_get_color(fg, bg);
}
