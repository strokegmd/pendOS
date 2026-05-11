void main(void)
{
	char *text = "test";
	
	asm volatile("int $0x80": :"a"(4), "b"(0), "c"(text), "d"(4));
	
	asm volatile("xor %eax, %eax\n");
	asm volatile("int $0x80": :"a"(1), "b"(0));

	for(;;);
}
