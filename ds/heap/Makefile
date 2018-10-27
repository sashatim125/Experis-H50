
TARGET=heapTest
OBJS=heap.o ../vector/vector.o

#############################
CFLAGS = -Wall -Wconversion -pedantic -ansi -Werror -g
LDFLAGS=
CC=gcc

.PHONEY:clean run

$(TARGET):$(OBJS)

clean:
	rm -f $(TARGET) $(OBJS) $(TARGET).out
	
run:$(TARGET)
	mv $(TARGET) $(TARGET).out
	./$(TARGET).out

#############################
heap.o:heap.h 

heap.h:../vector/vector.h

../vector/vector.o:../vector/vector.h


