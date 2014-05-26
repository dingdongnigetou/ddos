SECTIONS {
    . = 0xC0000000;
    
	.text :
	{
		boot/boot.o
		* (.text)
	}
	. = ALIGN(4);

	.rodata :
	{
		* (.rodata)
	}
	. = ALIGN(4);

	.data :
	{
		* (.data)
	}
	. = ALIGN(4);

    bss_start = .;
	.bss :
	{
		* (.bss)
		* (.common)
	}
    bss_end = .;
}

