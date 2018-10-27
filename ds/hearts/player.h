
#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "card.h"
#include "../vector/vector.h"
#include "../ADTErr.h"


/** 
 *  @file player.h
 *  @brief The Hand type and API definitions
 *	
 *  @details 
 *  
 *
 *  @author Alexander Timoshenko sashatim125@gmail.com
 * 
 */
 
#ifndef THREE
#define THREE 3
#endif /*THREE*/

#ifndef NUM_OF_PLAYERS
#define NUM_OF_PLAYERS 4
#endif /*NUM_OF_PLAYERS*/

 
typedef enum PlayerType
{
	COMPUTER,
	HUMAN
	
} PlayerType;


typedef struct Player Player;

/** 
 * @brief create the player (human of computer).
 * @param[in] _pt - the player type (human or computer)
 * @param[in] _name - of the player
 * @return new player
 */
Player* PlayerCreate(PlayerType _pt, const char *_name);

/** 
 * @brief destroy the player 
 * @param[in] _player - to be destroyed
 */
void PlayerDestroy(Player* _player);

/** 
 * @brief renew (destroy and create again) the player's hand.
 * @param[in] _player 
 * @return status
 * @retval ERR_OK on success
 * @retval ERR_NOT_INITIALIZED 
 */
ADTErr PlayerNewHand(Player *_player);

/** 
 * @brief give card to the player
 * @param[in] _player 
 * @param[in] _index - of the card to take
 * @return status
 * @retval ERR_OK on success
 * @retval ERR_NOT_INITIALIZED 
 */
ADTErr PlayerTakeCard(Player *_player,CardIndex _index);

/** 
 * @brief remove three cards from the player (computer or human)
 * @param[in] _player 
 * @param[out] _cards - array of three removed cards
 * @return status
 * @retval ERR_OK on success
 * @retval ERR_NOT_INITIALIZED 
 */
ADTErr PlayerRemoveForExchange(Player *_player, CardIndex* _cards);

/** 
 * @brief play the card
 * @param[in] _player 
 * @param[in] _table - the card in the table
 * @param[out] _cardPlayed - card to put on the table
 * @return status
 * @retval ERR_OK on success
 * @retval ERR_NOT_INITIALIZED 
 */
ADTErr PlayerPlay(Player* _player, Vector *_table, CardIndex *_cardPlayed);

/** 
 * @brief get the player's current score
 * @param[in] _player 
 * @param[out] _points - the score
 * @return status
 * @retval ERR_OK on success
 * @retval ERR_NOT_INITIALIZED 
 */
ADTErr PlayerGetPoints(const Player *_player,unsigned *_points);

/** 
 * @brief add to the player score more points
 * @param[in] _player 
 * @param[in] _points - to add
 * @return status
 * @retval ERR_OK on success
 * @retval ERR_NOT_INITIALIZED 
 */
ADTErr PlayerAddPoints(Player *_player,unsigned _points);


/** 
 * @brief get the player's name
 * @param[in] _player 
 * @param[out] _namePtr - to return the name
 * @return status
 * @retval ERR_OK on success
 * @retval ERR_NOT_INITIALIZED 
 */
ADTErr PlayerGetName(const Player *_player,char const **_namePtr);


/*test unit function*/
void PlayerPrint(Player*);


#endif /*__PLAYER_H__*/






