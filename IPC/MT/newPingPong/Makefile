
TARGET=pingpong
OBJS=ppongPlayer.o waitQueue.o prod.o cons.o

#############################
CFLAGS = -Wall -Wconversion -pedantic -ansi -Werror -g -pthread
LDFLAGS=
CC=gcc

.PHONEY:clean run

$(TARGET):$(OBJS)

clean:
	rm -f $(OBJS) $(TARGET)

#############################
ppongPlayer.o:ppongPlayer.c ppongPlayer.h

waitQueue.o:waitQueue.c waitQueue.h

prod.o:prod.c prod.h waitQueue.o

cons.o:cons.c cons.h waitQueue.o


