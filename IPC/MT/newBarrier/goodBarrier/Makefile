
TARGET=barrierFairTest
OBJS=barrier.o

#############################
CFLAGS = -Wall -Wconversion -pedantic -ansi -Werror -g 
LDFLAGS=-pthread
CC=gcc

.PHONEY:clean run

$(TARGET):$(OBJS)

clean:
	rm -f $(OBJS) $(TARGET)

#############################

$(OBJS):$($(OBJS):.o=.c) $($(OBJS):.o=.h)


