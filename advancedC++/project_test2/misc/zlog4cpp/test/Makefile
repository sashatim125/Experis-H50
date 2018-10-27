
TARGET=zlog4c_test
OBJS=zlog4c.o 

#############################-Wall -Wconversion -pedantic -ansi  -Werror
CFLAGS = -Wall -Wconversion -ansi -Werror -g -pthread #-D NDEBUG 
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
zlog4c.o:zlog4c.h


