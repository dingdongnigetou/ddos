#         (C) 2014 JinDongHuang

INCLUDEDIR  = ../include

AR      = arm-linux-ar
CC      = arm-linux-gcc
CFLAGS  = -Wall -I$(INCLUDEDIR) -nostdinc
OBJS    = sys_call.o

%.o:%.c
	$(CC) $(CFLAGS) -c $< -o $@

sys_call.a:$(OBJS)
	$(AR) rcs $@ $^
	sync
clean:
	rm -f *.o *.a

