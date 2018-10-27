
TARGET1=sndpipe
TARGET2=recpipe
OBJS=pipeHeader.o pipeComm.o

#############################
CFLAGS = -Wall -Wconversion -pedantic -ansi -Werror -g
LDFLAGS=
CC=gcc

.PHONEY:clean run

$(TARGET1):$(OBJS)

$(TARGET2):$(OBJS)

clean:
	rm -f $(OBJS) $(TARGET1).out $(TARGET2).out p1 d.txt_new
	
run:$(TARGET1) $(TARGET2)
	mv $(TARGET1) $(TARGET1).out
	mv $(TARGET2) $(TARGET2).out
	./$(TARGET1).out -f d.txt -p p1 &
	./$(TARGET2).out -p p1 


#############################
pipeHeader.o:pipeHeader.c pipeHeader.h
pipeComm.o:pipeComm.c pipeComm.h


