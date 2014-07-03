#         (C) 2014 JinDongHuang

INCLUDEDIR  = ../include
LCDDIR      = ./lcd
IRQDIR      = ./irq

AR      = arm-linux-ar
CC      = arm-linux-gcc
CFLAGS  = -Wall -I$(INCLUDEDIR) -nostdinc
OBJS    = sdram.o clock.o uart.o led.o nand.o  \
	  $(LCDDIR)/bg_light.o $(LCDDIR)/lcd.o \
	  $(LCDDIR)/font8x8.o $(LCDDIR)/pwm.o  \
	  $(IRQDIR)/irq.o $(IRQDIR)/irqm.o     \
	  fiq.o timer.o

%.o:%.c
	$(CC) $(CFLAGS) -c $< -o $@
%.o:%.S
	$(CC) $(CFLAGS) -c $< -o $@

drivers.a:$(OBJS)
	$(AR) rcs $@ $^
	sync

clean:
	rm -f *.o *.a
	rm -f $(LCDDIR)/*.o
	rm -f $(IRQDIR)/*.o

