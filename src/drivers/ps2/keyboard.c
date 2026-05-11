#include "../../include/drivers/ps2/keyboard.h"

bool shift = false;
bool caps  = false;

const char keymap[128] = {
    0, 27, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', '\b', '\t', 
    'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n', 0, 
    'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`', 0, 
    '\\', 'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/', 0, '*', 
    0, ' ', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '-', 
    0, 0, 0, '+', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

const char keymap_shift[128] = {
    0, 27, '!', '@', '#', '$', '%', '^', '&', '*', '(', ')', '_', '+', '\b', '\t', 
    'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P', '{', '}', '\n', 0, 
    'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', ':', '"', '~', 0, 
    '\\', 'Z', 'X', 'C', 'V', 'B', 'N', 'M', ',', '.', '/', 0, '*', 
    0, ' ', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '-', 
    0, 0, 0, '+', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

const char keymap_caps[128] = {
    0, 27, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', '\b', '\t', 
    'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P', '[', ']', '\n', 0, 
    'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', ';', '\'', '`', 0, 
    '\\', 'Z', 'X', 'C', 'V', 'B', 'N', 'M', ',', '.', '/', 0, '*', 
    0, ' ', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '-', 
    0, 0, 0, '+', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

volatile char key_buffer[128];
volatile char buffer_head = 0;
volatile char buffer_tail = 0;

void keyboard_handler()
{
    uint8_t scancode = inb(KEYBOARD_DATA_PORT);

    if (scancode & 0x80) 
    {
        shift = scancode == 0xAA ? false : shift;
    } 
    else 
    {
        shift = scancode == 0x2A ? true : shift;
        caps = scancode == 0x3A ? !caps : caps;
        char c = shift ? keymap_shift[scancode] : keymap[scancode];
        c = caps ? keymap_caps[scancode] : c;
        if (c) 
        {
            key_buffer[buffer_head] = c;
            buffer_head = (buffer_head + 1) % 128;
        }
    }
}

char keyboard_get_key()
{
    if (buffer_head == buffer_tail) 
    {
        return 0;
    } 
    else 
    {
        char c = key_buffer[buffer_tail];
        buffer_tail = (buffer_tail + 1) % 128;
        return c;
    }
}

void keyboard_init()
{
    irq_register(33, keyboard_handler);
}
