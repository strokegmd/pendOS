#ifndef __KEYBOARD_H
#define __KEYBOARD_H

#define KEYBOARD_DATA_PORT 0x60
#define KEYBOARD_STATUS_PORT 0x64

#include <stdint.h>
#include <stdbool.h>

#include "../../cpu/system.h"
#include "../../cpu/irq.h"

void keyboard_init();
char keyboard_get_key();

#endif
