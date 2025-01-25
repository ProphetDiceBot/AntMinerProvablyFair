
CC = arm-linux-gnueabihf-gcc
CFLAGS = -Wall -O2

all: firmware

firmware: main.o asic.o driver-bitmain.o
	$(CC) $(CFLAGS) -o firmware main.o asic.o driver-bitmain.o

main.o: main.c asic.h
	$(CC) $(CFLAGS) -c main.c

asic.o: asic.c asic.h driver-bitmain.h
	$(CC) $(CFLAGS) -c asic.c

driver-bitmain.o: driver-bitmain.c driver-bitmain.h
	$(CC) $(CFLAGS) -c driver-bitmain.c

clean:
	rm -f *.o firmware
