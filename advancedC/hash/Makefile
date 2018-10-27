
TARGET=testHashMap
OBJS= ../list/list.o ../list/list_itr.o ../list/list_functions.o HashMap.o

#############################
CFLAGS = -Wall -Wconversion -pedantic -ansi -Werror -g -I../list
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

HashMap.o:HashMap.h HashMap.h ../list/list.h ../list/list_itr.h ../list/list_functions.h



