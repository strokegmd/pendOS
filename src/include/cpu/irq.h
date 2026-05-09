#ifndef __IRQ_H
#define __IRQ_H

#include <stdbool.h>
#include "idt.h"

typedef struct regs 
{
    uint32_t gs, fs, es, ds;
    uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax;
    uint32_t idt_index, err_code;
    uint32_t eip, cs, eflags, useresp, ss;
} registers_t;

typedef void (*interrupt_handler_t)(struct regs* r);

void irq_ack(int irq_no);
void irq_enable(uint8_t irq);
bool irq_register(uint32_t idt_index, interrupt_handler_t handler);
void irq_handler(struct regs *r);
void irq_run(struct regs *r);

#endif
