#ifndef __STRING_H
#define __STRING_H

#include <stddef.h>
#include <stdint.h>

size_t strlen(const char *string);
void memset(void *src, uint8_t val, uint32_t len);
void *memcpy(void *dst, void *src, uint32_t len);
int memcmp(void *ptr1, void *ptr2, size_t num);
void *memmove(void *dst, void *src, size_t n);

#endif
