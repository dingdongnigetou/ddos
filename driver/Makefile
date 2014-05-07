#         (C) 2014 JinDongHuang

INCLUDEDIR  = ../include
LCDDIR      = ./lcd

AR      = arm-linux-ar
CC      = arm-linux-gcc
CFLAGS  = -Wall -I$(INCLUDEDIR) -nostdinc
OBJS    = sdram.o clock.o uart.o led.o pwm.o nand.o \
	  $(LCDDIR)/bg_light.o $(LCDDIR)/lcd.o

%.o:%.c
	$(CC) $(CFLAGS) -c $< -o $@

drivers.a:$(OBJS)
	$(AR) rcs $@ $^
	sync

clean:
	rm -f *.o *.a
	rm -f $(LCDDIR)/*.o

