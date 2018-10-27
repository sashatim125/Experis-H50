
TARGET1=LgSensorsLib.so
OBJS1=LgSensorsLib.o
TARGET2=PhillipsControllersLib.so
OBJS2=PhillipsControllersLib.o

TARGET3=DBLogLib.so
OBJS3=DBLogLib.o

INCDIR=../../lib/inc ../../inc 

#############################
CPPFLAGS = -MMD -std=c++03 -Wall -Wconversion -pedantic -ansi -Werror  $(patsubst %,-I% ,$(INCDIR)) -fPIC #-g
CC=g++

.PHONEY:clean all

all : $(TARGET1) $(TARGET2) $(TARGET3)

$(TARGET1):$(OBJS1)
	$(CC) $^ $(CPPFLAGS) -shared -o $@
#	rm -f $(OBJS1)

$(TARGET2):$(OBJS2)
	$(CC) $^ $(CPPFLAGS) -shared -o $@
#	rm -f $(OBJS2)

$(TARGET3):$(OBJS3)
	$(CC) $^ $(CPPFLAGS) -shared -o $@
#	rm -f $(OBJS3)


clean:
	rm -f $(OBJS1) $(OBJS2) $(OBJS3) $(TARGET1) $(TARGET2) $(TARGET3)

#############################


