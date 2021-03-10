#CROSS_COMPILE := aarch64-linux-gnu-
CROSS_COMPILE := arm-linux-gnueabihf-
ARCH:= arm
CC:=$(CROSS_COMPILE)gcc
LD:=$(CROSS_COMPILE)ld
objects =  main.o vkey.o joy.o
joy2key : $(objects)
	$(CC) -o joy2key $(objects)
$(objects) :
joy.o : joy.c
main.o : main.c
vkey.o : vkey.c

clean :
	rm joy2key $(objects)
upload :
	scp joy2key root@192.168.2.243:/storage/