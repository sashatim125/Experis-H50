

#include "round.h"
#include "card.h"
#include "deck.h"
#include "trick.h"
#include "../ADTErr.h"
#include <stdlib.h> 

#include <stdio.h> 



/** 
 *  @file round.c
 *  @brief The Round type and API implementations
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

#ifndef NUMBER_OF_TRICKS
#define NUMBER_OF_TRICKS (DECK_SIZE/NUM_OF_PLAYERS)
#endif /*NUMBER_OF_TRICKS*/


struct Round 
{
	int m_magicNum;
	
	Exchange m_exchangeMethod;
	
	unsigned m_beginPlayer;
	
	Player **m_players;
	
};

static ADTErr MakeExchange(Player **_players, Exchange _exchangeMethod);

static ADTErr DealCards(Round*, Deck*);


Round* RoundCreate(Player **_players, Exchange _exchangeMethod)
{
	Round *newRound;
	
	if(NULL==_players)
	{
		return NULL;
	}
	
	newRound = (Round*)malloc(sizeof(Round));
	if(NULL==newRound)
	{
		return NULL;
	}
	
	newRound->m_magicNum = MAGIC_NUMBER;
	
	newRound->m_exchangeMethod = _exchangeMethod;
	newRound->m_beginPlayer = 0;
	newRound->m_players = _players;
	
	return newRound;
}

void RoundDestroy(Round *_round)
{
	if((NULL==_round)||(MAGIC_NUMBER != _round->m_magicNum))
	{
		return;
	}
	
	_round->m_magicNum = 0;
	free(_round);
}



ADTErr RoundPlay(Round *_round)
{
	Deck *newDeck;
	Trick* nextTrick;
	unsigned trickCount, playerCount;
	ADTErr res;
	
	/*TEST
	int i;*/

	if(NULL==_round)
	{
		return ERR_NOT_INITIALIZED;
	}
	
	newDeck = DeckCreate();
	if(NULL==newDeck)
	{
		return ERR_NOT_INITIALIZED;
	}
	
	res=DeckShuffle(newDeck);
	if (ERR_OK != res)
	{
		return res;
	}
	
	for(playerCount=0 ; playerCount < NUM_OF_PLAYERS ; ++playerCount)
	{
		res=PlayerNewHand(_round->m_players[playerCount]);
		if (ERR_OK != res)
		{
			return res;
		}
	}

	res = DealCards(_round,newDeck);
	if (ERR_OK != res)
	{
		return res;
	}
	
	if(_round->m_exchangeMethod != NONE)
	{
		printf("At the beginig of this round each player has to tranfer %d card to the player ",THREE);
		
		switch(_round->m_exchangeMethod)
		{
			case LEFT:
				printf("on his left.\n\n");
				break;
			case RIGHT:
				printf("on his right.\n\n");
				break;
			case ACROSS:
				printf("across him.\n\n");
				break;
			default:
				break;
		}
	}
	
	res = MakeExchange(_round->m_players,_round->m_exchangeMethod);
	if (ERR_OK != res)
	{
		return res;
	}
	
	/*TEST
	fprintf(stdout,"After make_exchage :\n");
	for(i=0 ; i<4 ; ++i)
	{
		PlayerPrint(_round->m_players[i]);
	}
	fprintf(stdout,"After make exchage ^^^^^^^^^^^^^^:\n");
	*/
	
	for(trickCount=0 ; trickCount < NUMBER_OF_TRICKS ; ++trickCount)
	{
	
		nextTrick = TrickCreate(_round->m_players,_round->m_beginPlayer);
		if(NULL==nextTrick)
		{
			DeckDestroy(newDeck);
			return ERR_ALLOCATION_FAILED;
		}
	
		res = TrickPlay(nextTrick,&_round->m_beginPlayer);
		if (ERR_OK != res)
		{
			return res;
		}
		
		/*TEST
		for(i=0 ; i<4 ; ++i)
		{
			PlayerPrint(_round->m_players[i]);
		}
		printf("After trick #%d ^^^^^^^^^^^^^^^^^^^^^^^\n",trickCount+1);
		getchar();
		*/
		
		TrickDestroy(nextTrick);
	}
	
	DeckDestroy(newDeck);

	return ERR_OK;	
}

static ADTErr DealCards(Round *_round, Deck *_deck)
{
	unsigned count,playerNum;
	ADTErr res;
	CardIndex cardInx;
	Card nextCard;
	
	for(count=0, playerNum=0 ; count < DECK_SIZE ; ++count ,
		 playerNum = (playerNum+1)%NUM_OF_PLAYERS)
	{
		res=DeckRemoveLast(_deck,&cardInx);
		if (ERR_OK != res)
		{
			return res;
		}
		
		DeckSeeCard(cardInx,&nextCard);
		
		if((nextCard.m_suit == CLUBS)&&(nextCard.m_rank == R2))
		{
			_round->m_beginPlayer=playerNum;
		}
		
		res=PlayerTakeCard(_round->m_players[playerNum],cardInx);
		if (ERR_OK != res)
		{
			return res;
		}
	}
		
	return ERR_OK;
}


static ADTErr MakeExchange(Player **_players, Exchange _exchangeMethod)
{
	CardIndex cardInxs[NUM_OF_PLAYERS][THREE];
	unsigned playerNum ,cardNum , cardExchanges[NUM_OF_PLAYERS];
	ADTErr res;


	if(NULL==_players)
	{
		return ERR_NOT_INITIALIZED;
	}
	
	for(playerNum=0; playerNum < NUM_OF_PLAYERS ; ++playerNum)
	{
		res=PlayerRemoveForExchange(_players[playerNum], cardInxs[playerNum]);
		if (ERR_OK != res)
		{
			return res;
		}
	}
	
	switch (_exchangeMethod)
	{
		case LEFT:
			for(playerNum=0; playerNum < NUM_OF_PLAYERS ; ++playerNum)
			{
				cardExchanges[playerNum]=(playerNum+1)%NUM_OF_PLAYERS;
			}
			break;
		
		case RIGHT:
			for(playerNum=0; playerNum < NUM_OF_PLAYERS ; ++playerNum)
			{
				cardExchanges[(playerNum+1)%NUM_OF_PLAYERS]=playerNum;
			}
			break;
		
		case ACROSS:
			for(playerNum=0; playerNum < NUM_OF_PLAYERS ; ++playerNum)
			{
				cardExchanges[(playerNum+2)%NUM_OF_PLAYERS]=playerNum;
			}
			break;
		
		case NONE:
			for(playerNum=0; playerNum < NUM_OF_PLAYERS ; ++playerNum)
				{
					cardExchanges[playerNum]=playerNum;
				}
			break;
		default:
			break;		
	}
	
	for(playerNum=0; playerNum < NUM_OF_PLAYERS ; ++playerNum)
	{
		for(cardNum=0; cardNum < THREE ; ++cardNum)
		{
			res=PlayerTakeCard(_players[playerNum],cardInxs[cardExchanges[playerNum]][cardNum]);
			if (ERR_OK != res)
			{
				return res;
			}
		}
	}
	
	return ERR_OK;
}






