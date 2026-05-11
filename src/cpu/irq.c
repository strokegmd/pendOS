#include "../include/cpu/irq.h"

static interrupt_handler_t interrupt_handlers[IDT_NUM_ENTRIES];

void irq_ack(int irq_no)
{
	if (irq_no >= 12) 
    {
		outb(0xA0, 0x20);
	}

	outb(0x20, 0x20);
}

void irq_enable(uint8_t irq)
{
	uint8_t mask_master, mask_slave;

	mask_master = inb(0x21);
	mask_slave = inb(0xa1);

	if (irq > 7) 
    {
		outb(0xa1, mask_slave & ~(1 << (irq-8)));
	} 
    else 
    {
		outb(0x21, mask_master & ~(1 << irq));
	}
}

bool irq_register(uint32_t idt_index, interrupt_handler_t handler)
{
    if (idt_index >= IDT_NUM_ENTRIES) 
    {
        return false;
    }

    if (interrupt_handlers[idt_index] != 0) 
    {
        return false;
    }

    interrupt_handlers[idt_index] = handler;
    return true;
}

void irq_handler(struct regs *r)
{
    void (*handler)(struct regs * r);

    handler = interrupt_handlers[r->idt_index];
    if (handler)
    {
        handler(r);
    }

    if (r->idt_index >= 40) 
    {
        outb(0xA0, 0x20);
    }

    outb(0x20, 0x20);
}

void irq_run(struct regs *r)
{
    uint32_t idt_index = r->idt_index;
    if (idt_index < 32) 
    {
        return;
    }

    if (idt_index >= 32 && idt_index <= 47) 
    {
        irq_handler(r);
        return;
    }

    if (interrupt_handlers[r->idt_index] != 0) 
    {
        interrupt_handlers[r->idt_index](r);
    }
}
