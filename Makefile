#               (C) 2014 HuangJinDong

CC=arm-linux-gcc
CFLAGS += -Wall

BOOT=./boot

install:$(BOOT)/boot.o
	$(CC) $(CFLAGS) $^ -o ddos 

$(BOOT)/boot.o:$(BOOT)/boot.c


clean:
	rm -r $(BOOT)/*.o

