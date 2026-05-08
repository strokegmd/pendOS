#include "../include/lib/string.h"

size_t strlen(char *string) 
{
    size_t i = 0;
    while (string[i])
        i++;

    return i;
}
