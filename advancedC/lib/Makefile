
CC=gcc

CFLAGS= -Wall -Wconversion -pedantic -ansi -Werror 

OFLAGS= -c -fPIC

SOFLAGS= -shared

OBJECTS= bin_tree.o list.o list_itr.o list_functions.o stack.o vector.o heap.o HashMap.o

SOURCES=$(patsubst %.o,../*/%.c,$(OBJECTS))

HEADERS=$(patsubst %.o,../*/%.h,$(OBJECTS))

LIBRARY=libDS.so

$(LIBRARY):$(OBJECTS)
	$(CC) $^ $(CFLAGS) $(SOFLAGS) -o $@



$(OBJECTS): $(SOURCES) $(HEADERS)
	$(CC) $(CFLAGS) $(OFLAGS) $(filter-out -I../list_%,$(patsubst %.o,-I../%,$(OBJECTS))) -o $@  $(patsubst %.o,../*/%.c ,$@)


.PHONEY:clean

clean:
	rm *.o







