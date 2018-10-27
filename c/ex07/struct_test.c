
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define NAME_SIZE 30
#define PERSONS 3

typedef struct {
	char name[NAME_SIZE];
	unsigned int id;
} person_t;

int person_id_cmp(const void *per1,const void *per2){

	return ((person_t*)per1)->id-((person_t*)per2)->id;
}

int person_name_cmp(const void *per1,const void *per2){

	return strcmp((((person_t*)per1)->name),(((person_t*)per2)->name));
}

void print_persons(person_t* persons, size_t size) {

	size_t i;
	
	for (i=0 ; i<size ; ++i){

		printf("The %lu-th person's name is %s.\n",i+1,(persons+i)->name);
		printf("The %lu-th person's ID is %d.\n",i+1,(persons+i)->id);
	}
}


int main (){

	person_t persons[PERSONS];
	int i;
	
	for (i=0 ; i<PERSONS ; i++) {
		printf("Enter the name of %d-th person :",i+1);
		scanf("%s",((persons+i)->name));
		printf("Enter the ID of %d-th person :",i+1);
		scanf("%d",&((persons+i)->id));	
	}
	printf("Persons record unsorted :\n");
	print_persons(persons,PERSONS);
	putchar('\n');
	
	printf("Persons record sorted by ID :\n");
	qsort((void *)persons,PERSONS,sizeof(person_t),person_id_cmp);
	print_persons(persons,PERSONS);
	
	putchar('\n');
	
	printf("Persons record sorted by name :\n");
	qsort((void *)persons,PERSONS,sizeof(person_t),person_name_cmp);
	print_persons(persons,PERSONS);
	
	
	
	return 0;
}

