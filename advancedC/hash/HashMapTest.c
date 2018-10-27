#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../mu_test.h"
#include "HashMap.h"

#define STRING_SIZE 512


size_t HashStringToInt(const void* _str)
{
	size_t i, sum;
	char* str = (char*)_str;
	size_t len = strlen(str);
	for(sum = 0 , i = 0; i < len; i++)
	{
		sum += (size_t)str[i];
	}
	return sum % 101;
}

/****************************************************/

int FindKey(const void* _firstKey, const void* _secondKey)
{
	return (!strcmp((char*)_firstKey, (char*)_secondKey));
} 

/*******************************************************/
void KeyDestroy(void* _key)
{
	free(_key);
}
/******************************************************/
void ValDestroy(void* _val)
{
	free(_val);
}
/*******************************************************/

int MyPrint(const void* _key, void* _value, void* _context)
{
	printf("Key is %s\tValue is %s\n",(char*)_key, (char*)_value);
	return 1;
}
/*************************************************************************/

int MyKeyAndValueAction(const void* _key, void* _value, void* _context)
{
	return (strcmp((char*)_key, (char*)_context));
}



/*TODO Evrey Index IN the Hash is Buckt*/



UNIT(TestHashFunction)
	char str[] = "Alona";
	size_t check1;
	size_t check2;
	check1 = HashStringToInt(str);
	check2 = HashStringToInt(str); 
	ASSERT_THAT(check1 == check2);
	
END_UNIT


UNIT(TestHashCreate)
	HashMap* hash;
	size_t capacity  = 9;
	hash = HashMap_Create( capacity , HashStringToInt, FindKey);		
	ASSERT_THAT(NULL != hash);
	HashMap_Destroy(&hash, NULL, NULL);
END_UNIT


UNIT(TestHashInsert)
	HashMap* hash;
	char key[] = "ABCDE";
	char value[] = "Ron Potashnik";
	size_t capacity  = 5;

	hash = HashMap_Create( capacity , HashStringToInt, FindKey);		
	ASSERT_THAT(NULL != hash);
	
	ASSERT_THAT(MAP_SUCCESS == HashMap_Insert(hash, key, value ));
	HashMap_Destroy(&hash, NULL, NULL);
	
END_UNIT
	

UNIT(TestHashInsertDuplicate)
	HashMap* hash;
	char key[] = "ABCDE";
	char value[] = "Ron Potashnik";
	size_t capacity  = 5;
	hash = HashMap_Create( capacity , HashStringToInt, FindKey);		
	ASSERT_THAT(NULL != hash);
	
	ASSERT_THAT(MAP_SUCCESS == HashMap_Insert(hash, key, value ));
	ASSERT_THAT(MAP_KEY_DUPLICATE_ERROR == HashMap_Insert(hash, key, value ));
	HashMap_Destroy(&hash, NULL, NULL);
	
END_UNIT

UNIT(TestHashInsertKeyNull)
	
	HashMap* hash;
	char key[] = "ABCDE";
	char value[] = "Ron Potashnik";
	size_t capacity  = 5;

	hash = HashMap_Create( capacity , HashStringToInt, FindKey);		
	ASSERT_THAT(NULL != hash);
	
	ASSERT_THAT(MAP_SUCCESS == HashMap_Insert(hash, key, value ));
	ASSERT_THAT(MAP_KEY_NULL_ERROR == HashMap_Insert(hash, NULL, value ));
	HashMap_Destroy(&hash, NULL, NULL);
	
END_UNIT
	
/**************************************************/
UNIT(TestHashInsertUninitilaizd)
	
	HashMap* hash;
	char key[] = "ABCDE";
	char value[] = "Ron Potashnik";
	size_t capacity  = 5;

	hash = HashMap_Create( capacity , HashStringToInt, FindKey);		
	ASSERT_THAT(NULL != hash);
	
	ASSERT_THAT(MAP_SUCCESS == HashMap_Insert(hash, key, value ));
	ASSERT_THAT(MAP_UNINITIALIZED_ERROR == HashMap_Insert(NULL, key, value ));
	HashMap_Destroy(&hash, NULL, NULL);
	
END_UNIT
/*******************************************************************/
UNIT(TestHashInsertAndSearchNullValue)
	
	HashMap* hash;
	char key[] = "ABCDE";
	void* pValue;
	char* value = NULL;
	size_t capacity  = 5;

	hash = HashMap_Create( capacity , HashStringToInt, FindKey);		
	ASSERT_THAT(NULL != hash);
	
	ASSERT_THAT(MAP_SUCCESS == HashMap_Insert(hash, key, value ));
	ASSERT_THAT(MAP_SUCCESS == HashMap_Find(hash, key, &pValue  ));
	ASSERT_THAT(NULL == pValue);
	ASSERT_THAT(MAP_UNINITIALIZED_ERROR == HashMap_Insert(NULL, key, value ));
	HashMap_Destroy(&hash, NULL, NULL);
	
END_UNIT
/************************************************************************************/
UNIT(TestHashInsertLotsOfTime)
	
	HashMap* hash;
	char* key1 = (char*)malloc(STRING_SIZE);
	char* key2 = (char*)malloc(STRING_SIZE);
	char* key3 = (char*)malloc(STRING_SIZE);
	char* key4 = (char*)malloc(STRING_SIZE);
	char* key5 = (char*)malloc(STRING_SIZE);
	char* key6 = (char*)malloc(STRING_SIZE);
	
	char* val1 = (char*)malloc(STRING_SIZE);
	char* val2 = (char*)malloc(STRING_SIZE);
	char* val3 = (char*)malloc(STRING_SIZE);
	char* val4 = (char*)malloc(STRING_SIZE);
	char* val5 = (char*)malloc(STRING_SIZE);
	char* val6 = (char*)malloc(STRING_SIZE);
	
	size_t capacity  = 100;


	strcpy(val1, "Alona");
	strcpy(val2, "Eyal");
	strcpy(val3, "Shany");
	strcpy(val4, "Berry");
	strcpy(val5, "Ron");
	strcpy(val6, "Noa");



	strcpy(key1, "ABCDsdsdsdsdasdsd");
	strcpy(key2, "EsdasdasdasdasdF");
	strcpy(key3, "GasdasdasdasdH");
	strcpy(key4, "AasdasdasdasdS");
	strcpy(key5, "SasdasdasdDDF");
	strcpy(key6, "AasdasdasdasdasAA");

	hash = HashMap_Create( capacity , HashStringToInt, FindKey);		
	ASSERT_THAT(NULL != hash);
	
	ASSERT_THAT(MAP_SUCCESS == HashMap_Insert(hash, key1, val1 ));

	ASSERT_THAT(MAP_KEY_DUPLICATE_ERROR == HashMap_Insert(hash, key1, val1 ));
	
	ASSERT_THAT(MAP_SUCCESS == HashMap_Insert(hash, key2, val2 ));
	ASSERT_THAT(MAP_SUCCESS == HashMap_Insert(hash, key3, val3 ));
	ASSERT_THAT(MAP_SUCCESS == HashMap_Insert(hash, key4, val4 ));
	ASSERT_THAT(MAP_SUCCESS == HashMap_Insert(hash, key5, val5 ));
	ASSERT_THAT(MAP_SUCCESS == HashMap_Insert(hash, key6, val6 ));



	HashMap_Destroy(&hash, KeyDestroy , ValDestroy );
	
END_UNIT
/*********************************************************************************/


UNIT(TestHashRemove)
	
	HashMap* hash;
	void* pTrashKey;
	void* pTrashValue;
	char* key1 = (char*)malloc(STRING_SIZE);
	char* key2 = (char*)malloc(STRING_SIZE);
	char* key3 = (char*)malloc(STRING_SIZE);
	char* key4 = (char*)malloc(STRING_SIZE);
	char* key5 = (char*)malloc(STRING_SIZE);
	char* key6 = (char*)malloc(STRING_SIZE);
	
	char* val1 = (char*)malloc(STRING_SIZE);
	char* val2 = (char*)malloc(STRING_SIZE);
	char* val3 = (char*)malloc(STRING_SIZE);
	char* val4 = (char*)malloc(STRING_SIZE);
	char* val5 = (char*)malloc(STRING_SIZE);
	char* val6 = (char*)malloc(STRING_SIZE);
		
	size_t capacity  = 5;


	strcpy(val1, "Alona");
	strcpy(val2, "Eyal");
	strcpy(val3, "Shany");
	strcpy(val4, "Berry");
	strcpy(val5, "Ron");
	strcpy(val6, "Noa");



	strcpy(key1, "ABCD");
	strcpy(key2, "EF");
	strcpy(key3, "GH");
	strcpy(key4, "AS");
	strcpy(key5, "SDDF");
	strcpy(key6, "AAA");
	hash = HashMap_Create( capacity , HashStringToInt, FindKey);		
	ASSERT_THAT(NULL != hash);
	
	ASSERT_THAT(MAP_SUCCESS == HashMap_Insert(hash, key1, val1 ));

	ASSERT_THAT(MAP_KEY_DUPLICATE_ERROR == HashMap_Insert(hash, key1, val1 ));
	
	ASSERT_THAT(MAP_SUCCESS == HashMap_Insert(hash, key2, val2 ));
	ASSERT_THAT(MAP_SUCCESS == HashMap_Insert(hash, key3, val3 ));
	ASSERT_THAT(MAP_SUCCESS == HashMap_Insert(hash, key4, val4 ));
	ASSERT_THAT(MAP_SUCCESS == HashMap_Insert(hash, key5, val5 ));
	ASSERT_THAT(MAP_SUCCESS == HashMap_Insert(hash, key6, val6 ));

	ASSERT_THAT(MAP_SUCCESS == HashMap_Remove(hash, key1, &pTrashKey, &pTrashValue));
	free(pTrashKey);
	free(pTrashValue);
	HashMap_Destroy(&hash, KeyDestroy , ValDestroy );
	
END_UNIT
/*******************************************************************************************/
UNIT(TestHashRemoveKeyNotFound)
	
	HashMap* hash;
	void* pTrashKey;
	void* pTrashValue;
	char* key1 = (char*)malloc(sizeof(char));
	
	char* val1 = (char*)malloc(sizeof(char));
	
	size_t capacity  = 5;


	strcpy(val1, "Alona");


	strcpy(key1, "ABCD");

	hash = HashMap_Create( capacity , HashStringToInt, FindKey);		
	ASSERT_THAT(NULL != hash);
	
	ASSERT_THAT(MAP_SUCCESS == HashMap_Insert(hash, key1, val1 ));

	ASSERT_THAT(MAP_KEY_DUPLICATE_ERROR == HashMap_Insert(hash, key1, val1 ));
	

	ASSERT_THAT(MAP_SUCCESS == HashMap_Remove(hash, key1, &pTrashKey, &pTrashValue));
	free(pTrashKey);
	free(pTrashValue);

	ASSERT_THAT( 0 == strcmp((char*)pTrashValue, val1));
	ASSERT_THAT( 0 == strcmp((char*)pTrashKey, key1));

	ASSERT_THAT(MAP_KEY_NOT_FOUND_ERROR == HashMap_Remove(hash, key1, &pTrashKey, &pTrashValue));
	HashMap_Destroy(&hash, KeyDestroy , ValDestroy );
	
END_UNIT	
/*****************************************************************/
UNIT(TestHashRemoveNullHash)
	
	HashMap* hash;
	void* pTrashKey;
	void* pTrashValue;
	char* key1 = (char*)malloc(STRING_SIZE);
	char* key2 = (char*)malloc(STRING_SIZE);
	char* key3 = (char*)malloc(STRING_SIZE);
	char* key4 = (char*)malloc(STRING_SIZE);
	char* key5 = (char*)malloc(STRING_SIZE);
	char* key6 = (char*)malloc(STRING_SIZE);
	
	char* val1 = (char*)malloc(STRING_SIZE);
	char* val2 = (char*)malloc(STRING_SIZE);
	char* val3 = (char*)malloc(STRING_SIZE);
	char* val4 = (char*)malloc(STRING_SIZE);
	char* val5 = (char*)malloc(STRING_SIZE);
	char* val6 = (char*)malloc(STRING_SIZE);
	
	size_t capacity  = 5;


	strcpy(val1, "Alona");
	strcpy(val2, "Eyal");
	strcpy(val3, "Shany");
	strcpy(val4, "Berry");
	strcpy(val5, "Ron");
	strcpy(val6, "Noa");



	strcpy(key1, "ABCD");
	strcpy(key2, "EF");
	strcpy(key3, "GH");
	strcpy(key4, "AS");
	strcpy(key5, "SDDF");
	strcpy(key6, "AAA");

	hash = HashMap_Create( capacity , HashStringToInt, FindKey);		
	ASSERT_THAT(NULL != hash);
	
	ASSERT_THAT(MAP_SUCCESS == HashMap_Insert(hash, key1, val1 ));

	ASSERT_THAT(MAP_KEY_DUPLICATE_ERROR == HashMap_Insert(hash, key1, val1 ));
	

	ASSERT_THAT(MAP_SUCCESS == HashMap_Remove(hash, key1, &pTrashKey, &pTrashValue));
	free(pTrashKey);
	free(pTrashValue);
	ASSERT_THAT(MAP_UNINITIALIZED_ERROR == HashMap_Remove(NULL, key2, &pTrashKey, &pTrashValue));
	

	HashMap_Destroy(&hash, KeyDestroy , ValDestroy );
	
END_UNIT	
/*************************************************************************/		
UNIT(TestHashRemoveLotsOfTime)
	
	HashMap* hash;
	void* pTrashKey;
	void* pTrashValue;
	char* key1 = (char*)malloc(STRING_SIZE);
	char* key2 = (char*)malloc(STRING_SIZE);
	char* key3 = (char*)malloc(STRING_SIZE);
	char* key4 = (char*)malloc(STRING_SIZE);
	char* key5 = (char*)malloc(STRING_SIZE);
	char* key6 = (char*)malloc(STRING_SIZE);
	
	char* val1 = (char*)malloc(STRING_SIZE);
	char* val2 = (char*)malloc(STRING_SIZE);
	char* val3 = (char*)malloc(STRING_SIZE);
	char* val4 = (char*)malloc(STRING_SIZE);
	char* val5 = (char*)malloc(STRING_SIZE);
	char* val6 = (char*)malloc(STRING_SIZE);
	
	size_t capacity  = 5;


	strcpy(val1, "Alona");
	strcpy(val2, "Eyal");
	strcpy(val3, "Shany");
	strcpy(val4, "Berry");
	strcpy(val5, "Ron");
	strcpy(val6, "Noa");



	strcpy(key1, "ABCD");
	strcpy(key2, "EF");
	strcpy(key3, "GH");
	strcpy(key4, "AS");
	strcpy(key5, "SDDF");
	strcpy(key6, "AAA");

	hash = HashMap_Create( capacity , HashStringToInt, FindKey);		
	ASSERT_THAT(NULL != hash);
	
	ASSERT_THAT(MAP_SUCCESS == HashMap_Insert(hash, key1, val1 ));
	ASSERT_THAT(MAP_SUCCESS == HashMap_Insert(hash, key2, val2 ));
	ASSERT_THAT(MAP_SUCCESS == HashMap_Insert(hash, key3, val3 ));
	ASSERT_THAT(MAP_SUCCESS == HashMap_Insert(hash, key4, val4 ));
	ASSERT_THAT(MAP_SUCCESS == HashMap_Insert(hash, key5, val5 ));
	ASSERT_THAT(MAP_SUCCESS == HashMap_Insert(hash, key6, val6 ));



	ASSERT_THAT(MAP_SUCCESS == HashMap_Remove(hash, key1, &pTrashKey, &pTrashValue));
	free(pTrashKey);
	free(pTrashValue);
	ASSERT_THAT(MAP_KEY_NOT_FOUND_ERROR == HashMap_Remove(hash, key1, &pTrashKey, &pTrashValue));
	ASSERT_THAT(MAP_SUCCESS == HashMap_Remove(hash, key2, &pTrashKey, &pTrashValue ));
	free(pTrashKey);
	free(pTrashValue);
	ASSERT_THAT(MAP_SUCCESS == HashMap_Remove(hash, key3, &pTrashKey, &pTrashValue ));
	free(pTrashKey);
	free(pTrashValue);

	ASSERT_THAT(MAP_SUCCESS == HashMap_Remove(hash, key4, &pTrashKey, &pTrashValue ));
	free(pTrashKey);
	free(pTrashValue);
	ASSERT_THAT(MAP_SUCCESS == HashMap_Remove(hash, key5, &pTrashKey, &pTrashValue ));
	free(pTrashKey);
	free(pTrashValue);
	ASSERT_THAT(MAP_SUCCESS == HashMap_Remove(hash, key6, &pTrashKey, &pTrashValue ));
	free(pTrashKey);
	free(pTrashValue);

	ASSERT_THAT(MAP_KEY_NOT_FOUND_ERROR == HashMap_Remove(hash, "SDSsdsdD", &pTrashKey, &pTrashValue ));



	HashMap_Destroy(&hash, KeyDestroy , ValDestroy );
	HashMap_Destroy(&hash, KeyDestroy , ValDestroy );
	
END_UNIT

/*************************************************************/

UNIT(TestHashFind)
	
	HashMap* hash;
	void* pTrashValue;
	char* key1 = (char*)malloc(STRING_SIZE);
	char* key2 = (char*)malloc(STRING_SIZE);
	char* key3 = (char*)malloc(STRING_SIZE);
	char* key4 = (char*)malloc(STRING_SIZE);
	char* key5 = (char*)malloc(STRING_SIZE);
	char* key6 = (char*)malloc(STRING_SIZE);
	
	char* val1 = (char*)malloc(STRING_SIZE);
	char* val2 = (char*)malloc(STRING_SIZE);
	char* val3 = (char*)malloc(STRING_SIZE);
	char* val4 = (char*)malloc(STRING_SIZE);
	char* val5 = (char*)malloc(STRING_SIZE);
	char* val6 = (char*)malloc(STRING_SIZE);
	
	size_t capacity  = 5;


	strcpy(val1, "Alona");
	strcpy(val2, "Eyal");
	strcpy(val3, "Shany");
	strcpy(val4, "Berry");
	strcpy(val5, "Ron");
	strcpy(val6, "Noa");



	strcpy(key1, "ABCD");
	strcpy(key2, "EF");
	strcpy(key3, "GH");
	strcpy(key4, "AS");
	strcpy(key5, "SDDF");
	strcpy(key6, "AAA");

	hash = HashMap_Create( capacity , HashStringToInt, FindKey);		
	ASSERT_THAT(NULL != hash);
	
	ASSERT_THAT(MAP_SUCCESS == HashMap_Insert(hash, key1, val1 ));
	ASSERT_THAT(MAP_SUCCESS == HashMap_Insert(hash, key2, val2 ));
	ASSERT_THAT(MAP_SUCCESS == HashMap_Insert(hash, key3, val3 ));
	ASSERT_THAT(MAP_SUCCESS == HashMap_Insert(hash, key4, val4 ));
	ASSERT_THAT(MAP_SUCCESS == HashMap_Insert(hash, key5, val5 ));
	ASSERT_THAT(MAP_SUCCESS == HashMap_Insert(hash, key6, val6 ));

	ASSERT_THAT(MAP_SUCCESS == HashMap_Find( hash, key1, &pTrashValue));
	ASSERT_THAT(0 == strcmp((char*)pTrashValue, val1));



	HashMap_Destroy(&hash, KeyDestroy , ValDestroy );
	HashMap_Destroy(&hash, KeyDestroy , ValDestroy );
	
END_UNIT

/***********************************************************************/

UNIT(TestHashFindKeyNotFound)
	
	HashMap* hash;
	void* pTrashValue;
	char* key1 = (char*)malloc(STRING_SIZE);
	char* key2 = (char*)malloc(STRING_SIZE);
	char* key3 = (char*)malloc(STRING_SIZE);
	char* key4 = (char*)malloc(STRING_SIZE);
	char* key5 = (char*)malloc(STRING_SIZE);
	char* key6 = (char*)malloc(STRING_SIZE);
	
	char* val1 = (char*)malloc(STRING_SIZE);
	char* val2 = (char*)malloc(STRING_SIZE);
	char* val3 = (char*)malloc(STRING_SIZE);
	char* val4 = (char*)malloc(STRING_SIZE);
	char* val5 = (char*)malloc(STRING_SIZE);
	char* val6 = (char*)malloc(STRING_SIZE);
	
	size_t capacity  = 5;


	strcpy(val1, "Alona");
	strcpy(val2, "Eyal");
	strcpy(val3, "Shany");
	strcpy(val4, "Berry");
	strcpy(val5, "Ron");
	strcpy(val6, "Noa");



	strcpy(key1, "ABCD");
	strcpy(key2, "EF");
	strcpy(key3, "GH");
	strcpy(key4, "AS");
	strcpy(key5, "SDDF");
	strcpy(key6, "AAA");

	hash = HashMap_Create( capacity , HashStringToInt, FindKey);		
	ASSERT_THAT(NULL != hash);
	
	ASSERT_THAT(MAP_SUCCESS == HashMap_Insert(hash, key1, val1 ));
	ASSERT_THAT(MAP_SUCCESS == HashMap_Insert(hash, key2, val2 ));
	ASSERT_THAT(MAP_SUCCESS == HashMap_Insert(hash, key3, val3 ));
	ASSERT_THAT(MAP_SUCCESS == HashMap_Insert(hash, key4, val4 ));
	ASSERT_THAT(MAP_SUCCESS == HashMap_Insert(hash, key5, val5 ));
	ASSERT_THAT(MAP_SUCCESS == HashMap_Insert(hash, key6, val6 ));

	ASSERT_THAT(MAP_SUCCESS == HashMap_Find( hash, key1, &pTrashValue));
	ASSERT_THAT(0 == strcmp((char*)pTrashValue, val1));
	ASSERT_THAT(MAP_KEY_NOT_FOUND_ERROR == HashMap_Find( hash, "SDSDSD", &pTrashValue));


	HashMap_Destroy(&hash, KeyDestroy , ValDestroy );
	HashMap_Destroy(&hash, KeyDestroy , ValDestroy );
	
END_UNIT
/******************************************************************/


UNIT(TestHashFindUnithilizd)
	
	HashMap* hash;
	void* pTrashValue;
	char* key1 = (char*)malloc(STRING_SIZE);
	char* key2 = (char*)malloc(STRING_SIZE);
	char* key3 = (char*)malloc(STRING_SIZE);
	char* key4 = (char*)malloc(STRING_SIZE);
	char* key5 = (char*)malloc(STRING_SIZE);
	char* key6 = (char*)malloc(STRING_SIZE);
	
	char* val1 = (char*)malloc(STRING_SIZE);
	char* val2 = (char*)malloc(STRING_SIZE);
	char* val3 = (char*)malloc(STRING_SIZE);
	char* val4 = (char*)malloc(STRING_SIZE);
	char* val5 = (char*)malloc(STRING_SIZE);
	char* val6 = (char*)malloc(STRING_SIZE);
	size_t capacity  = 5;


	strcpy(val1, "Alona");
	strcpy(val2, "Eyal");
	strcpy(val3, "Shany");
	strcpy(val4, "Berry");
	strcpy(val5, "Ron");
	strcpy(val6, "Noa");



	strcpy(key1, "ABCD");
	strcpy(key2, "EF");
	strcpy(key3, "GH");
	strcpy(key4, "AS");
	strcpy(key5, "SDDF");
	strcpy(key6, "AAA");

	hash = HashMap_Create( capacity , HashStringToInt, FindKey);		
	ASSERT_THAT(NULL != hash);
	
	ASSERT_THAT(MAP_SUCCESS == HashMap_Insert(hash, key1, val1 ));
	ASSERT_THAT(MAP_SUCCESS == HashMap_Insert(hash, key2, val2 ));
	ASSERT_THAT(MAP_SUCCESS == HashMap_Insert(hash, key3, val3 ));
	ASSERT_THAT(MAP_SUCCESS == HashMap_Insert(hash, key4, val4 ));
	ASSERT_THAT(MAP_SUCCESS == HashMap_Insert(hash, key5, val5 ));
	ASSERT_THAT(MAP_SUCCESS == HashMap_Insert(hash, key6, val6 ));

	ASSERT_THAT(MAP_SUCCESS == HashMap_Find( hash, key1, &pTrashValue));
	ASSERT_THAT(0 == strcmp((char*)pTrashValue, val1));
	ASSERT_THAT(MAP_UNINITIALIZED_ERROR == HashMap_Find( NULL, "SDSDSD", &pTrashValue));


	HashMap_Destroy(&hash, KeyDestroy , ValDestroy );
	HashMap_Destroy(&hash, KeyDestroy , ValDestroy );
	
END_UNIT
/*************************************************************************************************/
UNIT(TestHashSize)
	
	HashMap* hash;
	void* pTrashValue;
	void* pTrashKey;
	char* key1 = (char*)malloc(STRING_SIZE);
	char* key2 = (char*)malloc(STRING_SIZE);
	char* key3 = (char*)malloc(STRING_SIZE);
	char* key4 = (char*)malloc(STRING_SIZE);
	char* key5 = (char*)malloc(STRING_SIZE);
	char* key6 = (char*)malloc(STRING_SIZE);
	
	char* val1 = (char*)malloc(STRING_SIZE);
	char* val2 = (char*)malloc(STRING_SIZE);
	char* val3 = (char*)malloc(STRING_SIZE);
	char* val4 = (char*)malloc(STRING_SIZE);
	char* val5 = (char*)malloc(STRING_SIZE);
	char* val6 = (char*)malloc(STRING_SIZE);
	
	size_t capacity  = 5;


	strcpy(val1, "Alona");
	strcpy(val2, "Eyal");
	strcpy(val3, "Shany");
	strcpy(val4, "Berry");
	strcpy(val5, "Ron");
	strcpy(val6, "Noa");



	strcpy(key1, "ABCD");
	strcpy(key2, "EF");
	strcpy(key3, "GH");
	strcpy(key4, "AS");
	strcpy(key5, "SDDF");
	strcpy(key6, "AAA");

	hash = HashMap_Create( capacity , HashStringToInt, FindKey);		
	ASSERT_THAT(NULL != hash);
	
	ASSERT_THAT(MAP_SUCCESS == HashMap_Insert(hash, key1, val1 ));
	ASSERT_THAT(MAP_SUCCESS == HashMap_Insert(hash, key2, val2 ));
	ASSERT_THAT(MAP_SUCCESS == HashMap_Insert(hash, key3, val3 ));
	ASSERT_THAT(MAP_SUCCESS == HashMap_Insert(hash, key4, val4 ));
	ASSERT_THAT(MAP_SUCCESS == HashMap_Insert(hash, key5, val5 ));
	ASSERT_THAT(MAP_SUCCESS == HashMap_Insert(hash, key6, val6 ));

	ASSERT_THAT(6 == HashMap_Size( hash));

	ASSERT_THAT(MAP_SUCCESS == HashMap_Remove(hash, key6, &pTrashKey, &pTrashValue ));
	free(pTrashKey);
	free(pTrashValue);
	ASSERT_THAT(5 == HashMap_Size( hash));
	
	ASSERT_THAT(MAP_SUCCESS == HashMap_Remove(hash, key5, &pTrashKey, &pTrashValue ));
	free(pTrashKey);
	free(pTrashValue);
	
	ASSERT_THAT(MAP_SUCCESS == HashMap_Remove(hash, key4, &pTrashKey, &pTrashValue ));
	free(pTrashKey);
	free(pTrashValue);
	ASSERT_THAT(MAP_SUCCESS == HashMap_Remove(hash, key3, &pTrashKey, &pTrashValue ));
	free(pTrashKey);
	free(pTrashValue);	
	ASSERT_THAT(MAP_SUCCESS == HashMap_Remove(hash, key2, &pTrashKey, &pTrashValue ));
	free(pTrashKey);
	free(pTrashValue);	
	ASSERT_THAT(MAP_SUCCESS == HashMap_Remove(hash, key1, &pTrashKey, &pTrashValue ));
	free(pTrashKey);
	free(pTrashValue);
	ASSERT_THAT(0 == HashMap_Size( hash));
	ASSERT_THAT(MAP_KEY_NOT_FOUND_ERROR == HashMap_Remove(hash, key1, &pTrashKey, &pTrashValue ));
	ASSERT_THAT(0 == HashMap_Size( hash));	

	HashMap_Destroy(&hash, KeyDestroy , ValDestroy );
	HashMap_Destroy(&hash, KeyDestroy , ValDestroy );
	
END_UNIT
/****************************************************************************************************/

UNIT(TestForEach)
	
	HashMap* hash;
	void* pValue;
	size_t size;
	char* key1 = (char*)malloc(STRING_SIZE);
	char* key2 = (char*)malloc(STRING_SIZE);
	char* key3 = (char*)malloc(STRING_SIZE);
	char* key4 = (char*)malloc(STRING_SIZE);
	char* key5 = (char*)malloc(STRING_SIZE);
	char* key6 = (char*)malloc(STRING_SIZE);
	
	char* val1 = (char*)malloc(STRING_SIZE);
	char* val2 = (char*)malloc(STRING_SIZE);
	char* val3 = (char*)malloc(STRING_SIZE);
	char* val4 = (char*)malloc(STRING_SIZE);
	char* val5 = (char*)malloc(STRING_SIZE);
	char* val6 = (char*)malloc(STRING_SIZE);
	size_t capacity  = 6;


	strcpy(val1, "Alona");
	strcpy(val2, "Eyal");
	strcpy(val3, "Shany");
	strcpy(val4, "Berry");
	strcpy(val5, "Ron");
	strcpy(val6, "Noa");



	strcpy(key1, "ABCD");
	strcpy(key2, "EF");
	strcpy(key3, "GH");
	strcpy(key4, "AS");
	strcpy(key5, "SDDF");
	strcpy(key6, "AAA");

	hash = HashMap_Create( capacity , HashStringToInt, FindKey);		
	ASSERT_THAT(NULL != hash);
	
	ASSERT_THAT(MAP_SUCCESS == HashMap_Insert(hash, key1, val1 ));
	ASSERT_THAT(MAP_SUCCESS == HashMap_Insert(hash, key2, val2 ));
	ASSERT_THAT(MAP_SUCCESS == HashMap_Insert(hash, key3, val3 ));
	ASSERT_THAT(MAP_SUCCESS == HashMap_Insert(hash, key4, val4 ));
	ASSERT_THAT(MAP_SUCCESS == HashMap_Insert(hash, key5, val5 ));
	ASSERT_THAT(MAP_SUCCESS == HashMap_Insert(hash, key6, val6 ));
	printf("THE HASH Print\n");
	ASSERT_THAT(0 != (size = HashMap_ForEach(hash, MyPrint, "SDSD")));
	putchar('\n');
	fflush(stdout);
	
	ASSERT_THAT(HashMap_Find(hash, key1, &pValue) == MAP_SUCCESS);
	ASSERT_THAT(HashMap_Find(hash, key2, &pValue) == MAP_SUCCESS);		 
	ASSERT_THAT(HashMap_Find(hash, key3, &pValue) == MAP_SUCCESS);
	ASSERT_THAT(HashMap_Find(hash, key4, &pValue) == MAP_SUCCESS);
	ASSERT_THAT(HashMap_Find(hash, key5, &pValue) == MAP_SUCCESS);
	ASSERT_THAT(HashMap_Find(hash, key6, &pValue) == MAP_SUCCESS);
	
	

	HashMap_Destroy(&hash, KeyDestroy , ValDestroy );
	HashMap_Destroy(&hash, KeyDestroy , ValDestroy );
	
END_UNIT


/***********************************************************************/


UNIT(TestHashReHash)
	
	HashMap* hash;
	void* pTrashValue;
	void* pTrashKey;
	void* pValue;
	size_t size;
	char* key1 = (char*)malloc(STRING_SIZE);
	char* key2 = (char*)malloc(STRING_SIZE);
	char* key3 = (char*)malloc(STRING_SIZE);
	char* key4 = (char*)malloc(STRING_SIZE);
	char* key5 = (char*)malloc(STRING_SIZE);
	char* key6 = (char*)malloc(STRING_SIZE);
	
	char* val1 = (char*)malloc(STRING_SIZE);
	char* val2 = (char*)malloc(STRING_SIZE);
	char* val3 = (char*)malloc(STRING_SIZE);
	char* val4 = (char*)malloc(STRING_SIZE);
	char* val5 = (char*)malloc(STRING_SIZE);
	char* val6 = (char*)malloc(STRING_SIZE);

	size_t capacity  = 6;


	strcpy(val1, "Alona");
	strcpy(val2, "Eyal");
	strcpy(val3, "Shany");
	strcpy(val4, "Berry");
	strcpy(val5, "Ron");
	strcpy(val6, "Noa");



	strcpy(key1, "ABsadasdsaCD");
	strcpy(key2, "EasdasdasF");
	strcpy(key3, "GasdashfdhgdsadH");
	strcpy(key4, "AasdasdsadS");
	strcpy(key5, "SasdasdasDDF");
	strcpy(key6, "AdgfhgjghjAA");

	hash = HashMap_Create( capacity , HashStringToInt, FindKey);		
	ASSERT_THAT(NULL != hash);
	
	ASSERT_THAT(MAP_SUCCESS == HashMap_Insert(hash, key1, val1 ));
	ASSERT_THAT(MAP_SUCCESS == HashMap_Insert(hash, key2, val2 ));
	ASSERT_THAT(MAP_SUCCESS == HashMap_Insert(hash, key3, val3 ));
	ASSERT_THAT(MAP_SUCCESS == HashMap_Insert(hash, key4, val4 ));
	ASSERT_THAT(MAP_SUCCESS == HashMap_Insert(hash, key5, val5 ));
	ASSERT_THAT(MAP_SUCCESS == HashMap_Insert(hash, key6, val6 ));
	ASSERT_THAT(6 == HashMap_Size( hash));

	printf("THE HASH BEFORE RE-HASHING\n");
	ASSERT_THAT(0 != (size = HashMap_ForEach(hash, MyPrint, "SDSD")));	
	putchar('\n');
	fflush(stdout);
	
	ASSERT_THAT(MAP_SUCCESS == HashMap_Rehash(hash, 20 ));
	ASSERT_THAT(6 == HashMap_Size(hash));
	printf("THE HASH AFTER RE-HASHING TO 20\n");
	ASSERT_THAT(0 != (size = HashMap_ForEach(hash, MyPrint, "SDSD")));
	ASSERT_THAT(6 == HashMap_Size( hash));
	
	
	putchar('\n');
	ASSERT_THAT(MAP_SUCCESS == HashMap_Rehash(hash, 100 ));
	ASSERT_THAT(6 == HashMap_Size(hash));
	ASSERT_THAT(HashMap_Find(hash, key1, &pValue) == MAP_SUCCESS);
	printf("THE HASH AFTER RE-HASHING TO 100\n");


	ASSERT_THAT(0 != (size = HashMap_ForEach(hash, MyPrint, "SDSD")));






	ASSERT_THAT(6 == HashMap_Size( hash));
	
	putchar('\n');
	ASSERT_THAT(MAP_SUCCESS == HashMap_Rehash(hash, 2 ));
	ASSERT_THAT(6 == HashMap_Size(hash));
	ASSERT_THAT(HashMap_Find(hash, key5, &pValue) == MAP_SUCCESS);
	printf("THE HASH AFTER RE-HASHING TO 2\n");
	ASSERT_THAT(0 != (size = HashMap_ForEach(hash, MyPrint, "SDSD")));
	ASSERT_THAT(6 == HashMap_Size( hash));
	ASSERT_THAT(MAP_SUCCESS == HashMap_Remove(hash, key4, &pTrashKey, &pTrashValue ));
	free(pTrashKey);
	free(pTrashValue);	
	ASSERT_THAT(5 == HashMap_Size( hash));


	putchar('\n');	
	printf("THE HASH AFTER REMOVE\n");
	ASSERT_THAT(0 != (size = HashMap_ForEach(hash, MyPrint, "SDSD")));

	HashMap_Destroy(&hash, KeyDestroy , ValDestroy );
	HashMap_Destroy(&hash, KeyDestroy , ValDestroy );
	
END_UNIT
/*******************************************************************/
UNIT(TestHashReHashSizeZero)
	
	HashMap* hash;
	char* key1 = (char*)malloc(STRING_SIZE);
	char* key2 = (char*)malloc(STRING_SIZE);
	char* key3 = (char*)malloc(STRING_SIZE);
	char* key4 = (char*)malloc(STRING_SIZE);
	char* key5 = (char*)malloc(STRING_SIZE);
	char* key6 = (char*)malloc(STRING_SIZE);
	
	char* val1 = (char*)malloc(STRING_SIZE);
	char* val2 = (char*)malloc(STRING_SIZE);
	char* val3 = (char*)malloc(STRING_SIZE);
	char* val4 = (char*)malloc(STRING_SIZE);
	char* val5 = (char*)malloc(STRING_SIZE);
	char* val6 = (char*)malloc(STRING_SIZE);

	size_t capacity  = 500;


	strcpy(val1, "Alona");
	strcpy(val2, "Eyal");
	strcpy(val3, "Shany");
	strcpy(val4, "Berry");
	strcpy(val5, "Ron");
	strcpy(val6, "Noa");



	strcpy(key1, "ABsadasdsaCD");
	strcpy(key2, "EasdasdasF");
	strcpy(key3, "GasdashfdhgdsadH");
	strcpy(key4, "AasdasdsadS");
	strcpy(key5, "SasdasdasDDF");
	strcpy(key6, "AdgfhgjghjAA");


	hash = HashMap_Create( capacity , HashStringToInt, FindKey);		
	ASSERT_THAT(NULL != hash);
	
	ASSERT_THAT(MAP_SUCCESS == HashMap_Insert(hash, key1, val1 ));
	ASSERT_THAT(MAP_SUCCESS == HashMap_Insert(hash, key2, val2 ));
	ASSERT_THAT(MAP_SUCCESS == HashMap_Insert(hash, key3, val3 ));
	ASSERT_THAT(MAP_SUCCESS == HashMap_Insert(hash, key4, val4 ));
	ASSERT_THAT(MAP_SUCCESS == HashMap_Insert(hash, key5, val5 ));
	ASSERT_THAT(MAP_SUCCESS == HashMap_Insert(hash, key6, val6 ));

	ASSERT_THAT(MAP_ALLOCATION_ERROR == HashMap_Rehash(hash, 0));
	HashMap_Destroy(&hash, KeyDestroy , ValDestroy );
	
END_UNIT

/*************************************************************************/

UNIT(TestForEachCase2)
	
	HashMap* hash;
	size_t size;
	char* key1 = (char*)malloc(STRING_SIZE);
	char* key2 = (char*)malloc(STRING_SIZE);
	char* key3 = (char*)malloc(STRING_SIZE);
	char* key4 = (char*)malloc(STRING_SIZE);
	char* key5 = (char*)malloc(STRING_SIZE);
	char* key6 = (char*)malloc(STRING_SIZE);
	
	char* val1 = (char*)malloc(STRING_SIZE);
	char* val2 = (char*)malloc(STRING_SIZE);
	char* val3 = (char*)malloc(STRING_SIZE);
	char* val4 = (char*)malloc(STRING_SIZE);
	char* val5 = (char*)malloc(STRING_SIZE);
	char* val6 = (char*)malloc(STRING_SIZE);
	size_t capacity  = 202;

	strcpy(val1, "Eyadasdsl");
	strcpy(val2, "Eyal");
	strcpy(val3, "Shany");
	strcpy(val4, "Berry");
	strcpy(val5, "Ron");
	strcpy(val6, "Noa");



	strcpy(key1, "ABCD");
	strcpy(key2, "EF");
	strcpy(key3, "GH");
	strcpy(key4, "AS");
	strcpy(key5, "SDDF");
	strcpy(key6, "AAA");

	hash = HashMap_Create( capacity , HashStringToInt, FindKey);		
	ASSERT_THAT(NULL != hash);
	
	ASSERT_THAT(MAP_SUCCESS == HashMap_Insert(hash, key1, val1 ));
	ASSERT_THAT(MAP_SUCCESS == HashMap_Insert(hash, key2, val2 ));
	ASSERT_THAT(MAP_SUCCESS == HashMap_Insert(hash, key3, val3 ));
	ASSERT_THAT(MAP_SUCCESS == HashMap_Insert(hash, key4, val4 ));
	ASSERT_THAT(MAP_SUCCESS == HashMap_Insert(hash, key5, val5 ));
	ASSERT_THAT(MAP_SUCCESS == HashMap_Insert(hash, key6, val6 ));
	
	size = HashMap_ForEach(hash, MyKeyAndValueAction, key6);
	ASSERT_THAT(0 != size);
	printf("\nTHE IVOKED UNTIL FOR EACH FIND %s = %lu\n",key6, size );

	size = HashMap_ForEach(hash, MyKeyAndValueAction, key2);
	ASSERT_THAT(0 != size);
	printf("\nTHE IVOKED UNTIL FOR EACH FIND %s = %lu\n",key1, size );

	size = HashMap_ForEach(hash, MyKeyAndValueAction, key3);
	ASSERT_THAT(0 != size);
	printf("\nTHE IVOKED UNTIL FOR EACH FIND %s = %lu\n",key3, size );
	
	size = HashMap_ForEach(hash, MyKeyAndValueAction, key1);
	ASSERT_THAT(0 != size);
	printf("\nTHE IVOKED UNTIL FOR EACH FIND %s = %lu\n",key1, size );
	
	
	size = HashMap_ForEach(hash, MyKeyAndValueAction, key5);
	ASSERT_THAT(0 != size);
	printf("\nTHE IVOKED UNTIL FOR EACH FIND %s = %lu\n",key5, size );
	
	
	
	size = HashMap_ForEach(hash, MyKeyAndValueAction, "SDSDFFGGH");
	ASSERT_THAT(0 != size);
	printf("\nTHE IVOKED UNTIL FOR EACH SEARCH FOR NON KEY IN THE HASH = %lu\n", size );
	HashMap_Destroy(&hash, KeyDestroy , ValDestroy );
	HashMap_Destroy(&hash, KeyDestroy , ValDestroy );
	
END_UNIT

/********************************************************************************************/

UNIT(TestComplex)
	
	HashMap* hash;
	size_t size;
	char* key1 = (char*)malloc(STRING_SIZE);
	char* key2 = (char*)malloc(STRING_SIZE);
	char* key3 = (char*)malloc(STRING_SIZE);
	char* key4 = (char*)malloc(STRING_SIZE);
	char* key5 = (char*)malloc(STRING_SIZE);
	char* key6 = (char*)malloc(STRING_SIZE);
	char* key7 = (char*)malloc(STRING_SIZE);
	char* key8 = (char*)malloc(STRING_SIZE);
	char* key9 = (char*)malloc(STRING_SIZE);
	char* key10 = (char*)malloc(STRING_SIZE);
	char* key11 = (char*)malloc(STRING_SIZE);
	char* key12 = (char*)malloc(STRING_SIZE);
	
	
	
	char* val1 = (char*)malloc(STRING_SIZE);
	char* val2 = (char*)malloc(STRING_SIZE);
	char* val3 = (char*)malloc(STRING_SIZE);
	char* val4 = (char*)malloc(STRING_SIZE);
	char* val5 = (char*)malloc(STRING_SIZE);
	char* val6 = (char*)malloc(STRING_SIZE);
	char* val7 = (char*)malloc(STRING_SIZE);
	char* val8 = (char*)malloc(STRING_SIZE);
	char* val9 = (char*)malloc(STRING_SIZE);
	char* val10 = (char*)malloc(STRING_SIZE);
	char* val11 = (char*)malloc(STRING_SIZE);
	char* val12 = (char*)malloc(STRING_SIZE);

	size_t capacity  = 100;


	strcpy(val1, "Alona");
	strcpy(val2, "Eyal");
	strcpy(val3, "Shany");
	strcpy(val4, "Golan");
	strcpy(val5, "Ron");
	strcpy(val6, "Noa");
	strcpy(val7, "Jhon");
	strcpy(val8, "Lenon");
	strcpy(val9, "Bob");
	strcpy(val10, "Dylan");
	strcpy(val11, "Eyal");
	strcpy(val12, "Golan");



	strcpy(key1, "ABsadasdsadasdCD");
	strcpy(key2, "gjghjghjkhgkEF");
	strcpy(key3, "GxvvccccrtyH");
	strcpy(key4, "Auiii76fgfS");
	strcpy(key5, "SD23423rfsdDF");
	strcpy(key6, "AAAvcxvxc3");
	strcpy(key7, "ABdgtfi9to43xnCD");
	strcpy(key8, "Edsgfdghfdyhur5ty764F");
	strcpy(key9, "GHetrftrfET");
	strcpy(key10, "ASsadasdasdsad");
	strcpy(key11, "SD%^^&$^DF");
	strcpy(key12, "AAsadadas#A");



	hash = HashMap_Create( capacity , HashStringToInt, FindKey);		
	ASSERT_THAT(NULL != hash);
	
	ASSERT_THAT(MAP_SUCCESS == HashMap_Insert(hash, key1, val1 ));
	ASSERT_THAT(MAP_SUCCESS == HashMap_Insert(hash, key2, val2 ));
	ASSERT_THAT(MAP_SUCCESS == HashMap_Insert(hash, key3, val3 ));
	ASSERT_THAT(MAP_SUCCESS == HashMap_Insert(hash, key4, val4 ));
	ASSERT_THAT(MAP_SUCCESS == HashMap_Insert(hash, key5, val5 ));
	ASSERT_THAT(MAP_SUCCESS == HashMap_Insert(hash, key6, val6 ));
	ASSERT_THAT(MAP_SUCCESS == HashMap_Insert(hash, key7, val7 ));
	ASSERT_THAT(MAP_SUCCESS == HashMap_Insert(hash, key8, val8 ));
	ASSERT_THAT(MAP_SUCCESS == HashMap_Insert(hash, key9, val9 ));
	ASSERT_THAT(MAP_SUCCESS == HashMap_Insert(hash, key10, val10 ));
	ASSERT_THAT(MAP_SUCCESS == HashMap_Insert(hash, key11, val11 ));
	ASSERT_THAT(MAP_SUCCESS == HashMap_Insert(hash, key12, val12 ));


	
	size = HashMap_ForEach(hash, MyKeyAndValueAction, key6);
	ASSERT_THAT(0 != size);
	printf("\nTHE IVOKED UNTIL FOR EACH FIND %s = %lu\n",key6, size );

	size = HashMap_ForEach(hash, MyKeyAndValueAction, key2);
	ASSERT_THAT(0 != size);
	printf("\nTHE IVOKED UNTIL FOR EACH FIND %s = %lu\n",key1, size );

	size = HashMap_ForEach(hash, MyKeyAndValueAction, key3);
	ASSERT_THAT(0 != size);
	printf("\nTHE IVOKED UNTIL FOR EACH FIND %s = %lu\n",key3, size );
	
	size = HashMap_ForEach(hash, MyKeyAndValueAction, key1);
	ASSERT_THAT(0 != size);
	printf("\nTHE IVOKED UNTIL FOR EACH FIND %s = %lu\n",key1, size );
	
	
	size = HashMap_ForEach(hash, MyKeyAndValueAction, key5);
	ASSERT_THAT(0 != size);
	printf("\nTHE IVOKED UNTIL FOR EACH FIND %s = %lu\n",key5, size );
	
	
	
	size = HashMap_ForEach(hash, MyKeyAndValueAction, "SDSDFFGGH");
	ASSERT_THAT(0 != size);
	printf("\nTHE IVOKED UNTIL FOR EACH SEARCH FOR NON KEY IN THE HASH = %lu\n", size );
	
	
	printf("THE HASH BEFORE RE-HASHING\n");
	ASSERT_THAT(0 != (size = HashMap_ForEach(hash, MyPrint, "SDSD")));
	
	
	
	ASSERT_THAT(MAP_SUCCESS == HashMap_Rehash(hash, 20 ));
	ASSERT_THAT(12 == HashMap_Size(hash));
	printf("THE HASH AFTER RE-HASHING TO 20\n");
	ASSERT_THAT(0 != (size = HashMap_ForEach(hash, MyPrint, "SDSD")));
	ASSERT_THAT(12 == HashMap_Size( hash));
	
	
	HashMap_Destroy(&hash, KeyDestroy , ValDestroy );
	HashMap_Destroy(&hash, KeyDestroy , ValDestroy );
	
END_UNIT












TEST_SUITE(Ron test)
	TEST(TestHashFunction)
	TEST(TestHashCreate)
	TEST(TestHashInsert)
	TEST(TestHashInsertDuplicate)
	TEST(TestHashInsertKeyNull)
	TEST(TestHashInsertUninitilaizd)
	TEST(TestHashInsertLotsOfTime)
	TEST(TestHashRemove)
	TEST(TestHashRemoveKeyNotFound)
	TEST(TestHashInsertKeyNull)	
	TEST(TestHashRemoveLotsOfTime)
	TEST(TestHashFind)
	TEST(TestHashFindKeyNotFound)
	TEST(TestHashFindUnithilizd)
	TEST(TestHashSize)
	TEST(TestForEach)	
	TEST(TestHashReHash)
	TEST(TestHashReHashSizeZero)
	TEST(TestForEachCase2)
	TEST(TestComplex)
	TEST(TestHashInsertAndSearchNullValue)
END_SUITE	
	

	
