
TARGET=WaitableCyclicQueue
OBJS=ShMemWCQueue.o memAlloc.o sysutils.o 

#############################
CFLAGS = -Wall -Wconversion -pedantic -ansi -Werror -g
LDFLAGS=
CC=gcc

.PHONEY:clean run

$(TARGET):$(OBJS)

clean:
	rm -f $(OBJS) $(TARGET)

#############################
ShMemWCQueue.o:ShMemWCQueue.c ShMemWCQueue.h
memAlloc.o:memAlloc.c memAlloc.h
sysutils.o:sysutils.c sysutils.h


