#               (C) 2014 JinDongHuang

CC       = arm-linux-gcc
LD       = arm-linux-ld
OBJCOPY  = arm-linux-objcopy
OBJDUMP  = arm-linux-objdump

CFLAGS  += -Wall
LDFLAGS += -Ttext=0
ODFLAGS += -D
OCFLAGS += -O binary

BOOT     = ./boot


install:ddos.bin

ddos.bin:$(BOOT)/boot.o
	$(LD) $(LDFLAGS) $< -o ddos.elf
	$(OBJCOPY) $(OCFLAGS) ddos.elf $@
	$(OBJDUMP) $(ODFLAGS) ddos.elf > ddos.dis

$(BOOT)/boot.o:$(BOOT)/boot.s
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(BOOT)/*.o
	rm -rf *.elf
	rm -rf *.bin
	rm -rf *.dis

