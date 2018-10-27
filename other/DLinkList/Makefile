
TARGET=DLinkListTest
OBJS=DLinkList.o DLinkListItr.o DLinkListItrFunc.o

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
DLinkList.o:DLinkList.h DLinkListCommon.h

DLinkListItr.h:DLinkList.h
DLinkListItr.o:DLinkListItr.h DLinkListCommon.h

DLinkListItrFunc.h:DLinkList.h DLinkListItr.h
DLinkListItrFunc.h:DLinkList.h DLinkListItr.h DLinkListItrFunc.h

