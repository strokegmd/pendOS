#ifndef __PPM_H
#define __PPM_H

#include <stdint.h>
#include <stddef.h>

#include "../drivers/vbe.h"

void ppm_render(uint8_t *data, uint32_t xOffset, uint32_t yOffset);

#endif
