#ifndef __TTY_H
#define __TTY_H

#include <stdint.h>
#include <stddef.h>

#define VGA_MEMORY 0xB8000
#define VGA_WIDTH  80
#define VGA_HEIGHT 25

typedef enum 
{
    TTY_COLOR_BLACK = 0,
    TTY_COLOR_BLUE = 1,
    TTY_COLOR_GREEN = 2,
    TTY_COLOR_CYAN = 3,
    TTY_COLOR_RED = 4,
    TTY_COLOR_MAGENTA = 5,
    TTY_COLOR_BROWN = 6,
    TTY_COLOR_LIGHT_GREY = 7,
    TTY_COLOR_DARK_GREY = 8,
    TTY_COLOR_LIGHT_BLUE = 9,
    TTY_COLOR_LIGHT_GREEN = 10,
    TTY_COLOR_LIGHT_CYAN = 11,
    TTY_COLOR_LIGHT_RED = 12,
    TTY_COLOR_LIGHT_MAGENTA = 13,
    TTY_COLOR_LIGHT_BROWN = 14,
    TTY_COLOR_WHITE = 15,
} tty_color_t;

typedef struct 
{
    size_t x;
    size_t y;
    uint8_t color;
} tty_cursor_t;

void tty_init(void);
tty_color_t tty_get_color(tty_color_t fg, tty_color_t bg);
void tty_clear(void);
void tty_putchar(char c);
void tty_write_string(char *string);

#endif