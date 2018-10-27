
TARGET=barrierTest
OBJS=barrier.o 

#############################
CFLAGS = -Wall -Wconversion -pedantic -ansi -Werror -g -pthread
LDFLAGS=
CC=gcc

.PHONEY:clean run

$(TARGET):$(OBJS)

clean:
	rm -f $(OBJS) $(TARGET)

#############################
barrier.o:barrier.c barrier.h

