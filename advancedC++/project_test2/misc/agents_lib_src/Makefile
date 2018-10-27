
TARGET2=TestAgentsLib.so
OBJS2=TestAgentsLib.o

TARGET3=DBLogLib.so
OBJS3=DBLogLib.o

INCDIR=../../lib/inc ../../inc 

#############################
CPPFLAGS =  -std=c++03 -Wall -Wconversion -pedantic -ansi -Werror  $(patsubst %,-I% ,$(INCDIR)) -fPIC #-g
CC=g++

.PHONEY:clean all

all : $(TARGET2) $(TARGET3)


$(TARGET2):$(OBJS2)
	$(CC) $^ $(CPPFLAGS) -shared -o $@
#	rm -f $(OBJS2)

$(TARGET3):$(OBJS3)
	$(CC) $^ $(CPPFLAGS) -shared -o $@
#	rm -f $(OBJS3)


clean:
	rm -f  $(OBJS2) $(OBJS3)  $(TARGET2) $(TARGET3)

#############################


