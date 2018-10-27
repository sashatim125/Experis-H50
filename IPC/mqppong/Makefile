
TARGET=mqppong
OBJS=msg.o queue.o prod.o cons.o

#############################
CFLAGS = -Wall -Wconversion -pedantic -ansi -Werror -g
LDFLAGS=
CC=gcc

.PHONEY:clean run

$(TARGET):$(OBJS)

clean:
	rm -f $(OBJS) $(TARGET).out 
	
#run:$(TARGET1) 
#mv $(TARGET) $(TARGET).out
#./$(TARGET1).out 


#############################
msg.o:msg.c msg.h
queue.o:queue.c queue.h
prod.o:prod.c prod.h
cons.o:cons.c cons.h

