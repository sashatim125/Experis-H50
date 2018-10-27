

OBJS=aggregator.o formatedPrint.o operStorageManager.o subscrStorageManager.o parser.o upserter.o queryMaker.o reportMaker.o
INCDIR=../inc/
SRCDIR=../src/

#############################
CFLAGS = -Wall -Wconversion -pedantic -ansi -Werror -I $(INCDIR) -c -g
LDFLAGS=
CC=gcc

.PHONEY:clean all

all:$(OBJS)

$(OBJS):$(addprefix $(SRCDIR),$(subst .o,.c,$@)) $(addprefix $(INCDIR),$(subst .o,.h,$@))
	$(CC) $(CFLAGS) $(addprefix $(SRCDIR),$(subst .o,.c,$@)) 

clean:
	rm -f $(OBJS) 

#############################



