
TARGET=string_tTest
OBJS=string_t.o 

#############################
CPPFLAGS = -Wall -Wconversion -pedantic -ansi -Werror -g
LDFLAGS=
CC=g++

.PHONEY:clean

$(TARGET):$(OBJS)

clean:
	rm -f $(OBJS) $(TARGET)

#############################
string_t.o:$(subst .o,.cpp,$(OBJS)) $(subst .o,.h,$(OBJS))

