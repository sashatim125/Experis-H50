#include <stdio.h>

typedef int (*personalDuty)(char*) ;

struct person {
	char*	 name;
	int	 age;
	personalDuty func;
};

struct familyTree {
   	 int nMembers;
   	 struct person p[2];
   	 struct familyTree* 	next;
};

typedef struct person Person_t;
typedef struct familyTree FamilyTree_t;

int Refua(char* name)   { printf("I'm a doctor\n");	return 0; }
int Handasa(char* name) { printf("I'm an engineer\n");  return 0; }

FamilyTree_t Halakhmi = { 2, "Ilan", 28, Handasa, "Gilad", 26, Handasa, NULL};
FamilyTree_t Buchler  = { 2, "Rita", 38, Refua, "Brian", 30, Refua, NULL };

void DoIt(Person_t* ptPtr, char* name) {
	printf("%s ==> ",name);
	ptPtr->func(name);
}

int main() {
	DoIt(Halakhmi.p+0 , "Ilan");
	DoIt(Buchler.p+0  , "Rita");
	return 1;
}
