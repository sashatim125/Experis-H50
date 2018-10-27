
TARGET=waitableQueueTest
OBJS=mutex.o cv.o waitableQueue.o stopwatch.o
INCDIR=../

#############################
CPPFLAGS =  -std=c++03 -Wall -Wconversion -pedantic -ansi -Werror  -I $(INCDIR) -fPIC#-g
LDFLAGS= -pthread
CC=g++

.PHONEY:clean

$(TARGET):$(OBJS)

clean:
	rm -f $(OBJS) $(TARGET)

#############################
$(OBJS):$(subst .o,.cpp,$(OBJS)) $(subst .o,.h,$(OBJS))

