
#ifndef __P_PONG_PLAYER_H__
#define __P_PONG_PLAYER_H__


/** 
 *  @file ppongPlayer.h
 *  @brief PingPong Player
 *	
 *  @details  see comments
 *  
 *
 *  @author Alexander Timoshenko sashatim125@gmail.com
 * 
 */


#define QUEUE_SIZE 8

typedef struct PpongPlayer PpongPlayer;


PpongPlayer* PpongPlayer_Create(unsigned _numOfProds, unsigned _numOfCons, unsigned _numOfMsgs, long _delay_ms);


void PpongPlayer_Destory(PpongPlayer* _ppongPlayer);


int PpongPlayer_Run(PpongPlayer* _ppongPlayer);


#endif /*__P_PONG_PLAYER_H__*/


