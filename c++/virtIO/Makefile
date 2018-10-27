
TARGET=virtIOTest
OBJS=virtIO_t.o binIO_t.o

#############################
CPPFLAGS = -Wall -Wconversion -pedantic -ansi -Werror -g
LDFLAGS=
CC=g++

.PHONEY:clean

$(TARGET):$(OBJS) asciiIO_t.h

clean:
	rm -f $(OBJS) $(TARGET)

#############################
$(OBJS):$(subst .o,.cpp,$(OBJS)) $(subst .o,.h,$(OBJS))

