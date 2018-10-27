
#include "game.h"
#include "round.h"
#include "player.h"
#include <stdlib.h> 
#include <stdio.h> 

/** 
 *  @file game.c
 *  @brief The Game type and API implementations
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

#ifndef NAME_SIZE
#define NAME_SIZE 20
#endif /*NAME_SIZE*/

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 1024
#endif /*BUFFER_SIZE*/

#ifndef MAX_GAME_SCORE
#define MAX_GAME_SCORE 100
#endif /*MAX_GAME_SCORE*/

#define PRINT_ROUND_RESULTS(file,round) \
{\
	fprintf(file,"The results of the round number %u are :\n\n",round+1);\
	PrintResults(file,_game);\
}

#define PRINT_FINAL_RESULTS(file) \
{\
	fprintf(file,"The FINAL results of the game are :\n\n");\
	PrintResults(file,_game);\
	PrintFinalResults(file,_game);\
}


struct Game
{
	int m_magicNum;
	
	FILE *m_output;
	
	unsigned m_minScore;
	unsigned m_maxScore;
	
	char m_names[NUM_OF_PLAYERS][NAME_SIZE];
	Player *m_players[NUM_OF_PLAYERS];
	
};



static void PrintResults(FILE *_file, Game *_game);

static void PrintFinalResults(FILE *_file, Game *_game);

Game* GameCreate()
{
	Game *newGame;
	unsigned i, j;
	
	printf("\n\n\n!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
	printf("!!!!!!!!!! Welcome to the HEARTS game !!!!!!!!!!!\n");
	printf("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n\n\n");
	
	
	newGame = (Game*)malloc(sizeof(Game));
	if(NULL==newGame)
	{
		return NULL;
	}
	
	newGame->m_output = fopen(RESULTS_FILE,"w+");
	if(NULL==newGame->m_output)
	{
		free(newGame);
		return NULL;
	}
	
	newGame->m_minScore = 0;
	newGame->m_minScore = MAX_GAME_SCORE*10;
	
	newGame->m_magicNum = MAGIC_NUMBER;
	
	for(i=0 ; i < NUM_OF_PLAYERS ; ++i)
	{
		printf("\nPlease enter the name of the %2u-th player %s:",i+1,(i==0)?"- your name":" (computer)");
		scanf("%s",newGame->m_names[i]);
	
		newGame->m_players[i] = PlayerCreate((i==0)?HUMAN:COMPUTER,newGame->m_names[i]);
		if(NULL==newGame->m_players[i])
		{
			for(j=0 ; j<i ; ++j)
			{
				PlayerDestroy(newGame->m_players[j]);
			}
			free(newGame);
			return NULL;
		}
	}
	printf("\n\n");
		
	return newGame;
}


void GameDestroy(Game *_game)
{
	unsigned i;
	
	if((NULL==_game)||(MAGIC_NUMBER != _game->m_magicNum))
	{
		return;
	}
	
	for(i=0 ; i < NUM_OF_PLAYERS ; ++i)
	{
		PlayerDestroy(_game->m_players[i]);
	}
	
	fclose(_game->m_output);
	
	_game->m_magicNum = 0;
	
	free(_game);
}



ADTErr GameRun(Game *_game)
{
	Round *nextRound;
	Exchange exchangeMethod;
	unsigned roundCount;
	ADTErr res;

	if(NULL==_game)
	{
		return ERR_NOT_INITIALIZED;
	}
	
	for(roundCount=0, exchangeMethod=LEFT;_game->m_maxScore < MAX_GAME_SCORE; 
		++roundCount, exchangeMethod=(exchangeMethod+1)%N_EXCHANGE)
	{
		nextRound = RoundCreate(_game->m_players,exchangeMethod);
		if(NULL==nextRound)
		{
			return ERR_NOT_INITIALIZED;
		}
	
		res = RoundPlay(nextRound);
		if (ERR_OK != res)
		{
			return res;
		}
		
		PRINT_ROUND_RESULTS(stdout,roundCount)
		PRINT_ROUND_RESULTS(_game->m_output,roundCount)
	}
	
	PRINT_FINAL_RESULTS(stdout)
	PRINT_FINAL_RESULTS(_game->m_output)

	return ERR_OK;
}



void GamePrintResults(Game *_game)
{
	char buff[BUFFER_SIZE]={'\0'};
	
	if(NULL==_game)
	{
		return ;
	}
	
	rewind(_game->m_output);

	while(!feof(_game->m_output))
	{
		fputs(buff,stdout);
		fgets(buff,BUFFER_SIZE,_game->m_output);
	}
}


static void PrintResults(FILE *_file, Game *_game)
{
	unsigned i , score ;
	const char *name;
	
	if((NULL==_game)||(NULL==_file))
	{
		return;
	}
	
	for(i=0 ; i < NUM_OF_PLAYERS ; ++i)
	{
		PlayerGetName(_game->m_players[i],&name);
		PlayerGetPoints(_game->m_players[i],&score);
		
		if(score > _game->m_maxScore)
		{
			_game->m_maxScore = score;
		}
		else if(score < _game->m_minScore)
		{
			 _game->m_minScore = score;
		}
		
		fprintf(_file," %-20s has %4u points.\n\n",name,score);
	}
	
	fprintf(_file,"\n\n");
}

static void PrintFinalResults(FILE *_file, Game *_game)
{
	unsigned i , score ;
	const char *name;
	
	if((NULL==_game)||(NULL==_file))
	{
		return;
	}
	
	fprintf(_file,"\n\n\n!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
	fprintf(_file,"!!!!!!!!!! The WIN/LOST table !!!!!!!!!!!\n");
	fprintf(_file,"!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n\n\n");	
	
	for(i=0 ; i < NUM_OF_PLAYERS ; ++i)
	{
		PlayerGetName(_game->m_players[i],&name);
		PlayerGetPoints(_game->m_players[i],&score);
		
		if(score == _game->m_minScore)
		{
			fprintf(_file," %-20s is a WINNER !!!\n\n",name);
		}
		else if(score == _game->m_maxScore)
		{
			fprintf(_file," %-20s is a loser  ...\n\n",name);
		}		
	}
	
	fprintf(_file,"\n\n");
}


















