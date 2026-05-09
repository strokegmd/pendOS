#ifndef __GDT_H
#define __GDT_H

#include <stdint.h>

typedef struct 
{
    uint16_t limit_low;
    uint16_t base_low;
    uint8_t base_middle;
    uint8_t access;
    uint8_t granularity;
    uint8_t base_high;
} __attribute__((packed)) gdt_entry;

typedef struct 
{
    uint16_t limit;
    uint32_t base;
} __attribute__((packed)) gdt_ptr;

extern void gdt_flush(gdt_ptr *gdt_ptr_addr);
void gdt_set_gate(int32_t num, uint32_t base, uint32_t limit, uint8_t access, uint8_t gran);
void gdt_init();

#endif
