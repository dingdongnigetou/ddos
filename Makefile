#               (C) 2014 JinDongHuang

BOOTDIR     = ./boot
INITDIR     = ./init
INCLUDEDIR  = ./include
DRIVERDIR   = ./driver
LDSFILE     = ddos.lds

CC          = arm-linux-gcc
LD          = arm-linux-ld
OBJCOPY     = arm-linux-objcopy
OBJDUMP     = arm-linux-objdump

CFLAGS      = -Wall -I$(INCLUDEDIR) -nostdinc
LDFLAGS     = -T$(LDSFILE)
ODFLAGS     = -D
OCFLAGS     = -O binary

install:ddos.bin

ddos.bin:ddos.elf
	$(OBJCOPY) $(OCFLAGS) ddos.elf $@
	$(OBJDUMP) $(ODFLAGS) ddos.elf > ddos.dis

ddos.elf:$(BOOTDIR)/boot.o $(INITDIR)/main.o $(DRIVERDIR)/drivers.a
	$(LD) $(LDFLAGS) $^ -o ddos.elf

%.o/:%.S
	$(CC) $(CFLAGS) -c $< -o $@

%.o:%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(DRIVERDIR)/drivers.a:
	(cd $(DRIVERDIR); make)

clean:
	rm -rf $(BOOTDIR)/*.o $(INITDIR)/*.o  *.elf *.bin *.dis
	(cd $(DRIVERDIR); make clean)

