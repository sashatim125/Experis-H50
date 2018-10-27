
TARGET=list_test
OBJS=list.o list_itr.o list_functions.o

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
list.o:list.h list_common.h

list_itr.h:list.h
list_itr.o:list_itr.h list_common.h

list_functions.h:list.h list_itr.h
list_functions.o:list.h list_itr.h list_functions.h

