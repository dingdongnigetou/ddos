#         (C) 2014 JinDongHuang

INCLUDEDIR  = ../include

AR      = arm-linux-ar
CC      = arm-linux-gcc
CFLAGS  = -Wall -I$(INCLUDEDIR)
OBJS    = string.o vsprintf.o io.o div64.o

%.o:%.c
	$(CC) $(CFLAGS) -c $< -o $@

%.o:%.S
	$(CC) $(CFLAGS) -c $< -o $@

lib.a:$(OBJS)
	$(AR) rcs $@ $^
	sync
clean:
	rm -f *.o *.a

