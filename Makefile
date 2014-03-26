#               (C) 2014 JinDongHuang

BOOT     = ./boot
INIT     = ./init
INCLUDE  = ./include
DRIVER   = ./driver

CC       = arm-linux-gcc
LD       = arm-linux-ld
OBJCOPY  = arm-linux-objcopy
OBJDUMP  = arm-linux-objdump

CFLAGS  += -Wall
CFLAGS  += -I$(INCLUDE)
LDFLAGS += -Ttext=0
ODFLAGS += -D
OCFLAGS += -O binary

install:ddos.bin

ddos.bin:ddos.elf
	$(OBJCOPY) $(OCFLAGS) ddos.elf $@
	$(OBJDUMP) $(ODFLAGS) ddos.elf > ddos.dis

ddos.elf:$(BOOT)/boot.o $(BOOT)/clock.o $(INIT)/main.o $(DRIVER)/uart.o $(DRIVER)/led.o
	$(LD) $(LDFLAGS) $^ -o ddos.elf

%.o/:%.S
	$(CC) $(CFLAGS) -c $< -o $@

%.o:%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(BOOT)/*.o
	rm -rf $(INIT)/*.o
	rm -rf $(DRIVER)/*.o
	rm -rf *.elf *.bin *.dis

