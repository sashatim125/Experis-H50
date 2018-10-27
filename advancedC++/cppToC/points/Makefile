
TARGET1=a1.out
TARGET2=a2.out

#############################
CFLAGS = -Wall -Wconversion -pedantic -ansi -Werror -lm #-g
CXXFLAGS = #-Wall -Wconversion -pedantic -ansi -Werror -lm#-g
LDFLAGS=
CC=gcc

CXX=g++

.PHONEY:clean check all

all: $(TARGET1) $(TARGET2)



$(TARGET1):
	$(CC) points_jul_17.c $(CFLAGS) -o $@
	
$(TARGET2):
	$(CXX) points_jul_17.cpp $(CXXFLAGS) -o $@
	
clean:
	rm -f $(TARGET1) $(TARGET2) 
	
check:$(TARGET1) $(TARGET2)
	$(TARGET1) > $(basename $(TARGET1)).txt
	$(TARGET2) > $(basename $(TARGET2)).txt
	diff $(basename $(TARGET1)).txt $(basename $(TARGET2)).txt
	rm $(basename $(TARGET1)).txt
	rm $(basename $(TARGET2)).txt
	
	

#############################



