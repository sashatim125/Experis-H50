
TARGET=PTETest

SRCDIR=./src
OBJS=$(SRCDIR)/PeriodicExecutor.o $(SRCDIR)/TaskClass.o $(SRCDIR)/TimeUtils.o ../heap/heap.o ../vector/vector.o\
../zlog/zlog4c.o ../list/list.o

#############################
CFLAGS = -Wall -Wconversion -pedantic -ansi -Werror -g -I$(SRCDIR)/inc -I./inc -I../lib/inc -I../zlog -std=c99
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
$(SRCDIR)/PeriodicExecutor.o:./inc/PeriodicExecutor.h $(SRCDIR)/PeriodicExecutor.c ../lib/libDS.so \
$(SRCDIR)/inc/PeriodicExecutorShared.h $(SRCDIR)/inc/TaskClass.h $(SRCDIR)/TaskClass.o

$(SRCDIR)/TaskClass.o:$(SRCDIR)/inc/TaskClass.h $(SRCDIR)/TaskClass.c \
$(SRCDIR)/inc/PeriodicExecutorShared.h $(SRCDIR)/inc/TimeUtils.h $(SRCDIR)/TimeUtils.o

$(SRCDIR)/TimeUtils.o:$(SRCDIR)/TimeUtils.c $(SRCDIR)/inc/TimeUtils.h




