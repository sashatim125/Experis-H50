
TARGET=carsTest
OBJS=car_t.o bus_t.o private_t.o

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

