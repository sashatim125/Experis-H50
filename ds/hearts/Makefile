
TARGET=hearts
OBJS=deck.o hand.o ai.o player.o trick.o round.o game.o ../shakeSort/shakeSort.o ../vector/vector.o

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
	./$(TARGET).out 

#############################

deck.h:card.h ../ADTErr.h
deck.o:deck.h ../vector/vector.h

hand.h:card.h ../vector/vector.h ../ADTErr.h
hand.o:hand.h deck.h ../shakeSort/shakeSort.h

ai.h:hand.h ../vector/vector.h ../ADTErr.h
ai.c:ai.h card.h deck.h

player.h:card.h ../vector/vector.h ../ADTErr.h
player.o:player.h hand.h

trick.h:player.h ../ADTErr.h
trick.o:trick.h deck.h card.h hand.h

round.h:player.h ../ADTErr.h
round.o:round.h card.h card.h deck.h trick.h

game.h:../ADTErr.h
game.o:game.h round.h player.h

hearts.c:game.h ../ADTErr.h


../shakeSort/shakeSort.o:../shakeSort/shakeSort.h
../vector/vector.o:../vector/vector.h


