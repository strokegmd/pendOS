#include "../include/cpu/system.h"

void halt()
{
    __asm__("hlt");
}

uint8_t inb(uint16_t port)
{
	uint8_t result;
	__asm__ __volatile__ ("inb %1, %0" : "=a" (result) : "dN" (port));

	return result;
}

uint16_t inw(uint16_t port)
{
	uint16_t result;

	__asm__ __volatile__ ("inw %1, %0" : "=a" (result) : "dN" (port));
	return result;
}

void outb(uint16_t port, uint8_t data)
{
	__asm__ __volatile__ ("outb %1, %0" : : "dN" (port), "a" (data));
}

void outw(uint16_t port, uint16_t data) 
{
	__asm__ __volatile__ ("outw %1, %0" : : "dN" (port), "a" (data));
}

void shutdown()
{
    outw(0xB004, 0x2000);
    outw(0x604, 0x2000);
    outw(0x4004, 0x3400);
    outw(0x600, 0x34);
}

void reboot()
{
    uint8_t good = 0x02;
    while (good & 0x02)
        good = inb(0x64);

    outb(0x64, 0xFE);
    halt();
}
