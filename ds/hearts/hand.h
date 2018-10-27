
#ifndef __HAND_H__
#define __HAND_H__

#include "card.h"
#include "../vector/vector.h"
#include "../ADTErr.h"

#ifndef THREE
#define THREE 3
#endif /*THREE*/

/** 
 *  @file hand.h
 *  @brief The Hand type and API definitions
 *	
 *  @details 
 *  
 *
 *  @author Alexander Timoshenko sashatim125@gmail.com
 * 
 */


typedef struct Hand Hand;

/** 
 * @brief create the hand(empty)
 * @return new empty hand
 */
Hand* HandCreate();

/** 
 * @brief destroy the hand
 * @param[in] _hand - to be destroyed
 */
void HandDestroy(Hand *_hand);

/** 
 * @brief add card to hand
 * @param[in] _hand - the hand
 * @param[in] _index - of the card to add
 * @return status
 * @retval ERR_OK on success
 * @retval ERR_NOT_INITIALIZED 
 */
ADTErr HandAdd(Hand *_hand,CardIndex _index);

/** 
 * @brief remove three cards from the hand(by computer)
 * @param[in] _hand - the hand
 * @param[out] _threeCards array of three removed cards
 * @return status
 * @retval ERR_OK on success
 * @retval ERR_NOT_INITIALIZED 
 */
ADTErr HandRemoveForExchange(Hand *_hand, CardIndex *_threeCards);

/** 
 * @brief remove three cards from the hand(by human user)
 * @param[in] _hand - the hand
 * @param[out] _threeCards - array of three removed cards
 * @return status
 * @retval ERR_OK on success
 * @retval ERR_NOT_INITIALIZED 
 */
ADTErr HandRemoveForExchangeHuman(Hand *_hand, CardIndex *_threeCards);

/** 
 * @brief play the hand(by computer)
 * @param[in] _hand - the hand
 * @param[in] _table - the card in the table
 * @param[out] _cardPlayed - card to put on the table
 * @return status
 * @retval ERR_OK on success
 * @retval ERR_NOT_INITIALIZED 
 */
ADTErr HandPlay(Hand *_hand, Vector *_table, CardIndex *_cardPlayed);

/** 
 * @brief play the hand(by human user)
 * @param[in] _hand - the hand
 * @param[in] _table - the cards on the table
 * @param[out] _cardPlayed - card to put on the table
 * @return status
 * @retval ERR_OK on success
 * @retval ERR_NOT_INITIALIZED 
 */
ADTErr HandPlayHuman(Hand *_hand, Vector *_table, CardIndex *_cardPlayed);


/** 
 * @brief print the hand
 * @param[in] _hand - the hand
 * @return status
 * @retval ERR_OK on success
 * @retval ERR_NOT_INITIALIZED 
 */
ADTErr HandPrint(Hand *_hand);


#endif /*__HAND_H__*/



