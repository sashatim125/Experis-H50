
TARGET=mystringTest
OBJS=specialString.o simpleString.o stringManip.o toUpperString.o jumpString.o
INCDIR=../

#############################
CPPFLAGS =  -std=c++03 -Wall -Wconversion -pedantic -ansi -Werror  -I $(INCDIR) #-g
LDFLAGS= 
CC=g++

.PHONEY:clean

$(TARGET):$(OBJS)

clean:
	rm -f $(OBJS) $(TARGET)

#############################
$(OBJS):$(subst .o,.cpp,$(OBJS)) $(subst .o,.h,$(OBJS))

