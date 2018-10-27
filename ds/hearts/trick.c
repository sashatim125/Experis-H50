

#include "trick.h"
#include "card.h"
#include "deck.h"
#include "hand.h"
#include <stdlib.h> 
#include <stdio.h> 

/** 
 *  @file trick.c
 *  @brief The Trick type and API implementations
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

#define PRINT_THE_TABLE \
{\
	printf("_______TABLE________\n");\
	PrintTable(_trick->m_table);\
}

#define PRINT_THE_MOVE(player,cardInx,name) \
{\
	PlayerGetName(player,&name);\
	printf("\n%s played with ",name);\
	PrintCard(cardInx);\
	printf("\n\n");\
}
	

struct Trick
{
	int m_magicNum;
	
	unsigned m_playerNum;
	
	Vector *m_table;
	
	Player **m_players;
};


static void CalcPoints(Trick *_trick,unsigned _playerNum, unsigned *_loser);

static unsigned GetPoints(CardIndex _cardInx);


/** 
 * @brief print the cards on the table
 * @param[in] _table - the cards on the table
 * @return status
 * @retval ERR_OK on success
 * @retval ERR_NOT_INITIALIZED 
 */
static ADTErr PrintTable(Vector *_table);


Trick* TrickCreate(Player *_players[], unsigned _playerNum)
{
	Trick *newTrick;
	
	if(NULL==_players)
	{
		return NULL;
	}
	
	newTrick = (Trick*)malloc(sizeof(Trick));
	if(NULL==newTrick)
	{
		return NULL;
	}
	
	newTrick->m_table = VectorCreate(NUM_OF_PLAYERS,0);
	if(NULL==newTrick->m_table)
	{
		free(newTrick);
		return NULL;
	}
	
	newTrick->m_playerNum = _playerNum;
	newTrick->m_players = _players;
	
	newTrick->m_magicNum = MAGIC_NUMBER;
	
	return newTrick;
}

void TrickDestroy(Trick* _trick)
{
	if((NULL==_trick)||(_trick->m_magicNum))
	{
		return;
	}
	
	VectorDestroy(_trick->m_table);
	
	_trick->m_magicNum = 0;
	free(_trick);
}

ADTErr TrickPlay(Trick *_trick, unsigned *_loser)
{
	CardIndex nextCardInx;
	unsigned nextMove, playerNum;
	const char *name;

	if(NULL==_trick)
	{
		return ERR_NOT_INITIALIZED;
	}
	
	
	for(nextMove=0, playerNum = _trick->m_playerNum ; nextMove < NUM_OF_PLAYERS ;
		++nextMove , playerNum = (playerNum+1)%NUM_OF_PLAYERS)
	{
		PRINT_THE_TABLE
		
		PlayerPlay(_trick->m_players[playerNum],_trick->m_table,&nextCardInx);
		
		VectorAdd(_trick->m_table,nextCardInx);

		PRINT_THE_MOVE(_trick->m_players[playerNum],nextCardInx,name)
	}
	
	PRINT_THE_TABLE
	
	CalcPoints(_trick,_trick->m_playerNum,_loser);

	return ERR_OK;	
}


static void CalcPoints(Trick *_trick,unsigned _playerNum, unsigned *_loser)
{
	CardIndex cardInx;
	unsigned totPoints, nextPlayerNum;
	size_t cardsCount;
	Suit leadingSuit;
	Rank maxRank;
	Card nextCard;
	const char *name;
	
	VectorGet(_trick->m_table,0,&cardInx);
	
	DeckSeeCard(cardInx,&nextCard);
	
	leadingSuit = nextCard.m_suit;
	maxRank=nextCard.m_rank;
	*_loser = _playerNum;
	totPoints=GetPoints(cardInx);
	
	nextPlayerNum=(_playerNum+1)%NUM_OF_PLAYERS;
		 
	for(cardsCount=1  ; cardsCount < NUM_OF_PLAYERS;
		 ++cardsCount, nextPlayerNum=(nextPlayerNum+1)%NUM_OF_PLAYERS)
	{
		VectorGet(_trick->m_table,cardsCount,&cardInx);
		totPoints+=GetPoints(cardInx);
		
		DeckSeeCard(cardInx,&nextCard);
		if((nextCard.m_suit == leadingSuit)&&(nextCard.m_rank > maxRank))
		{
			*_loser = nextPlayerNum;
			maxRank = nextCard.m_rank;
		}
	}
	
	PlayerAddPoints(_trick->m_players[*_loser],totPoints);
	
	PlayerGetName(_trick->m_players[*_loser],&name);
	printf("%s lost the trick with %u points.\n",name,totPoints);
}


static unsigned GetPoints(CardIndex _cardInx)
{
	Card theCard;
	
	unsigned points;
	
	DeckSeeCard(_cardInx,&theCard);
	
	if(theCard.m_suit == HEARTS)
	{
		points = 1;	
		
	}else if((theCard.m_suit == SPADES)&&(theCard.m_rank == QUEEN))
	{
		points = 13;
	}else
	{
		points = 0;
	}
	
	return points;
}


static ADTErr PrintTable(Vector *_table)
{
	size_t i,numOfCards;
	CardIndex nextCardInx;


	if(NULL==_table)
	{
		return ERR_NOT_INITIALIZED;
	}

	VectorItemsNum(_table,&numOfCards);
		
	for(i=0 ; i < numOfCards ; ++i)
	{
		VectorGet(_table,i,&nextCardInx);
		PrintCard(nextCardInx);
	}
	printf("\n\n");
	
	return ERR_OK;
}









