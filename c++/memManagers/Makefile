
TARGET=memManagersTest
OBJS=memPage_t.o memPool_t.o

#############################
CPPFLAGS = -Wall -Wconversion -pedantic -ansi -Werror -g
LDFLAGS=
CC=g++

.PHONEY:clean

$(TARGET):$(OBJS)

clean:
	rm -f $(OBJS) $(TARGET)

#############################
$(OBJS):$(subst .o,.cpp,$(OBJS)) $(subst .o,.h,$(OBJS))

