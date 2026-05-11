#include "../include/lib/string.h"

size_t strlen(const char *string)
{
    size_t i = 0;
    while (string[i])
        i++;

    return i;
}

void memset(void *src, uint8_t val, uint32_t len)
{
    uint8_t *ptr = (uint8_t *) src;
    while (len--)
        *ptr++ = val;
}

void *memcpy(void *dst, void *src, uint32_t len) 
{
    uint8_t *d = (uint8_t *) dst;
    uint8_t *s = (uint8_t *) src;
    while (len-- > 0)
        *d++ = *s++;

    return dst;
}

int memcmp(void *ptr1, void *ptr2, size_t num)
{
    uint8_t *p1 = (uint8_t *) ptr1;
    uint8_t *p2 = (uint8_t *) ptr2;

    for (size_t i = 0; i < num; i++)
    {
        if (p1[i] != p2[i])
        {
            return p1[i] - p2[i];
        }
    }

    return 0;
}

void *memmove(void *dst, void *src, size_t n)
{
    if (dst != src)
    {
        memcpy(dst, src, n);
    }

    return dst;
}
