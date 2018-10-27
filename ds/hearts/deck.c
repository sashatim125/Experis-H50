
#include "deck.h"
#include "../vector/vector.h"
#include <stdlib.h> 
#include <time.h>/*time for srand*/
#include <stdio.h>


/** 
 *  @file deck.c
 *  @brief The Deck type and API implementations
 *	
 *  @details 
 *  
 *
 *  @author Alexander Timoshenko sashatim125@gmail.com
 * 
 */
 
#ifndef MAGIC_NUMBER
#define MAGIC_NUMBER 0xabcd
#endif /*MAGIC_NUMBER*/


static const char *suitNames[]  = {"\xE2\x99\xA5","\xE2\x99\xA0","\xE2\x99\xA6","\xE2\x99\xA3"};

static const char *ranksNames[] = {"2","3","4","5","6","7","8","9","10",\
	"J","Q","K","A"};


static Card theDeck[DECK_SIZE];
static int isDeckCreated = FALSE;


static void DeckCreateGlobal();

struct Deck
{
	int m_magicNum;
	
	Vector *m_deck;
};


Deck* DeckCreate()
{
	Deck *newDeck;
	int i;

	/*create the GLOBAL DECK*/
	if(!isDeckCreated)
	{
		DeckCreateGlobal();
		isDeckCreated = TRUE;
	}
	
	newDeck = (Deck*)malloc(sizeof(Deck));
	if(NULL==newDeck)
	{
		return NULL;
	}	

	newDeck->m_deck = VectorCreate(DECK_SIZE,0);
	
	if(NULL==newDeck->m_deck)
	{
		free(newDeck);
		return NULL;
	}
	
	newDeck->m_magicNum = MAGIC_NUMBER;
	
	for(i=0 ; i < DECK_SIZE ; ++i)
	{
		VectorAdd(newDeck->m_deck,i);
	}
	
	return newDeck;
}

void DeckDestroy(Deck* _deck)
{
	if((NULL==_deck)||(_deck->m_magicNum != MAGIC_NUMBER))
	{
		return;
	}

	VectorDestroy(_deck->m_deck);
	_deck->m_magicNum = 0;
	
	free(_deck);
}



ADTErr DeckShuffle(Deck *_deck)
{
	size_t numOfCards;
	CardIndex i, nextInx, nextCard, tempCard;

	if(NULL==_deck)
	{
		return ERR_NOT_INITIALIZED;
	}
	
	VectorItemsNum(_deck->m_deck,&numOfCards);
	
	if(numOfCards < DECK_SIZE)
	{
		return ERR_UNDERFLOW;
	}
	
	srand((unsigned)time(NULL));
	
	for(i=0 ; i < DECK_SIZE-1 ; ++i)
	{
		nextInx = rand()%(DECK_SIZE-i)+i;
		
		VectorGet(_deck->m_deck,(size_t)i,&tempCard);
		
		VectorGet(_deck->m_deck,(size_t)nextInx, &nextCard);
		
		VectorSet(_deck->m_deck,(size_t)i,nextCard);
		
		VectorSet(_deck->m_deck,(size_t)nextInx,tempCard);
	}
	
	return ERR_OK;
}



ADTErr DeckRemoveLast(Deck *_deck, CardIndex *_cardInx)
{

	if((NULL==_deck)||(NULL==_cardInx))
	{
		return ERR_NOT_INITIALIZED;
	}
	
	return (VectorDelete(_deck->m_deck,_cardInx));
}




ADTErr DeckSeeCard(CardIndex _index, Card *_card)
{
	if(NULL==_card)
	{
		return ERR_NOT_INITIALIZED;
	}

	if(_index < 0 || _index >= DECK_SIZE)
	{
		return ERR_WRONG_INDEX;
	}
	
	*_card = theDeck[_index];
	
	return ERR_OK;
}

void DeckPrint(Deck *_deck)
{
	CardIndex i;
	Card c;
	int j;
	
	VectorPrint(_deck->m_deck);
	
	for(i=0 ; i<DECK_SIZE ; ++i)
	{
		VectorGet(_deck->m_deck,(size_t)i,&j);
		DeckSeeCard(j,&c);
		printf("suit=%d rank=%d ",c.m_suit,c.m_rank);
	}
	printf("\n");
}

static void DeckCreateGlobal()
{
	int i;
	Suit s;
	Rank r;
		
	if(!isDeckCreated)
	{
		for(i=0 , s=HEARTS , r=R2 ; i < DECK_SIZE ; ++i,
			r=(r+1)%N_RANKS, (r==R2)?++s:0)
		{
			theDeck[i].m_suit = s;
			theDeck[i].m_rank = r;
		}
		isDeckCreated = TRUE;
	}
}




ADTErr PrintCard(CardIndex _cardInx)
{
	ADTErr res;
	Card nextCard;
	
	res = DeckSeeCard(_cardInx,&nextCard);
	if(ERR_OK != res)
	{
		return res;
	}
	
	printf("|%s %s|",suitNames[nextCard.m_suit],ranksNames[nextCard.m_rank]);
	
	return ERR_OK;
}


