
#ifndef __DECK_H__
#define __DECK_H__

#include "card.h"
#include "../ADTErr.h"


/** 
 *  @file deck.h
 *  @brief The Deck type and API definitions
 *	
 *  @details 
 *  
 *
 *  @author Alexander Timoshenko sashatim125@gmail.com
 * 
 */

#ifndef DECK_SIZE
#define DECK_SIZE 52
#endif /*DECK_SIZE*/


typedef struct Deck Deck;

/** 
 * @brief Creates the deck
 * @return new deck
 */
Deck* DeckCreate();

/** 
 * @brief Destroys the deck
 * @param[in] _deck - deck to be destroyed 
 */
void DeckDestroy(Deck* _deck);

/** 
 * @brief Shuffles the deck
 * @param[in] _deck - unshuffled deck 
 * @return status
 * @retval ERR_OK on success
 * @retval ERR_NOT_INITIALIZED 
 */
ADTErr DeckShuffle(Deck *_deck);

/** 
 * @brief take last card from the deck
 * @param[in] _deck - unshuffled deck 
 * @param[out] _cardInx - card from the deck
 * @return status
 * @retval ERR_OK on success
 * @retval ERR_NOT_INITIALIZED 
 */
ADTErr DeckRemoveLast(Deck *_deck, CardIndex *_cardInx);


/** 
 * @brief give the card from the index
 * @param[in] _index - index of the card
 * @param[out] _card the card
 * @return status
 * @retval ERR_OK on success
 * @retval ERR_NOT_INITIALIZED 
 */
ADTErr DeckSeeCard(CardIndex _index, Card *_card);

/** 
 * @brief print the card
 * @param[in] _cardInx - index of the card
 * @return status
 * @retval ERR_OK on success
 * @retval ERR_NOT_INITIALIZED 
 */
ADTErr PrintCard(CardIndex _cardInx);


/*test unit function*/
void DeckPrint(Deck*);

#endif /*__DECK_H__*/


