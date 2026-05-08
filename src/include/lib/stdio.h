#ifndef __STDIO_H
#define __STDIO_H

#include <limits.h>
#include <stdarg.h>

#include "../drivers/tty.h"
#include "../lib/string.h"

int printf(const char *format, ...);

#endif
