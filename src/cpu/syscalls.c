#include "../include/cpu/syscalls.h"

void syscall(struct regs *r)
{
    if (r->eax == 4)
    {
        tty_write_string("write");
    }
    else
    {
        tty_write_string("unknown syscall");
    }
}

void syscall_init()
{
    irq_register(0x80, syscall);
}
