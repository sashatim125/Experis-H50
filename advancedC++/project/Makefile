
TARGET=smartHouse.out
SRCDIR=src
SRC = $(wildcard $(SRCDIR)/*.cpp)
OBJDIR=obj
OBJ=$(subst $(SRCDIR),$(OBJDIR),$(SRC:.cpp=.o))
INCDIR=inc lib/inc
LIBDIR=lib
LIB=$(notdir $(wildcard $(LIBDIR)/*.so))
INIDIR=ini
DEP=$(OBJ:.o=.d)
CPPFLAGS = -std=c++03 -Wall -Wconversion -pedantic -ansi -Werror $(patsubst %,-I% ,$(INCDIR)) -g
LDFLAGS= $(addprefix -L,$(LIBDIR)) $(subst .so,,$(subst lib,-l,$(LIB))) -pthread -ldl -lmysqlcppconn

CC=g++

#############################
.PHONEY:clean run setlib

$(TARGET):$(OBJ)
	$(CC) -o $@ $^ $(CPPFLAGS) $(LDFLAGS) 

$(OBJ): 
	$(CC) -MMD $(patsubst $(OBJDIR)%,$(SRCDIR)%,$(subst .o,.cpp,$@)) -o $@ $(CPPFLAGS) -c 

clean:
	rm -f $(OBJ) $(DEP) $(TARGET)

run:$(TARGET) setlib
	$(TARGET) 

setlib:
	export LD_LIBRARY_PATH=${LD_LIBRARY_PATH}:./lib
	

#############################

-include $(DEP)



