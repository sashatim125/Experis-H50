

OBJS=aggregator.o formatedPrint.o operStorageManager.o subscrStorageManager.o parser.o upserter.o queryMaker.o reportMaker.o
INCDIR=./inc/
OBJDIR=./obj/
SRCDIR=./src/

#############################
CFLAGS = -Wall -Wconversion -pedantic -ansi -Werror -I $(INCDIR) -g
LDFLAGS= -pthread -lDS -L lib/
CC=gcc

.PHONEY:all clean

all:parserMain dataManagerMain


parserMain: $(SRCDIR)parserMain.c $(OBJDIR)parser.o 
	$(CC) $< $(CFLAGS) -o $@ $(OBJDIR)parser.o 

dataManagerMain:$(SRCDIR)dataManagerMain.c $(addprefix $(OBJDIR),$(OBJS))
	$(CC)  $< $(CFLAGS) -o $@ $(addprefix $(OBJDIR),$(OBJS)) $(LDFLAGS)

clean:
	rm -f parserMain dataManagerMain

#############################


