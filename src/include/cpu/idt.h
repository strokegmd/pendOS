//kukuvagmd, [6/6/24 12:19 PM]
#ifndef __IDT_H
#define __IDT_H

#define IDT_NUM_ENTRIES 256

#include "../system.h"
#include <stdint.h>

/**
 * Macro to set an IDT entry with the given index, handler address, selector, and flags.
 */
#define SET_IDT_ENTRY(idx) \
    set_idt_entry(idx, (uint32_t) &interrupt_handler_##idx,\
                  0x08, 0x8E);

/**
 * Macro to declare an interrupt handler function with the given index.
 */
#define DECLARE_INTERRUPT_HANDLER(i) void interrupt_handler_##i(void)

/**
 * Enables all interrupts.
 */
inline void interrupt_enable_all() { __asm__ volatile("sti"); }

/**
 * Disables all interrupts.
 */
inline void interrupt_disable_all() { __asm__ volatile("cli"); }

/**
 * Structure to represent an IDT entry.
 */
typedef struct {
    uint16_t handler_lo; /**< Lower 16 bits of the handler address */
    uint16_t sel; /**< Selector for the handler */
    uint8_t always0; /**< Always zero */
    uint8_t flags; /**< Flags for the handler */
    uint16_t handler_hi; /**< Upper 16 bits of the handler address */
} __attribute__((packed)) idt_entry_t;

/**
 * Structure to represent an IDT pointer.
 */
typedef struct {
    uint16_t limit; /**< Limit of the IDT */
    uint32_t base; /**< Base address of the IDT */
} __attribute__((packed)) idt_ptr_t;

/**
 * Array of IDT entries.
 */
idt_entry_t idt[IDT_NUM_ENTRIES];

/**
 * IDT pointer.
 */
idt_ptr_t idtp;

/**
 * External function to load the IDT.
 * @param idt_ptr_addr Address of the IDT pointer
 */
extern void idt_load(idt_ptr_t* idt_ptr_addr);

/**
 * Declare interrupt handlers for indices 0-19 and 32-47.
 */
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

/**
 * Sets an IDT entry with the given index, handler address, selector, and flags.
 * @param num Index of the IDT entry
 * @param handler Address of the handler function
 * @param sel Selector for the handler
 * @param flags Flags for the handler
 */
void set_idt_entry(uint8_t num, uint64_t handler, uint16_t sel, uint8_t flags) {
    idt[num].handler_lo = handler & 0xFFFF;
    idt[num].handler_hi = (handler >> 16) & 0xFFFF;
    idt[num].always0 = 0;
    idt[num].flags = flags;
    idt[num].sel = sel;
}

/**
 * Installs the IDT.
 */
void idt_install() {
    idtp.limit = (sizeof(idt_entry_t) * IDT_NUM_ENTRIES) - 1;
    idtp.base = (uint32_t)&idt;

    for (uint32_t i = 0; i < IDT_NUM_ENTRIES; i++) {
        idt[i].handler_lo = 0;
        idt[i].handler_hi = 0;
        idt[i].always0 = 0;
        idt[i].flags = 0;
        idt[i].sel = 0;
    }

    SET_IDT_ENTRY(0);
    SET_IDT_ENTRY(1);
    SET_IDT_ENTRY(2);
    SET_IDT_ENTRY(3);
    SET_IDT_ENTRY(4);
    SET_IDT_ENTRY(5);
    SET_IDT_ENTRY(6);
    SET_IDT_ENTRY(7);
    SET_IDT_ENTRY(8);
    SET_IDT_ENTRY(9);
    SET_IDT_ENTRY(10);
    SET_IDT_ENTRY(11);
    SET_IDT_ENTRY(12);
    SET_IDT_ENTRY(13);
    SET_IDT_ENTRY(14);
    SET_IDT_ENTRY(15);
    SET_IDT_ENTRY(16);
    SET_IDT_ENTRY(17);
    SET_IDT_ENTRY(18);
    SET_IDT_ENTRY(19);

    //  kukuvagmd, [6/6/24 12:19 PM]

    SET_IDT_ENTRY(32);
    SET_IDT_ENTRY(33);
    SET_IDT_ENTRY(34);
    SET_IDT_ENTRY(35);
    SET_IDT_ENTRY(36);
    SET_IDT_ENTRY(37);
    SET_IDT_ENTRY(38);
    SET_IDT_ENTRY(39);
    SET_IDT_ENTRY(40);
    SET_IDT_ENTRY(41);
    SET_IDT_ENTRY(42);
    SET_IDT_ENTRY(43);
    SET_IDT_ENTRY(44);
    SET_IDT_ENTRY(45);
    SET_IDT_ENTRY(46);
    SET_IDT_ENTRY(47);

    outb(0x20, 0x10);
    outb(0xA0, 0x10);
    outb(0x21, 0x20);
    outb(0xA1, 0x28);
    outb(0x21, 0x04);
    outb(0xA1, 0x02);
    outb(0x21, 0x01);
    outb(0xA1, 0x01);
    outb(0x21, 0x0);
    outb(0xA1, 0x0);

    idt_load(&idtp);
}

#endif