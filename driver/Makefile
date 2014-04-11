#         (C) 2014 JinDongHuang

INCLUDEDIR  = ../include

AR      = arm-linux-ar
LD      = arm-linux-ld
LDFLAGS = -s -x
CC      = arm-linux-gcc
CFLAGS  = -Wall -I$(INCLUDEDIR) -nostdinc

%.o:%.c
	$(CC) $(CFLAGS) -c $< -o $@

OBJS    = sdram.o clock.o uart.o led.o bglight.o lcd.o \
	  pwm.o

drivers.a:$(OBJS)
	$(AR) rcs $@ $^
	sync

clean:
	rm -f *.o *.a

