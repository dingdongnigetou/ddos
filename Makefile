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
INIT     = ./init

install:ddos.bin

ddos.bin:ddos.elf
	$(OBJCOPY) $(OCFLAGS) ddos.elf $@
	$(OBJDUMP) $(ODFLAGS) ddos.elf > ddos.dis

ddos.elf:$(BOOT)/boot.o $(INIT)/main.o
	$(LD) $(LDFLAGS) $^ -o ddos.elf

%.o/:%.s
	$(CC) $(CFLAGS) -c $< -o $@

%.o:%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(BOOT)/*.o
	rm -rf $(INIT)/*.o
	rm -rf *.elf
	rm -rf *.bin
	rm -rf *.dis

