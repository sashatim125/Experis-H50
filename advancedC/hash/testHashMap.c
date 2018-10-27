#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "HashMap.h"
#include "../mu_test.h"


typedef struct
{
	size_t m_age;
	char* m_name;
	int* m_comment;
} Person;

/* destroy function */
void PersonDestroy(void* _PersonToDelete)
{
	free(((Person*)_PersonToDelete)->m_comment);
	free((Person*)_PersonToDelete);
}

/* predicate function */
int PredicateAboveX(void* _element, void* _context)
{
	return (((Person*)_element)->m_age > *((size_t*)_context));
}

/* action function */

int ActionPrintAge(void* _element, void* _context)
{
	printf("%lu ", ((Person*)_element)->m_age);
	
	return 1;
}

/* Equality Function */
int IsEqualName(const void* nameA, const void* nameB)
{
	return !strcmp((char*)nameA, (char*)nameB);
}

/* Hash Function */
size_t hashString(const void* _string)
{
	size_t i, sum = 0;
	char* str = (char*)_string;
	size_t len = strlen(str);
	
	for (i=0; i<len; ++i)
	{
		sum += (size_t)str[i];
	}
	
	return sum%11;
}

/**/

UNIT(test_create_normal)
	HashMap* pMap;
	ASSERT_THAT ((pMap = HashMap_Create(11, hashString, IsEqualName)) != NULL);
	HashMap_Destroy(&pMap, NULL, PersonDestroy);
END_UNIT

UNIT(test_create_capacity_zero)
	HashMap* pMap;
	ASSERT_THAT ((pMap = HashMap_Create(0, hashString, IsEqualName)) == NULL);
END_UNIT

UNIT(test_create_alloc_fail)
	HashMap* pMap;
	ASSERT_THAT ((pMap = HashMap_Create(99999999999, hashString, IsEqualName)) == NULL);
END_UNIT

/**/

UNIT(test_delete_double)
	HashMap* pMap;
	ASSERT_THAT ((pMap = HashMap_Create(11, hashString, IsEqualName)) != NULL);
	HashMap_Destroy(&pMap, NULL, PersonDestroy);
	HashMap_Destroy(&pMap, NULL, PersonDestroy);
END_UNIT

/**/

UNIT(test_insert_null_h_pointer)
	HashMap* pMap;
	Person *people[20];
	size_t i;
	char* names[20] = {"nir", "erez", "edo", "ori", "yotam", "gregor", "shali", "ralph", "andrey", "luuk", "hank", "roy", "rotem", "gil", "adam", "ethan", "evyatar", "naama", "iris", "noam"};
	for (i=0; i<20; ++i)
	{
		people[i] = (Person*) malloc(sizeof(Person));
		people[i]->m_name = names[i];
		people[i]->m_comment = (int*) malloc(i*sizeof(int));
		people[i]->m_age = i;
	}
	ASSERT_THAT ((pMap = HashMap_Create(11, hashString, IsEqualName)) != NULL);
	ASSERT_THAT (HashMap_Insert(NULL, names[0], people[0]) == MAP_UNINITIALIZED_ERROR);
	HashMap_Destroy(&pMap, NULL, PersonDestroy);
END_UNIT

UNIT(test_insert_null_k_pointer)
	HashMap* pMap;
	Person *people[20];
	size_t i;
	char* names[20] = {"nir", "erez", "edo", "ori", "yotam", "gregor", "shali", "ralph", "andrey", "luuk", "hank", "roy", "rotem", "gil", "adam", "ethan", "evyatar", "naama", "iris", "noam"};
	for (i=0; i<20; ++i)
	{
		people[i] = (Person*) malloc(sizeof(Person));
		people[i]->m_name = names[i];
		people[i]->m_comment = (int*) malloc(i*sizeof(int));
		people[i]->m_age = i;
	}
	ASSERT_THAT ((pMap = HashMap_Create(11, hashString, IsEqualName)) != NULL);
	ASSERT_THAT (HashMap_Insert(pMap, NULL, people[0]) == MAP_KEY_NULL_ERROR);
	HashMap_Destroy(&pMap, NULL, PersonDestroy);
END_UNIT
/*
UNIT(test_insert_null_v_pointer)
	HashMap* pMap;
	Person *people[20];
	size_t i;
	char* names[20] = {"nir", "erez", "edo", "ori", "yotam", "gregor", "shali", "ralph", "andrey", "luuk", "hank", "roy", "rotem", "gil", "adam", "ethan", "evyatar", "naama", "iris", "noam"};
	for (i=0; i<20; ++i)
	{
		people[i] = (Person*) malloc(sizeof(Person));
		people[i]->m_name = names[i];
		people[i]->m_comment = (int*) malloc(i*sizeof(int));
		people[i]->m_age = i;
	}
	ASSERT_THAT ((pMap = HashMap_Create(11, hashString, IsEqualName)) != NULL);
	ASSERT_THAT (HashMap_Insert(pMap, names[0], NULL) == MAP_KEY_NULL_ERROR);
	HashMap_Destroy(&pMap, NULL, PersonDestroy);
END_UNIT
*/
UNIT(test_insert_single)
	HashMap* pMap;
	Person *people[20];
	size_t i;
	char* names[20] = {"nir", "erez", "edo", "ori", "yotam", "gregor", "shali", "ralph", "andrey", "luuk", "hank", "roy", "rotem", "gil", "adam", "ethan", "evyatar", "naama", "iris", "noam"};
	for (i=0; i<20; ++i)
	{
		people[i] = (Person*) malloc(sizeof(Person));
		people[i]->m_name = names[i];
		people[i]->m_comment = (int*) malloc(i*sizeof(int));
		people[i]->m_age = i;
	}
	ASSERT_THAT ((pMap = HashMap_Create(11, hashString, IsEqualName)) != NULL);
	ASSERT_THAT (HashMap_Insert(pMap, names[5], people[5]) == MAP_SUCCESS);
	HashMap_Destroy(&pMap, NULL, PersonDestroy);
END_UNIT

UNIT(test_insert_multiple)
	HashMap* pMap;
	Person *people[20];
	size_t i;
	char* names[20] = {"nir", "erez", "edo", "ori", "yotam", "gregor", "shali", "ralph", "andrey", "luuk", "hank", "roy", "rotem", "gil", "adam", "ethan", "evyatar", "naama", "iris", "noam"};
	for (i=0; i<20; ++i)
	{
		people[i] = (Person*) malloc(sizeof(Person));
		people[i]->m_name = names[i];
		people[i]->m_comment = (int*) malloc(i*sizeof(int));
		people[i]->m_age = i;
	}
	ASSERT_THAT ((pMap = HashMap_Create(11, hashString, IsEqualName)) != NULL);
	for (i=0; i<15; ++i)
	{
		ASSERT_THAT (HashMap_Insert(pMap, people[i]->m_name, people[i]) == MAP_SUCCESS);
	}
	HashMap_Destroy(&pMap, NULL, PersonDestroy);
END_UNIT

UNIT(test_insert_duplicate)
	HashMap* pMap;
	Person *people[20];
	size_t i;
	char* names[20] = {"nir", "erez", "edo", "ori", "yotam", "gregor", "shali", "ralph", "andrey", "luuk", "hank", "roy", "rotem", "gil", "adam", "ethan", "evyatar", "naama", "iris", "noam"};
	for (i=0; i<20; ++i)
	{
		people[i] = (Person*) malloc(sizeof(Person));
		people[i]->m_name = names[i];
		people[i]->m_comment = (int*) malloc(i*sizeof(int));
		people[i]->m_age = i;
	}
	ASSERT_THAT ((pMap = HashMap_Create(11, hashString, IsEqualName)) != NULL);
	ASSERT_THAT (HashMap_Insert(pMap, names[5], people[5]) == MAP_SUCCESS);
	ASSERT_THAT (HashMap_Insert(pMap, names[5], people[5]) == MAP_KEY_DUPLICATE_ERROR);
END_UNIT

/**/

UNIT(test_remove_null_h_pointer)
	void *pValue, *pKey;
	ASSERT_THAT (HashMap_Remove(NULL, "nir", &pKey, &pValue) == MAP_UNINITIALIZED_ERROR);
END_UNIT

UNIT(test_remove_null_k_pointer)
	HashMap* pMap;
	Person *people[20];
	size_t i;
	void *pValue, *pKey;
	char* names[20] = {"nir", "erez", "edo", "ori", "yotam", "gregor", "shali", "ralph", "andrey", "luuk", "hank", "roy", "rotem", "gil", "adam", "ethan", "evyatar", "naama", "iris", "noam"};
	for (i=0; i<20; ++i)
	{
		people[i] = (Person*) malloc(sizeof(Person));
		people[i]->m_name = names[i];
		people[i]->m_comment = (int*) malloc(i*sizeof(int));
		people[i]->m_age = i;
	}
	ASSERT_THAT ((pMap = HashMap_Create(11, hashString, IsEqualName)) != NULL);
	for (i=0; i<15; ++i)
	{
		ASSERT_THAT (HashMap_Insert(pMap, names[i], people[i]) == MAP_SUCCESS);
	}
	ASSERT_THAT (HashMap_Remove(pMap, NULL, &pKey, &pValue) == MAP_KEY_NULL_ERROR);
	HashMap_Destroy(&pMap, NULL, PersonDestroy);
END_UNIT

UNIT(test_remove_null_pk_pointer)
	HashMap* pMap;
	Person *people[20];
	size_t i;
	void *pValue;
	char* names[20] = {"nir", "erez", "edo", "ori", "yotam", "gregor", "shali", "ralph", "andrey", "luuk", "hank", "roy", "rotem", "gil", "adam", "ethan", "evyatar", "naama", "iris", "noam"};
	for (i=0; i<20; ++i)
	{
		people[i] = (Person*) malloc(sizeof(Person));
		people[i]->m_name = names[i];
		people[i]->m_comment = (int*) malloc(i*sizeof(int));
		people[i]->m_age = i;
	}
	ASSERT_THAT ((pMap = HashMap_Create(11, hashString, IsEqualName)) != NULL);
	for (i=0; i<15; ++i)
	{
		ASSERT_THAT (HashMap_Insert(pMap, names[i], people[i]) == MAP_SUCCESS);
	}
	ASSERT_THAT (HashMap_Remove(pMap, names[2], NULL, &pValue) == MAP_UNINITIALIZED_ERROR);
	HashMap_Destroy(&pMap, NULL, PersonDestroy);
END_UNIT

UNIT(test_remove_null_pv_pointer)
	HashMap* pMap;
	Person *people[20];
	size_t i;
	void *pKey;
	char* names[20] = {"nir", "erez", "edo", "ori", "yotam", "gregor", "shali", "ralph", "andrey", "luuk", "hank", "roy", "rotem", "gil", "adam", "ethan", "evyatar", "naama", "iris", "noam"};
	for (i=0; i<20; ++i)
	{
		people[i] = (Person*) malloc(sizeof(Person));
		people[i]->m_name = names[i];
		people[i]->m_comment = (int*) malloc(i*sizeof(int));
		people[i]->m_age = i;
	}
	ASSERT_THAT ((pMap = HashMap_Create(11, hashString, IsEqualName)) != NULL);
	for (i=0; i<15; ++i)
	{
		ASSERT_THAT (HashMap_Insert(pMap, names[i], people[i]) == MAP_SUCCESS);
	}
	ASSERT_THAT (HashMap_Remove(pMap, names[2], &pKey, NULL) == MAP_UNINITIALIZED_ERROR);
	HashMap_Destroy(&pMap, NULL, PersonDestroy);
END_UNIT

UNIT(test_remove_normal)
	HashMap* pMap;
	Person *people[20];
	size_t i;
	void *pValue, *pKey;
	char* names[20] = {"nir", "erez", "edo", "ori", "yotam", "gregor", "shali", "ralph", "andrey", "luuk", "hank", "roy", "rotem", "gil", "adam", "ethan", "evyatar", "naama", "iris", "noam"};
	for (i=0; i<20; ++i)
	{
		people[i] = (Person*) malloc(sizeof(Person));
		people[i]->m_name = names[i];
		people[i]->m_comment = (int*) malloc(i*sizeof(int));
		people[i]->m_age = i;
	}
	ASSERT_THAT ((pMap = HashMap_Create(11, hashString, IsEqualName)) != NULL);
	for (i=0; i<15; ++i)
	{
		ASSERT_THAT (HashMap_Insert(pMap, names[i], people[i]) == MAP_SUCCESS);
	}
	ASSERT_THAT (HashMap_Remove(pMap, names[2], &pKey, &pValue) == MAP_SUCCESS);
	ASSERT_THAT (pKey == names[2]);
	ASSERT_THAT (pValue == people[2]);
	ASSERT_THAT (HashMap_Remove(pMap, names[11], &pKey, &pValue) == MAP_SUCCESS);
	ASSERT_THAT (pKey == names[11] && pValue == people[11]);
	HashMap_Destroy(&pMap, NULL, PersonDestroy);
END_UNIT

UNIT(test_remove_no_match)
	HashMap* pMap;
	Person *people[20];
	size_t i;
	void *pValue, *pKey;
	char* names[20] = {"nir", "erez", "edo", "ori", "yotam", "gregor", "shali", "ralph", "andrey", "luuk", "hank", "roy", "rotem", "gil", "adam", "ethan", "evyatar", "naama", "iris", "noam"};
	for (i=0; i<20; ++i)
	{
		people[i] = (Person*) malloc(sizeof(Person));
		people[i]->m_name = names[i];
		people[i]->m_comment = (int*) malloc(i*sizeof(int));
		people[i]->m_age = i;
	}
	ASSERT_THAT ((pMap = HashMap_Create(11, hashString, IsEqualName)) != NULL);
	for (i=0; i<15; ++i)
	{
		ASSERT_THAT (HashMap_Insert(pMap, names[i], people[i]) == MAP_SUCCESS);
	}
	ASSERT_THAT (HashMap_Remove(pMap, names[18], &pKey, &pValue) == MAP_KEY_NOT_FOUND_ERROR);
	HashMap_Destroy(&pMap, NULL, PersonDestroy);
END_UNIT


/**/

UNIT(test_find_null_h_pointer)
	HashMap* pMap;
	void *pValue;
	char* names[20] = {"nir", "erez", "edo", "ori", "yotam", "gregor", "shali", "ralph", "andrey", "luuk", "hank", "roy", "rotem", "gil", "adam", "ethan", "evyatar", "naama", "iris", "noam"};
	ASSERT_THAT (HashMap_Find(NULL, names[5], &pValue) == MAP_UNINITIALIZED_ERROR);
	HashMap_Destroy(&pMap, NULL, PersonDestroy);
END_UNIT

UNIT(test_find_null_k_pointer)
	HashMap* pMap;
	Person *people[20];
	size_t i;
	void *pValue;
	char* names[20] = {"nir", "erez", "edo", "ori", "yotam", "gregor", "shali", "ralph", "andrey", "luuk", "hank", "roy", "rotem", "gil", "adam", "ethan", "evyatar", "naama", "iris", "noam"};
	for (i=0; i<20; ++i)
	{
		people[i] = (Person*) malloc(sizeof(Person));
		people[i]->m_name = names[i];
		people[i]->m_comment = (int*) malloc(i*sizeof(int));
		people[i]->m_age = i;
	}
	ASSERT_THAT ((pMap = HashMap_Create(11, hashString, IsEqualName)) != NULL);
	for (i=0; i<15; ++i)
	{
		ASSERT_THAT (HashMap_Insert(pMap, names[i], people[i]) == MAP_SUCCESS);
	}
	ASSERT_THAT (HashMap_Find(pMap, NULL, &pValue) == MAP_KEY_NULL_ERROR);
	HashMap_Destroy(&pMap, NULL, PersonDestroy);
END_UNIT

UNIT(test_find_null_pv_pointer)
	HashMap* pMap;
	Person *people[20];
	size_t i;
	char* names[20] = {"nir", "erez", "edo", "ori", "yotam", "gregor", "shali", "ralph", "andrey", "luuk", "hank", "roy", "rotem", "gil", "adam", "ethan", "evyatar", "naama", "iris", "noam"};
	for (i=0; i<20; ++i)
	{
		people[i] = (Person*) malloc(sizeof(Person));
		people[i]->m_name = names[i];
		people[i]->m_comment = (int*) malloc(i*sizeof(int));
		people[i]->m_age = i;
	}
	ASSERT_THAT ((pMap = HashMap_Create(11, hashString, IsEqualName)) != NULL);
	for (i=0; i<15; ++i)
	{
		ASSERT_THAT (HashMap_Insert(pMap, names[i], people[i]) == MAP_SUCCESS);
	}
	ASSERT_THAT (HashMap_Find(pMap, names[5], NULL) == MAP_UNINITIALIZED_ERROR);
	HashMap_Destroy(&pMap, NULL, PersonDestroy);
END_UNIT


UNIT(test_find_poz)
	HashMap* pMap;
	Person *people[20];
	size_t i;
	void *pValue;
	char* names[20] = {"nir", "erez", "edo", "ori", "yotam", "gregor", "shali", "ralph", "andrey", "luuk", "hank", "roy", "rotem", "gil", "adam", "ethan", "evyatar", "naama", "iris", "noam"};
	for (i=0; i<20; ++i)
	{
		people[i] = (Person*) malloc(sizeof(Person));
		people[i]->m_name = names[i];
		people[i]->m_comment = (int*) malloc(i*sizeof(int));
		people[i]->m_age = i;
	}
	ASSERT_THAT ((pMap = HashMap_Create(11, hashString, IsEqualName)) != NULL);
	for (i=0; i<15; ++i)
	{
		ASSERT_THAT (HashMap_Insert(pMap, names[i], people[i]) == MAP_SUCCESS);
	}
	ASSERT_THAT (HashMap_Find(pMap, names[5], &pValue) == MAP_SUCCESS);
	ASSERT_THAT (pValue == people[5]);
	HashMap_Destroy(&pMap, NULL, PersonDestroy);
END_UNIT

UNIT(test_find_neg)
	HashMap* pMap;
	Person *people[20];
	size_t i;
	void *pValue;
	char* names[20] = {"nir", "erez", "edo", "ori", "yotam", "gregor", "shali", "ralph", "andrey", "luuk", "hank", "roy", "rotem", "gil", "adam", "ethan", "evyatar", "naama", "iris", "noam"};
	for (i=0; i<20; ++i)
	{
		people[i] = (Person*) malloc(sizeof(Person));
		people[i]->m_name = names[i];
		people[i]->m_comment = (int*) malloc(i*sizeof(int));
		people[i]->m_age = i;
	}
	ASSERT_THAT ((pMap = HashMap_Create(11, hashString, IsEqualName)) != NULL);
	for (i=0; i<15; ++i)
	{
		ASSERT_THAT (HashMap_Insert(pMap, names[i], people[i]) == MAP_SUCCESS);
	}
	ASSERT_THAT (HashMap_Find(pMap, names[17], &pValue) == MAP_KEY_NOT_FOUND_ERROR);
	HashMap_Destroy(&pMap, NULL, PersonDestroy);
END_UNIT

/**/

UNIT(test_rehash_same_capacity)
	HashMap* pMap;
	Person *people[20];
	size_t i;
	char* names[20] = {"nir", "erez", "edo", "ori", "yotam", "gregor", "shali", "ralph", "andrey", "luuk", "hank", "roy", "rotem", "gil", "adam", "ethan", "evyatar", "naama", "iris", "noam"};
	for (i=0; i<20; ++i)
	{
		people[i] = (Person*) malloc(sizeof(Person));
		people[i]->m_name = names[i];
		people[i]->m_comment = (int*) malloc(i*sizeof(int));
		people[i]->m_age = i;
	}
	ASSERT_THAT ((pMap = HashMap_Create(11, hashString, IsEqualName)) != NULL);
	for (i=0; i<15; ++i)
	{
		ASSERT_THAT (HashMap_Insert(pMap, people[i]->m_name, people[i]) == MAP_SUCCESS);
	}
	ASSERT_THAT (HashMap_Rehash(pMap, 11) == MAP_SUCCESS);
	HashMap_Destroy(&pMap, NULL, PersonDestroy);
END_UNIT

UNIT(test_rehash_normal)
	HashMap* pMap;
	Person *people[20];
	size_t i;
	char* names[20] = {"nir", "erez", "edo", "ori", "yotam", "gregor", "shali", "ralph", "andrey", "luuk", "hank", "roy", "rotem", "gil", "adam", "ethan", "evyatar", "naama", "iris", "noam"};
	for (i=0; i<20; ++i)
	{
		people[i] = (Person*) malloc(sizeof(Person));
		people[i]->m_name = names[i];
		people[i]->m_comment = (int*) malloc(i*sizeof(int));
		people[i]->m_age = i;
	}
	ASSERT_THAT ((pMap = HashMap_Create(11, hashString, IsEqualName)) != NULL);
	for (i=0; i<15; ++i)
	{
		ASSERT_THAT (HashMap_Insert(pMap, people[i]->m_name, people[i]) == MAP_SUCCESS);
	}
	ASSERT_THAT (HashMap_Rehash(pMap, 17) == MAP_SUCCESS);
	HashMap_Destroy(&pMap, NULL, PersonDestroy);
END_UNIT

UNIT(test_rehash_less_capacity)
	HashMap* pMap;
	Person *people[20];
	size_t i;
	char* names[20] = {"nir", "erez", "edo", "ori", "yotam", "gregor", "shali", "ralph", "andrey", "luuk", "hank", "roy", "rotem", "gil", "adam", "ethan", "evyatar", "naama", "iris", "noam"};
	for (i=0; i<20; ++i)
	{
		people[i] = (Person*) malloc(sizeof(Person));
		people[i]->m_name = names[i];
		people[i]->m_comment = (int*) malloc(i*sizeof(int));
		people[i]->m_age = i;
	}
	ASSERT_THAT ((pMap = HashMap_Create(11, hashString, IsEqualName)) != NULL);
	for (i=0; i<15; ++i)
	{
		ASSERT_THAT (HashMap_Insert(pMap, people[i]->m_name, people[i]) == MAP_SUCCESS);
	}
	ASSERT_THAT (HashMap_Rehash(pMap, 7) == MAP_SUCCESS);
	HashMap_Destroy(&pMap, NULL, PersonDestroy);
END_UNIT

UNIT(test_rehash_alloc_fail)
	HashMap* pMap;
	Person *people[20];
	size_t i;
	char* names[20] = {"nir", "erez", "edo", "ori", "yotam", "gregor", "shali", "ralph", "andrey", "luuk", "hank", "roy", "rotem", "gil", "adam", "ethan", "evyatar", "naama", "iris", "noam"};
	for (i=0; i<20; ++i)
	{
		people[i] = (Person*) malloc(sizeof(Person));
		people[i]->m_name = names[i];
		people[i]->m_comment = (int*) malloc(i*sizeof(int));
		people[i]->m_age = i;
	}
	ASSERT_THAT ((pMap = HashMap_Create(11, hashString, IsEqualName)) != NULL);
	for (i=0; i<15; ++i)
	{
		ASSERT_THAT (HashMap_Insert(pMap, people[i]->m_name, people[i]) == MAP_SUCCESS);
	}
	ASSERT_THAT (HashMap_Rehash(pMap, 999999999999) == MAP_ALLOCATION_ERROR);
	HashMap_Destroy(&pMap, NULL, PersonDestroy);
END_UNIT

UNIT(test_rehash_zero_capacity)
	HashMap* pMap;
	Person *people[20];
	size_t i;
	char* names[20] = {"nir", "erez", "edo", "ori", "yotam", "gregor", "shali", "ralph", "andrey", "luuk", "hank", "roy", "rotem", "gil", "adam", "ethan", "evyatar", "naama", "iris", "noam"};
	for (i=0; i<20; ++i)
	{
		people[i] = (Person*) malloc(sizeof(Person));
		people[i]->m_name = names[i];
		people[i]->m_comment = (int*) malloc(i*sizeof(int));
		people[i]->m_age = i;
	}
	ASSERT_THAT ((pMap = HashMap_Create(11, hashString, IsEqualName)) != NULL);
	for (i=0; i<15; ++i)
	{
		ASSERT_THAT (HashMap_Insert(pMap, people[i]->m_name, people[i]) == MAP_SUCCESS);
	}
	ASSERT_THAT (HashMap_Rehash(pMap, 0) == MAP_ALLOCATION_ERROR);
	HashMap_Destroy(&pMap, NULL, PersonDestroy);
END_UNIT

/**/

UNIT(test_size_normal)
	HashMap* pMap;
	Person *people[20];
	size_t i;
	char* names[20] = {"nir", "erez", "edo", "ori", "yotam", "gregor", "shali", "ralph", "andrey", "luuk", "hank", "roy", "rotem", "gil", "adam", "ethan", "evyatar", "naama", "iris", "noam"};
	for (i=0; i<20; ++i)
	{
		people[i] = (Person*) malloc(sizeof(Person));
		people[i]->m_name = names[i];
		people[i]->m_comment = (int*) malloc(i*sizeof(int));
		people[i]->m_age = i;
	}
	ASSERT_THAT ((pMap = HashMap_Create(11, hashString, IsEqualName)) != NULL);
	for (i=0; i<15; ++i)
	{
		ASSERT_THAT (HashMap_Insert(pMap, people[i]->m_name, people[i]) == MAP_SUCCESS);
	}
	ASSERT_THAT (HashMap_Size(pMap) == 15);
	HashMap_Destroy(&pMap, NULL, PersonDestroy);
END_UNIT

UNIT(test_size_stress)
	HashMap* pMap;
	Person *people[20];
	size_t i;
	void *pKey, *pValue;
	char* names[20] = {"nir", "erez", "edo", "ori", "yotam", "gregor", "shali", "ralph", "andrey", "luuk", "hank", "roy", "rotem", "gil", "adam", "ethan", "evyatar", "naama", "iris", "noam"};
	for (i=0; i<20; ++i)
	{
		people[i] = (Person*) malloc(sizeof(Person));
		people[i]->m_name = names[i];
		people[i]->m_comment = (int*) malloc(i*sizeof(int));
		people[i]->m_age = i;
	}
	ASSERT_THAT ((pMap = HashMap_Create(11, hashString, IsEqualName)) != NULL);
	for (i=0; i<15; ++i)
	{
		ASSERT_THAT (HashMap_Insert(pMap, people[i]->m_name, people[i]) == MAP_SUCCESS);
	}
	ASSERT_THAT (HashMap_Size(pMap) == 15);
	ASSERT_THAT (HashMap_Remove(pMap, names[0], &pKey, &pValue) == MAP_SUCCESS);
	ASSERT_THAT (HashMap_Size(pMap) == 14);
	ASSERT_THAT (HashMap_Rehash(pMap, 7) == MAP_SUCCESS);
	ASSERT_THAT (HashMap_Size(pMap) == 14);
	HashMap_Destroy(&pMap, NULL, PersonDestroy);
END_UNIT

/**/

UNIT(test_stats)
	HashMap* pMap;
	Person *people[20];
	size_t i;
	Map_Stats stats;
	char* names[20] = {"nir", "erez", "edo", "ori", "yotam", "gregor", "shali", "ralph", "andrey", "luuk", "hank", "roy", "rotem", "gil", "adam", "ethan", "evyatar", "naama", "iris", "noam"};
	for (i=0; i<20; ++i)
	{
		people[i] = (Person*) malloc(sizeof(Person));
		people[i]->m_name = names[i];
		people[i]->m_comment = (int*) malloc(i*sizeof(int));
		people[i]->m_age = i;
	}
	ASSERT_THAT ((pMap = HashMap_Create(11, hashString, IsEqualName)) != NULL);
	for (i=0; i<15; ++i)
	{
		ASSERT_THAT (HashMap_Insert(pMap, people[i]->m_name, people[i]) == MAP_SUCCESS);
	}
	stats = HashMap_GetStatistics(pMap);
	printf("pairs: %lu, coll: %lu, bkts: %lu, chains: %lu, max: %lu, ave: %lu\n", stats.pairs, stats.collisions, stats.buckets, stats.chains, stats.maxChainLength, stats.averageChainLength); 
	ASSERT_THAT (HashMap_Rehash(pMap, 7) == MAP_SUCCESS);
	stats = HashMap_GetStatistics(pMap);
	printf("pairs: %lu, coll: %lu, bkts: %lu, chains: %lu, max: %lu, ave: %lu\n", stats.pairs, stats.collisions, stats.buckets, stats.chains, stats.maxChainLength, stats.averageChainLength); 
	ASSERT_THAT (HashMap_Rehash(pMap, 101) == MAP_SUCCESS);
	stats = HashMap_GetStatistics(pMap);
	printf("pairs: %lu, coll: %lu, bkts: %lu, chains: %lu, max: %lu, ave: %lu\n", stats.pairs, stats.collisions, stats.buckets, stats.chains, stats.maxChainLength, stats.averageChainLength); 
	stats = HashMap_GetStatistics(NULL);
	printf("pairs: %lu, coll: %lu, bkts: %lu, chains: %lu, max: %lu, ave: %lu\n", stats.pairs, stats.collisions, stats.buckets, stats.chains, stats.maxChainLength, stats.averageChainLength); 
	HashMap_Destroy(&pMap, NULL, PersonDestroy);
END_UNIT

/**/

TEST_SUITE(Hash Map test)
	TEST(test_create_normal)
	TEST(test_create_capacity_zero)
	IGNORE_TEST(test_create_alloc_fail)
	TEST(test_delete_double)
	TEST(test_insert_null_h_pointer)
	TEST(test_insert_null_k_pointer)
	/*TEST(test_insert_null_v_pointer)*/
	TEST(test_insert_single)
	TEST(test_insert_multiple)
	TEST(test_insert_duplicate)
	TEST(test_remove_null_h_pointer)
	TEST(test_remove_null_k_pointer)
	TEST(test_remove_null_pk_pointer)
	TEST(test_remove_null_pv_pointer)
	TEST(test_remove_normal)
	TEST(test_remove_no_match)
	TEST(test_find_null_h_pointer)
	TEST(test_find_null_k_pointer)
	TEST(test_find_null_pv_pointer)
	TEST(test_find_poz)
	TEST(test_find_neg)
	TEST(test_rehash_normal)
	TEST(test_rehash_same_capacity)
	TEST(test_rehash_less_capacity)
	TEST(test_rehash_zero_capacity)
	IGNORE_TEST(test_rehash_alloc_fail)
	TEST(test_size_normal)
	TEST(test_size_stress)
	TEST(test_stats)
END_SUITE 

