#ifndef __SYSCALLS_H
#define __SYSCALLS_H

#include "irq.h"
#include "../drivers/tty.h"

void syscall();
void syscall_init();

#endif
