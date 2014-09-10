#               (C) 2014 JinDongHuang

BOOTDIR     = ./boot
INITDIR     = ./init
INCLUDEDIR  = ./include
DRIVERDIR   = ./driver
LIBDIR      = ./lib
MMDIR       = ./mm
PMDIR       = ./pm
SYSDIR      = ./sys
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

ddos.elf:$(BOOTDIR)/boot.o $(INITDIR)/main.o $(DRIVERDIR)/drivers.a \
	 $(LIBDIR)/lib.a $(MMDIR)/mm.a $(SYSDIR)/sys_call.a $(PMDIR)/pm.a
	$(LD) $(LDFLAGS) $^ -o $@

%.o:%.S
	$(CC) $(CFLAGS) -c $< -o $@

%.o:%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(DRIVERDIR)/drivers.a:
	(cd $(DRIVERDIR); make)

$(LIBDIR)/lib.a:
	(cd $(LIBDIR); make)

$(MMDIR)/mm.a:
	(cd $(MMDIR); make)

$(PMDIR)/pm.a:
	(cd $(PMDIR); make)

$(SYSDIR)/sys_call.a:
	(cd $(SYSDIR); make)

clean:
	rm -rf $(BOOTDIR)/*.o $(INITDIR)/*.o  *.elf *.bin *.dis
	(cd $(DRIVERDIR); make clean)
	(cd $(LIBDIR); make clean)
	(cd $(MMDIR); make clean)
	(cd $(SYSDIR); make clean)
	(cd $(PMDIR); make clean)

