
#include "ai.h"
#include "card.h"
#include "deck.h"



/** 
 *  @file ai.c
 *  @brief The logic API implementations
 *	
 *  @details 
 *  
 *
 *  @author Alexander Timoshenko sashatim125@gmail.com
 * 
 */


static int IsOnMyHand(Vector * const *_cards, CardIndex _cardInx);




ADTErr FindCardToPlay(Vector * const *_cards, Vector *_table, CardIndex *_cardPlayed, int _areHeartsBroken, int *_willHeartsBeBroken)
{	
	CardIndex cardInx;
	size_t cardsNumOnTable, cardsNums[N_SUITS];
	Suit leadingSuit, i;
	Card firstCard;

	
	if((NULL==_cards)||(NULL==_cardPlayed)||(NULL==_table))
	{
		return ERR_NOT_INITIALIZED;
	}
	
	*_willHeartsBeBroken = _areHeartsBroken;
	
	for (i=0 ; i < N_SUITS ; ++i)
	{
		VectorItemsNum(_cards[i], cardsNums+i);
	}
	
	VectorItemsNum(_table,&cardsNumOnTable);	
	if(cardsNumOnTable > 0)
	{
		VectorGet(_table,0,&cardInx);	
		DeckSeeCard(cardInx,&firstCard);
		
		leadingSuit = firstCard.m_suit;
	}
	

	if(cardsNumOnTable == 0)
	{
		for (i=N_SUITS-1 ; i >=0 ; --i)
		{
			if(cardsNums[i] > 0)
			{
				VectorGet(_cards[i],0,&cardInx);
				if((!_areHeartsBroken)&&(i == HEARTS))
				{
					continue;
				}
				*_cardPlayed = cardInx;
				return ERR_OK;
			}
		}
		if(i < 0)
		{
			if(!_areHeartsBroken)
			{
				*_willHeartsBeBroken = TRUE;
			}
			*_cardPlayed = cardInx;
			return ERR_OK;
		}
	}
	
	if(cardsNums[leadingSuit] > 0)
	{
		VectorGet(_cards[leadingSuit],0,&cardInx);
		*_cardPlayed = cardInx;
		return ERR_OK;
	}
		
	if(cardsNums[HEARTS] > 0)
	{
		if(!_areHeartsBroken)
		{
			*_willHeartsBeBroken = TRUE;
		}
		VectorGet(_cards[HEARTS],0,&cardInx);
		*_cardPlayed = cardInx;
		return ERR_OK;
	}
	
	if (IsOnMyHand(_cards,SPADES*N_RANKS+QUEEN))
	{
		*_cardPlayed = SPADES*N_RANKS+QUEEN;
		return ERR_OK;
	}
	
	for (i=0 ; i < N_SUITS ; ++i)
	{
		if(cardsNums[i] > 0)
		{
			VectorGet(_cards[i],0,&cardInx);
			*_cardPlayed = cardInx;
			return ERR_OK;
		}
	}

	return ERR_OK;
}


ADTErr FindCardsToRemoveForExchange(Vector * const *_cards, CardIndex *_threeCards)
{
	int cardsCount;
	Rank highRank;
	Suit nextSuit;
		
	if((NULL==_cards)||(NULL==_threeCards))
	{
		return ERR_NOT_INITIALIZED;
	}
	
	cardsCount = 0;
	
	if(ERR_OK == IsOnMyHand(_cards,SPADES*N_RANKS+ACE))
	{
		_threeCards[cardsCount++]=SPADES*N_RANKS+ACE;
	}
	if(ERR_OK == IsOnMyHand(_cards,SPADES*N_RANKS+KING))
	{
		_threeCards[cardsCount++]=SPADES*N_RANKS+KING;
	}
	if(ERR_OK == IsOnMyHand(_cards,SPADES*N_RANKS+QUEEN))
	{
		_threeCards[cardsCount++]=SPADES*N_RANKS+QUEEN;
	}
	
	for (highRank = ACE ; highRank >= R2 && cardsCount < THREE ; --highRank)
	{
		for(nextSuit = 0 ; nextSuit < N_SUITS && cardsCount < THREE ; ++nextSuit)
		{
			if(ERR_OK == IsOnMyHand(_cards,(int)(nextSuit*N_RANKS+highRank)))
			{
				_threeCards[cardsCount++]=(int)(nextSuit*N_RANKS+highRank);
				continue;
			}
		}
	}

	return ERR_OK;
}




static int IsOnMyHand(Vector * const *_cards, CardIndex _cardInx)
{
	Card theCard ;
	size_t i , numOfCards;
	CardIndex nextCardInx;
	ADTErr res;
	
	
	if(NULL==_cards)
	{
		return FALSE;
	}

	res = DeckSeeCard(_cardInx,&theCard);
	if(ERR_OK != res)
	{
		return FALSE;
	}
	
	VectorItemsNum(_cards[theCard.m_suit],&numOfCards);
	
	for(i=0 ; i < numOfCards ; ++i)
	{
		VectorGet(_cards[theCard.m_suit],i,&nextCardInx);	
		
		if(nextCardInx == _cardInx)
		{
			return TRUE;
		}
	}

	return FALSE;
}

