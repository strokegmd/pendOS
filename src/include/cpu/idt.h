#ifndef __IDT_H
#define __IDT_H

#define IDT_NUM_ENTRIES 256

#include <stdint.h>
#include <stddef.h>

#include "../cpu/system.h"

#define SET_IDT_ENTRY(idx) \
    idt_set_entry(idx, (uint32_t) &interrupt_handler_##idx,\
                  0x08, 0x8E);

#define DECLARE_INTERRUPT_HANDLER(i) void interrupt_handler_##i(void)

inline void interrupt_enable_all() { __asm__ volatile("sti"); }

inline void interrupt_disable_all() { __asm__ volatile("cli"); }

typedef struct 
{
    uint16_t handler_lo;
    uint16_t sel;
    uint8_t always0;
    uint8_t flags;
    uint16_t handler_hi;
} __attribute__((packed)) idt_entry_t;

typedef struct 
{
    uint16_t limit;
    uint32_t base;
} __attribute__((packed)) idt_ptr_t;

extern void idt_load(idt_ptr_t *idt_ptr_addr);
void idt_set_entry(uint8_t num, uint64_t handler, uint16_t sel, uint8_t flags);
void idt_init();

DECLARE_INTERRUPT_HANDLER(0);
DECLARE_INTERRUPT_HANDLER(1);
DECLARE_INTERRUPT_HANDLER(2);
DECLARE_INTERRUPT_HANDLER(3);
DECLARE_INTERRUPT_HANDLER(4);
DECLARE_INTERRUPT_HANDLER(5);
DECLARE_INTERRUPT_HANDLER(6);
DECLARE_INTERRUPT_HANDLER(7);
DECLARE_INTERRUPT_HANDLER(8);
DECLARE_INTERRUPT_HANDLER(9);
DECLARE_INTERRUPT_HANDLER(10);
DECLARE_INTERRUPT_HANDLER(11);
DECLARE_INTERRUPT_HANDLER(12);
DECLARE_INTERRUPT_HANDLER(13);
DECLARE_INTERRUPT_HANDLER(14);
DECLARE_INTERRUPT_HANDLER(15);
DECLARE_INTERRUPT_HANDLER(16);
DECLARE_INTERRUPT_HANDLER(17);
DECLARE_INTERRUPT_HANDLER(18);
DECLARE_INTERRUPT_HANDLER(19);

DECLARE_INTERRUPT_HANDLER(32);
DECLARE_INTERRUPT_HANDLER(33);
DECLARE_INTERRUPT_HANDLER(34);
DECLARE_INTERRUPT_HANDLER(35);
DECLARE_INTERRUPT_HANDLER(36);
DECLARE_INTERRUPT_HANDLER(37);
DECLARE_INTERRUPT_HANDLER(38);
DECLARE_INTERRUPT_HANDLER(39);
DECLARE_INTERRUPT_HANDLER(40);
DECLARE_INTERRUPT_HANDLER(41);
DECLARE_INTERRUPT_HANDLER(42);
DECLARE_INTERRUPT_HANDLER(43);
DECLARE_INTERRUPT_HANDLER(44);
DECLARE_INTERRUPT_HANDLER(45);
DECLARE_INTERRUPT_HANDLER(46);
DECLARE_INTERRUPT_HANDLER(47);

#endif
