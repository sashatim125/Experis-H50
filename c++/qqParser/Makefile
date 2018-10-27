
TARGET=qq--

OBJ=parser.o tokenizer.o analyzer.o

#############################
CPPFLAGS = -Wall -Wconversion -pedantic -ansi -Werror -g
LDFLAGS=
CC=g++

.PHONEY:clean

$(TARGET):$(OBJ)

clean:
	rm -f $(TARGET) $(OBJ)

#############################

parser.o:parser.h parser.cpp
tokenizer.o:tokenizer.h tokenizer.cpp
analyzer.o:analyzer.h analyzer.cpp

