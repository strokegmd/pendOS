#include "../include/cpu/idt.h"

idt_entry_t idt[IDT_NUM_ENTRIES];
idt_ptr_t idtp;

void idt_set_entry(uint8_t num, uint64_t handler, uint16_t sel, uint8_t flags) 
{
    idt[num].handler_lo = handler & 0xFFFF;
    idt[num].handler_hi = (handler >> 16) & 0xFFFF;
    idt[num].always0 = 0;
    idt[num].flags = flags;
    idt[num].sel = sel;
}

void idt_init()
{
    idtp.limit = (sizeof(idt_entry_t) * IDT_NUM_ENTRIES) - 1;
    idtp.base = (uint32_t) &idt;

    for (size_t i = 0; i < IDT_NUM_ENTRIES; i++) 
    {
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
