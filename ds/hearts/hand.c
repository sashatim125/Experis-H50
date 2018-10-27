
#include "hand.h"
#include "ai.h"
#include "deck.h"
#include "../shakeSort/shakeSort.h"
#include <stdlib.h> 
#include <stdio.h>

/** 
 *  @file hand.c
 *  @brief The Hand type and API implementations
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

struct Hand
{
	int m_magicNum;
	
	Vector *m_cards[N_SUITS];
};

static int areHeartsBroken;

static void SortHand(Hand *_hand);

static ADTErr RemoveFromHand(Hand *_hand, CardIndex _cardInx);

static CardIndex CardChoise(Hand *_hand);


Hand* HandCreate()
{
	Hand *newHand;
	int i , res;
	
	newHand = (Hand*)malloc(sizeof(Hand));
	if(NULL==newHand)
	{
		return NULL;
	}
	for(i=0 ; i < N_SUITS ; ++i)
	{
		newHand->m_cards[i] = VectorCreate(N_RANKS,0);
	}
	
	for(i=0 , res = FALSE ; i < N_SUITS && !res ; ++i)
	{
		res = res||(NULL==newHand->m_cards[i]);
	}
	
	if(res)
	{
		for(i=0 ; i < N_SUITS ; ++i)
		{
			VectorDestroy(newHand->m_cards[i]);
		}
		
		free(newHand);
		return NULL;
	}
	areHeartsBroken = FALSE;
	
	newHand->m_magicNum = MAGIC_NUMBER;
	
	return newHand;
}


void HandDestroy(Hand *_hand)
{
	int i;
	
	if((NULL==_hand)||(_hand->m_magicNum != MAGIC_NUMBER))
	{
		return;
	}

	for(i=0 ; i < N_SUITS ; ++i)
	{
		VectorDestroy(_hand->m_cards[i]);
	}
	
	_hand->m_magicNum = 0;
	
	free(_hand);
}


ADTErr HandAdd(Hand *_hand,CardIndex _index)
{
	Card c;
	ADTErr res;

	if(NULL==_hand)
	{
		return ERR_NOT_INITIALIZED;
	}
	
	res =  DeckSeeCard(_index, &c);
	if(ERR_OK != res)
	{
		return res;
	}
	
	res=VectorAdd(_hand->m_cards[c.m_suit],_index);
	if(ERR_OK != res)
	{
		return res;
	}
	SortHand(_hand);
	return ERR_OK;
}


ADTErr HandRemoveForExchange(Hand *_hand, CardIndex *_threeCards)
{
	ADTErr res;
	int i;

	if((NULL==_hand)||(NULL==_threeCards))
	{
		return ERR_NOT_INITIALIZED;
	}

	res = FindCardsToRemoveForExchange(_hand->m_cards,_threeCards);
	if(ERR_OK != res)
	{
		return res;
	}
	
	for(i=0 ; i < THREE ; ++i)
	{
		RemoveFromHand(_hand,_threeCards[i]);
	}
	
	return ERR_OK;
}



/*{
	int cardsCount;
	Rank highRank;
	Suit nextSuit;
		
	if((NULL==_hand)||(NULL==_threeCards))
	{
		return ERR_NOT_INITIALIZED;
	}
	
	cardsCount = 0;
	
	if(ERR_OK == RemoveFromHand(_hand,SPADES*N_RANKS+ACE))
	{
		_threeCards[cardsCount++]=SPADES*N_RANKS+ACE;
	}
	if(ERR_OK == RemoveFromHand(_hand,SPADES*N_RANKS+KING))
	{
		_threeCards[cardsCount++]=SPADES*N_RANKS+KING;
	}
	if(ERR_OK == RemoveFromHand(_hand,SPADES*N_RANKS+QUEEN))
	{
		_threeCards[cardsCount++]=SPADES*N_RANKS+QUEEN;
	}
	
	for (highRank = ACE ; highRank >= R2 && cardsCount < THREE ; --highRank)
	{
		for(nextSuit = 0 ; nextSuit < N_SUITS && cardsCount < THREE ; ++nextSuit)
		{
			if(ERR_OK == RemoveFromHand(_hand,(int)(nextSuit*N_RANKS+highRank)))
			{
				_threeCards[cardsCount++]=(int)(nextSuit*N_RANKS+highRank);
				continue;
			}
		}
	}

	return ERR_OK;
}*/

/*TEST
{
	int i,max;
	size_t s[4] ;	
	
	if((NULL==_hand)||(NULL==_threeCards))
	{
		return ERR_NOT_INITIALIZED;
	}
	
	for (i=0 ; i < N_SUITS ; ++i)
	{
		VectorItemsNum(_hand->m_cards[i], s+i);
	}
	
	max=0;
	if(s[1]>s[max]) max=1;
	if(s[2]>s[max]) max=2;
	if(s[3]>s[max]) max=3;
	
	for (i=0 ; i < THREE ; ++i)
	{
		VectorDelete(_hand->m_cards[max],_threeCards+i);
	}
	
	SortHand(_hand);
	
	return ERR_OK;	
}*/

ADTErr HandRemoveForExchangeHuman(Hand *_hand, CardIndex *_threeCards)
{
	int i;
	
	if((NULL==_hand)||(NULL==_threeCards))
	{
		return ERR_NOT_INITIALIZED;
	}
	
	printf("Please choose any %d cards to transfer from your hand.\n\n",THREE);
	HandPrint(_hand);
	printf("\n");
	
	for (i=0 ; i < THREE ; ++i)
	{
		_threeCards[i] = CardChoise(_hand);

	}
	
	return ERR_OK;	
}


ADTErr HandPlay(Hand *_hand, Vector *_table, CardIndex *_cardPlayed)
{
	ADTErr res;

	if((NULL==_hand)||(NULL==_cardPlayed)||(NULL==_table))
	{
		return ERR_NOT_INITIALIZED;
	}

	res = FindCardToPlay(_hand->m_cards,_table,_cardPlayed,areHeartsBroken,&areHeartsBroken);
	if(ERR_OK != res)
	{
		return res;
	}

	return RemoveFromHand(_hand,*_cardPlayed);
}
/*{	
	CardIndex cardInx;
	size_t cardsNumOnTable, cardsNums[N_SUITS];
	Suit leadingSuit, i;
	Card firstCard;
	
	if((NULL==_hand)||(NULL==_cardPlayed)||(NULL==_table))
	{
		return ERR_NOT_INITIALIZED;
	}
	
	for (i=0 ; i < N_SUITS ; ++i)
	{
		VectorItemsNum(_hand->m_cards[i], cardsNums+i);
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
				VectorGet(_hand->m_cards[i],0,&cardInx);
				if((!areHeartBroken)&&(i == HEARTS))
				{
					continue;
				}
				RemoveFromHand(_hand,cardInx);
				*_cardPlayed = cardInx;
				return ERR_OK;
			}
		}
		if(i < 0)
		{
			if(!areHeartBroken)
			{
				areHeartBroken = TRUE;
				printf("\n\n!!!!!!!!!! The HEARTS are broken !!!!!!!!!!\n\n");
			}
			RemoveFromHand(_hand,cardInx);
			*_cardPlayed = cardInx;
			return ERR_OK;
		}
	}
	
	if(cardsNums[leadingSuit] > 0)
	{
		VectorGet(_hand->m_cards[leadingSuit],0,&cardInx);
		RemoveFromHand(_hand,cardInx);
		*_cardPlayed = cardInx;
		return ERR_OK;
	}
		
	if(cardsNums[HEARTS] > 0)
	{
		if(!areHeartBroken)
		{
			areHeartBroken = TRUE;
			printf("\n\n!!!!!!!!!! The HEARTS are broken !!!!!!!!!!\n\n");
		}
		VectorGet(_hand->m_cards[HEARTS],0,&cardInx);
		RemoveFromHand(_hand,cardInx);
		*_cardPlayed = cardInx;
		return ERR_OK;
	}
	
	if (ERR_OK == RemoveFromHand(_hand,SPADES*N_RANKS+QUEEN))
	{
		*_cardPlayed = SPADES*N_RANKS+QUEEN;
		return ERR_OK;
	}
	
	for (i=0 ; i < N_SUITS ; ++i)
	{
		if(cardsNums[i] > 0)
		{
			VectorGet(_hand->m_cards[i],0,&cardInx);
			RemoveFromHand(_hand,cardInx);
			*_cardPlayed = cardInx;
			return ERR_OK;
		}
	}

	return ERR_OK;
}*/



ADTErr HandPlayHuman(Hand *_hand, Vector *_table, CardIndex *_cardPlayed)
{	
	CardIndex cardInx;
	size_t cardsNumOnTable, leadSuitCardsNum, heartsNum;
	Suit leadingSuit;
	Card firstCard, myCard;
	
	if((NULL==_hand)||(NULL==_cardPlayed)||(NULL==_table))
	{
		return ERR_NOT_INITIALIZED;
	}
	
	VectorItemsNum(_hand->m_cards[HEARTS],&heartsNum);
	
	VectorItemsNum(_table,&cardsNumOnTable);	
	if(cardsNumOnTable > 0)
	{
		VectorGet(_table,0,&cardInx);	
		DeckSeeCard(cardInx,&firstCard);
		
		leadingSuit = firstCard.m_suit;
		VectorItemsNum(_hand->m_cards[leadingSuit],&leadSuitCardsNum);
	}
	
	while (1)
	{
		printf("Please make your move (choose a card from your hand).\n\n");
		HandPrint(_hand);
		printf("\n");

		*_cardPlayed = CardChoise(_hand);
		
		DeckSeeCard(*_cardPlayed,&myCard);

		if(cardsNumOnTable == 0)
		{
			if((!areHeartsBroken)&&(myCard.m_suit == HEARTS))
			{
				HandAdd(_hand,*_cardPlayed);
				printf("\nThe HEARTS are not broken yet!\n\n");
				continue;
			}
			
			break;
		}
		if(myCard.m_suit == leadingSuit)
		{
			break;
		}
		
		if(leadSuitCardsNum > 0)
		{
			HandAdd(_hand,*_cardPlayed);
			printf("\nYou have to move with the leading suit.\n\n");
			continue;
		}
		
		if(myCard.m_suit == HEARTS)
		{
			if(!areHeartsBroken)
			{
				areHeartsBroken = TRUE;
				printf("\n\n!!!!!!!!!! The HEARTS are broken !!!!!!!!!!\n\n");
			}
			break;		
		}
		
		if(heartsNum > 0)
		{
			HandAdd(_hand,*_cardPlayed);
			printf("\nYou have to move with the HEARTS.\n\n");
			continue;
		}
		
		break;
	}

	return ERR_OK;	
}



static void SortHand(Hand *_hand)
{
	int i;
	
	for(i=0 ; i < N_SUITS ; ++i)
	{
		ShakeSort(_hand->m_cards[i]);
	}	
}


ADTErr HandPrint(Hand *_hand)
{
	int i;
	size_t j,numOfCards;
	CardIndex nextCardInx;
	
	if(NULL==_hand)
	{
		return ERR_NOT_INITIALIZED;
	}

	for(i=0 ; i < N_SUITS ; ++i)
	{		
		VectorItemsNum(_hand->m_cards[i],&numOfCards);

		for(j=0 ; j < numOfCards ; ++j)
		{			
			VectorGet(_hand->m_cards[i],j,&nextCardInx);
			PrintCard(nextCardInx);
		}
		printf(" ");
	}
	printf("\n\n");
	
	return ERR_OK;	
}




static ADTErr RemoveFromHand(Hand *_hand, CardIndex _cardInx)
{
	Card theCard ;
	size_t i , numOfCards;
	CardIndex nextCardInx, temp;
	ADTErr res;
	
	
	if(NULL==_hand)
	{
		return ERR_NOT_INITIALIZED;
	}

	res = DeckSeeCard(_cardInx,&theCard);
	if(ERR_OK != res)
	{
		return res;
	}
	
	VectorItemsNum(_hand->m_cards[theCard.m_suit],&numOfCards);
	
	for(i=0 ; i < numOfCards ; ++i)
	{
		VectorGet(_hand->m_cards[theCard.m_suit],i,&nextCardInx);	
		
		if(nextCardInx == _cardInx)
		{
			VectorGet(_hand->m_cards[theCard.m_suit],numOfCards-1,&temp);
			VectorSet(_hand->m_cards[theCard.m_suit],i,temp);
			VectorDelete(_hand->m_cards[theCard.m_suit],&temp);
			
			SortHand(_hand);
			
			return ERR_OK;
		}
	}

	return ERR_NOT_FOUND;

}



static CardIndex CardChoise(Hand *_hand)
{
	int corrEnter ;
	Suit nextSuit;
	Rank nextRank;
	CardIndex cardInx;
	char suit[10];
	size_t numOfCards;
	ADTErr res;


	corrEnter = FALSE;
	
	while(!corrEnter)
	{
		printf("Enter the first letter of the suit :");
		scanf("%s",suit);
		
		corrEnter = TRUE;
		
		switch (suit[0])
		{
			case 'H':
			case 'h':
				nextSuit = HEARTS;
				break;
			case 'S':
			case 's':
				nextSuit = SPADES;
				break;
			case 'D':
			case 'd':
				nextSuit = DIAMONDS;
				break;
			case 'C':
			case 'c':
				nextSuit = CLUBS;
				break;			
				
			default:
				nextSuit = HEARTS;
				corrEnter = FALSE;
				break;
		}
		
		VectorItemsNum(_hand->m_cards[nextSuit],&numOfCards);
		
		if((!corrEnter)||(0 == numOfCards))
		{
			printf("Wrong suit - try again.\n\n");
			corrEnter = FALSE;
			continue;
		}
		
		printf("Enter the number of the rank (JAKE=11, QUEEN=12, KING=13, ACE=14) :");
		scanf("%d",(int*)&nextRank);
		
		nextRank-=2;
		corrEnter = TRUE;
		
		if((nextRank >= R2)&&(nextRank<=ACE))
		{
			cardInx = (int)(N_RANKS * nextSuit + nextRank);
			
			res = RemoveFromHand(_hand,cardInx);
			if(res != ERR_OK)
			{
				printf("No such card in your hand!\nTry again.\n\n");
				corrEnter = FALSE;
				continue;
			}			
		}else
		{
			printf("Wrong rank - try again.\n\n");
			corrEnter = FALSE;
			continue;
		}
	}
	
	return cardInx;
}














