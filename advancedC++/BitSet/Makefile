
TARGET=main.out

#############################
CXXFLAGS = -Wall -Wconversion -pedantic -ansi -Werror -g
LDFLAGS=
CC=gcc
CXX=g++

.PHONEY:clean run
	
$(TARGET): main.cpp bitSet.h
	$(CXX) $< $(CXXFLAGS) -o $@
	
clean:
	rm -f $(TARGET) 
	
run: $(TARGET)
	./$(TARGET)

#############################



