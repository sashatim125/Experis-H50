
#ifndef __AI_H__
#define __AI_H__

#include "hand.h"
#include "../vector/vector.h"
#include "../ADTErr.h"

/** 
 *  @file ai.h
 *  @brief The logic API definitions
 *	
 *  @details 
 *  
 *
 *  @author Alexander Timoshenko sashatim125@gmail.com
 * 
 */

/** 
 * @brief play the hand(by computer)
 * @param[in] _cards - the hand
 * @param[in] _table - the card in the table
 * @param[in] _areHeartsBroken - the situation of the game
 * @param[in] _willHeartBeBroken - if the result will break the hearts
 * @param[out] _cardPlayed - card to put on the table
 * @return status
 * @retval ERR_OK on success
 * @retval ERR_NOT_INITIALIZED 
 */
ADTErr FindCardToPlay(Vector * const *_cards, Vector *_table, CardIndex *_cardPlayed, int _areHeartsBroken, int *_willHeartBeBroken);

/** 
 * @brief remove 3 cards for exchange(by computer)
 * @param[in] _cards - the hand
 * @param[out] _threeCards - the cards to be moved
 * @return status
 * @retval ERR_OK on success
 * @retval ERR_NOT_INITIALIZED 
 */
ADTErr FindCardsToRemoveForExchange(Vector * const *_cards, CardIndex *_threeCards);

#endif /*__AI_H__*/
