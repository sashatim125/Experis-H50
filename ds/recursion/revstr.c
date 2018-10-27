/*This file contains the main and revers string function.
 *AUTHOR        : Timoshenko Alexander
 *LAST MODIFIED : 13.12.2017
 */

#include <stdio.h>

#define BUFF_SIZE 50

struct Member
{
	char c;
	struct Member *next;
};

typedef struct Member Member;

void RevString(char *_str,Member *_head, Member *_me)
{
	Member meMember,*nextMem;
	
	meMember.c=*_str;
	meMember.next=NULL;
	
	if (*_str=='\0')
	{
		_me->next=&meMember;
		for (nextMem=_head ; nextMem->next!=NULL ; nextMem=nextMem->next)
		{
			*--_str=nextMem->c;	
		}
		return;
	}
	
	if (_head==NULL) 
	{
		RevString(_str+1,&meMember,&meMember);
	}else
	{
		_me->next=&meMember;
		RevString(_str+1,_head,&meMember);
	}
}

int main()
{
	char buff[BUFF_SIZE];
	
	printf("Please enter your string :");
	scanf("%s",buff);

	printf("Reversed string \"%s\" is ",buff);
	RevString(buff,NULL,NULL);
	printf("\"%s\".\n",buff);
		
	return 0;	
}	
	
	
	
