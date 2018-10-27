
#ifndef __GAME_H__
#define __GAME_H__

#include "../ADTErr.h"
#include <stdio.h>

/** 
 *  @file game.h
 *  @brief The Game type and API definitions
 *	
 *  @details 
 *  
 *
 *  @author Alexander Timoshenko sashatim125@gmail.com
 * 
 */


#ifndef RESULTS_FILE
#define RESULTS_FILE "heartsGameResults.txt"
#endif /*RESULTS_FILE*/


typedef struct Game Game;

/** 
 * @brief creates the game
 * @return new game
 */
Game* GameCreate();

/** 
 * @brief destroys the game
 * @param[in] _game - the game to be destroyed
 */
void GameDestroy(Game *_game);

/** 
 * @brief running the game
 * @param[in] _game - the game to run
 * @return status
 * @retval ERR_OK on success
 * @retval ERR_NOT_INITIALIZED 
 */
ADTErr GameRun(Game *_game);

/** 
 * @brief print the results of the game by rounds from the file
 * @param[in] _game - the game
 */
void GamePrintResults(Game *_game);

#endif /*__GAME_H__*/


