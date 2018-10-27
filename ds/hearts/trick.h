
#ifndef __TRICK_H__
#define __TRICK_H__

#include "player.h"
#include "../ADTErr.h"

/** 
 *  @file trick.h
 *  @brief The Trick type and API definitions
 *	
 *  @details 
 *  
 *
 *  @author Alexander Timoshenko sashatim125@gmail.com
 * 
 */


typedef struct Trick Trick;

/** 
 * @brief create the trick
 * @param[in] _players - array of pointers to players
 * @param[in] _playerNum - starting player
 * @return the new trick 
 */
Trick* TrickCreate(Player *_players[], unsigned _playerNum);

/** 
 * @brief destroys the trick
 * @param[in] _trick - to be destroyed
 */
void TrickDestroy(Trick* _trick);

/** 
 * @brief play the trick.
 * @param[in] _trick - to play
 * @param[out] _loser - number of player lost on the trick
 * @return status
 * @retval ERR_OK on success
 * @retval ERR_NOT_INITIALIZED 
 */
ADTErr TrickPlay(Trick *_trick, unsigned *_loser);



#endif /*__TRICK_H__*/



