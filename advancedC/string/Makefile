
TARGET=stringTest
OBJS=myString.o

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
myString.o:myString.h 



