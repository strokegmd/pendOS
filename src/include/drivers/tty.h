#ifndef __TTY_H
#define __TTY_H

#include <stdint.h>
#include "../lib/string.h"

uint8_t* vidmem = (uint8_t*) 0xb8000;

typedef struct {
    const uint8_t width;
    const uint8_t height;
    const uint16_t screensize;
    uint8_t* video;
} tty_screen_t;

typedef struct {
    uint16_t x;
    uint16_t y;
    uint16_t color;
} tty_cursor_t;

typedef enum {
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

tty_screen_t screen = { 80, 25, 80 * 25, (uint8_t*) 0xb8000 };
tty_cursor_t cursor = { 0, 0, TTY_COLOR_LIGHT_GREY };

void tty_scrollup();
size_t strlen(uint8_t* str);

/*
Gets color in TTY mode
*/
tty_color_t tty_get_color(tty_color_t fg, tty_color_t bg) {
    return fg | bg << 4;
}

/*
Sets cursor color in TTY mode.
*/
void tty_set_color(uint16_t color) {
    cursor.color = color;
}

/*
Updates cursor position in TTY mode
*/
void tty_update_cursor() {
    uint16_t pos = cursor.y * screen.width + cursor.x;

    outb(0x3D4, 0x0F);
    outb(0x3D5, (uint8_t) (pos & 0xFF));
    outb(0x3D4, 0x0E);
    outb(0x3D5, (uint8_t) ((pos >> 8) & 0xFF));
}

/*
Clears screen in TTY mode
*/
void tty_clear() {
    for (size_t i = 0; i < screen.width * screen.height * 2; i += 2) {
        screen.video[i] = ' ';
        screen.video[i + 1] = cursor.color;
    }
}

/*
Sets cursor position
*/
void tty_set_cursor(uint16_t x, uint16_t y) {
    cursor.x = x;
    cursor.y = y;
}

/*
Prints character in TTY mode
*/
void tty_putchar(uint8_t character) {
    uint16_t pos = (cursor.x + cursor.y * screen.width) * 2;

    switch (character) {
        case '\n':
            cursor.x = 0;
            cursor.y++;

            tty_set_color(tty_get_color(TTY_COLOR_LIGHT_GREY, TTY_COLOR_BLACK));
            tty_putchar(' ');
            tty_set_cursor(cursor.x-1, cursor.y);

            if (cursor.y >= screen.height) {
                cursor.y -= 1;
                tty_scrollup();
            }
            break;
        default:
            screen.video[pos] = character;
            screen.video[pos + 1] = cursor.color;
            cursor.x++;
            if (cursor.x >= screen.width) {
                cursor.x = 0;
                cursor.y++;
            }
            break;
    }

    tty_update_cursor();
}

/*
Prints string
*/
void tty_write_string(uint8_t* str) {
    for (size_t i = 0; i < strlen(str); i++) {
        tty_putchar(str[i]);
    }
}

/*
Scrolls the screen up by one line
*/
void tty_scrollup() {
    size_t offset = screen.width * 2;
    memcpy(screen.video, screen.video + offset, offset * (screen.height - 1));
    for (size_t i = 0; i < screen.width; i++) {
        screen.video[offset * (screen.height - 1) + i * 2] = ' ';
        screen.video[offset * (screen.height - 1) + i * 2 + 1] = cursor.color;
    }
}

#endif