
TARGET=sortTest
OBJS=sort.o ../stack/stack.o ../vector/vector.o

#############################
CFLAGS = -Wall -Wconversion -pedantic -ansi -Werror -g
LDFLAGS=
CC=gcc

.PHONEY:clean run

$(TARGET):$(OBJS)

clean:
	rm -f $(TARGET) $(OBJS) $(TARGET).out
	
run:$(TARGET)
	mv $(TARGET) $(TARGET).out
	./$(TARGET).out sortResults.txt

#############################
sort.o:sort.h
sort.o:../stack/stack.h
../stack/stack.o:../stack/stack.h
../stack/stack.h:../vector/vector.h
../vector/vector.o:../vector/vector.h


