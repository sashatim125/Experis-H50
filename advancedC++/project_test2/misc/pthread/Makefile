
TARGET=libmypthread.so
OBJS=pthread_class.o
INCDIR=-I../../lib/inc -I../../inc 

#############################
CPPFLAGS =  -std=c++03 -Wall -Wconversion -pedantic -ansi -Werror  $(INCDIR) -fPIC
CC=g++

.PHONEY:clean

$(TARGET):$(OBJS)
	$(CC) $^ $(CPPFLAGS) -shared -o $@
	rm -f $(OBJS)

clean:
	rm -f $(OBJS) $(TARGET)

#############################


