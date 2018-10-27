
#include "game.h"
#include "../ADTErr.h"
#include <stdio.h>
#include <stdlib.h> 


/** 
 *  @file hearts.c
 *  @brief The main file of the HEARTS game
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

int main()
{
	Game *myGame;
	ADTErr res;
	int choise1, choise2, isFirstGame;
	
	isFirstGame=TRUE;
	
	while(1)
	{
		printf("\n\nWelcome %sto the HEARTS game menu !\n\n",isFirstGame ? "" : "again ");
		printf("Enter \"1\" for starting a new game or \"0\" for exit :");
		scanf("%d",&choise1);
		
		switch (choise1)
		{
			case 1 :
				isFirstGame=FALSE;
				
				myGame = GameCreate();
				if(NULL==myGame)
				{
					perror("Allocation error occured !\n");
					exit(EXIT_FAILURE);
				}

				res = GameRun(myGame);
				if(ERR_OK != res)
				{
					perror("Error occured !\n");
					exit(EXIT_FAILURE);
				}
				
				printf("Enter \"1\" for printing ALL results per round or \"0\" for continue :");
				scanf("%d",&choise2);
				if(choise2 == 1)
				{
					GamePrintResults(myGame);
				}
				
				GameDestroy(myGame);
				break;
			
			default:
				printf("\n\nThank you for playing our great game !\n\n");
				exit(EXIT_SUCCESS);
				break;
		}
	}

	return 0;
}












