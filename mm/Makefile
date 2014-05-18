#         (C) 2014 JinDongHuang

INCLUDEDIR  = ../include

AR      = arm-linux-ar
CC      = arm-linux-gcc
CFLAGS  = -Wall -I$(INCLUDEDIR) -nostdinc
OBJS    = mmu.o

%.o:%.c
	$(CC) $(CFLAGS) -c $< -o $@

%.o:%.S
	$(CC) $(CFLAGS) -c $< -o $@

mm.a:$(OBJS)
	$(AR) rcs $@ $^
	sync
clean:
	rm -f *.o *.a

