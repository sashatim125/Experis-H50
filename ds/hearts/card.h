
#ifndef __CARD_H__
#define __CARD_H__

#include "../ADTErr.h"

/** 
 *  @file card.h
 *  @brief The Card type definitions
 *	
 *  @details 
 *  
 *
 *  @author Alexander Timoshenko sashatim125@gmail.com
 * 
 */
 

#ifndef TRUE
#define TRUE 1
#endif /*TRUE*/

#ifndef FALSE 
#define FALSE 0
#endif /*FALSE*/


typedef int CardIndex;

typedef enum Suit
{
	HEARTS,
	SPADES,
	DIAMONDS,
	CLUBS,
	N_SUITS
} Suit;


typedef enum Rank
{
	R2,
	R3,
	R4,
	R5,
	R6,
	R7,
	R8,
	R9,
	R10,
	JAKE,
	QUEEN,
	KING,
	ACE,
	N_RANKS
} Rank;


typedef struct Card
{
	Suit m_suit;
	Rank m_rank;
} Card;



#endif /*__CARD_H__*/
 
