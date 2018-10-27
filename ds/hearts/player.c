

#include "player.h"
#include "hand.h"
#include <stdlib.h> 

#include <stdio.h> 


/** 
 *  @file player.c
 *  @brief The player type and API implementations
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
 

struct Player
{
	int m_magicNum;
	
	const char *m_name;
	
	PlayerType m_pt;
	
	Hand *m_hand;
	
	unsigned m_points;
	
};


Player* PlayerCreate(PlayerType _pt, const char *_name)
{
	Player *newPlayer;
	
	if(NULL==_name)
	{
		return NULL;
	}
	
	newPlayer = (Player*)malloc(sizeof(Player));
	if((NULL==newPlayer)||(NULL==_name))
	{
		return NULL;
	}
	
	newPlayer->m_hand=NULL;
	newPlayer->m_pt = _pt;
	newPlayer->m_name = _name;
	newPlayer->m_points = 0;
	
	newPlayer->m_magicNum = MAGIC_NUMBER;
	
	return newPlayer;
}

void PlayerDestroy(Player* _player)
{
	
	if((NULL==_player)||(_player->m_magicNum != MAGIC_NUMBER))
	{
		return;
	}

	HandDestroy(_player->m_hand);
	_player->m_magicNum = 0;
	
	free(_player);
}


ADTErr PlayerNewHand(Player *_player)
{
	if(NULL==_player)
	{
		return ERR_NOT_INITIALIZED;
	}
	
	HandDestroy(_player->m_hand);
	
	_player->m_hand=HandCreate();
	
	if(NULL==_player->m_hand)
	{
		return ERR_ALLOCATION_FAILED;
	}
	
	return ERR_OK;
}


ADTErr PlayerTakeCard(Player *_player,CardIndex _index)
{

	if(NULL==_player)
	{
		return ERR_NOT_INITIALIZED;
	}
	
	return HandAdd(_player->m_hand,_index);
}


ADTErr PlayerRemoveForExchange(Player *_player, CardIndex* _cards)
{

	if((NULL==_player)||(NULL==_cards))
	{
		return ERR_NOT_INITIALIZED;
	}
	
	return (_player->m_pt == COMPUTER) ?  HandRemoveForExchange(_player->m_hand,_cards) : \
		HandRemoveForExchangeHuman(_player->m_hand,_cards) ;
}

ADTErr PlayerPlay(Player* _player, Vector *_table, CardIndex *_cardPlayed)
{
	
	if((NULL==_player)||(NULL==_table)||(NULL==_cardPlayed))
	{
		return ERR_NOT_INITIALIZED;
	}

	return (_player->m_pt == COMPUTER) ? HandPlay(_player->m_hand,_table,_cardPlayed) :\
		HandPlayHuman(_player->m_hand,_table,_cardPlayed);
}


ADTErr PlayerGetPoints(const Player *_player,unsigned *_points)
{
	if((NULL==_player)||(NULL==_points))
	{
		return ERR_NOT_INITIALIZED;
	}
	
	*_points = _player->m_points;
	
	return ERR_OK;
}


ADTErr PlayerAddPoints(Player *_player,unsigned _points)
{
	if(NULL==_player)
	{
		return ERR_NOT_INITIALIZED;
	}
	
	_player->m_points += _points;
	
	return ERR_OK;
}


ADTErr PlayerGetName(const Player *_player,char const **_namePtr)
{
	if((NULL==_player)||(NULL==_namePtr))
	{
		return ERR_NOT_INITIALIZED;
	}
	
	*_namePtr = _player->m_name;
	
	return ERR_OK;
}


/*test unit function*/
void PlayerPrint(Player* _player)
{
	char const *name;
	unsigned points;
	
	PlayerGetName(_player,&name);
	PlayerGetPoints(_player,&points);

	printf("I am %s, my type is %d, my points are %u and my hand is:\n",name,_player->m_pt,points);
	HandPrint(_player->m_hand);
}
















