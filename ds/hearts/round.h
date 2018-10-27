
#ifndef __ROUND_H__
#define __ROUND_H__

#include "player.h"
#include "../ADTErr.h"



/** 
 *  @file round.h
 *  @brief The Round type and API definitions
 *	
 *  @details 
 *  
 *
 *  @author Alexander Timoshenko sashatim125@gmail.com
 * 
 */

typedef enum Exchange
{
	LEFT,
	RIGHT,
	ACROSS,
	NONE,
	N_EXCHANGE
	
} Exchange;

typedef struct Round Round;

/** 
 * @brief create the round
 * @param[in] _players - array of pointers to players
 * @param[in] _exchangeMethod - in the beggining of the round
 * @return the new round 
 */
Round* RoundCreate(Player **_players, Exchange _exchangeMethod);

/** 
 * @brief destroys the round
 * @param[in] _round - to be destroyed
 */
void RoundDestroy(Round *_round);

/** 
 * @brief play the round.
 * @param[in] _round - to play
 * @return status
 * @retval ERR_OK on success
 * @retval ERR_NOT_INITIALIZED 
 */
ADTErr RoundPlay(Round *_round);



#endif /*__ROUND_H__*/



