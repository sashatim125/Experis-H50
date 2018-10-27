
TARGET=vectorTest
OBJS=vector.o ../../ds/DLinkList/DLinkList.o

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
vector.o:vector.h 
../../ds/DLinkList/DLinkList.o:../../ds/DLinkList/DLinkList.h


