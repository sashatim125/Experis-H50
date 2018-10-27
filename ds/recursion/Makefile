
TARGET=flip_list
OBJS=
#############################
CFLAGS = -Wall -Wconversion -pedantic -ansi -Werror
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






