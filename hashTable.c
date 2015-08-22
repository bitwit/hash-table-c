#include <stdlib.h>
#include <string.h>
#include "hashTable.h"

/**
 * @brief Hashing function for the hash table implementation. Currently uses division method
 * @param hashTable - current hash table 
 * @param key - key to lookup the value by
 * @return index in our items array where we can find the value
 */
int hashTableGetHash(table *hashTable, char *key)
{
	int hash = 0;
	unsigned char *k = (unsigned char *)key;
	while(*key != '\0') {  // Iterate over each character of the string
		hash = *key + (hash << 2); // Set the new hash as the char's ascii value + (2 * the previous hash)
		key++;
	}
	return hash % hashTable->size; //return an index within the bounds of our hash table size
}

/**
 * @brief Creates a new hash table with a few safety checks for size and enough memory space
 * @param size
 * @return the new hash table || NULL if there is an issue allocating the table
 */
table *hashTableCreate(int size){
	printf("Creating table of size: %d\n", size);
	
	table *newTable;
	
	if (size < 1){
		return NULL;
	}

    if ((newTable = malloc(sizeof(table))) == NULL) {
        return NULL;
    }

    newTable->size = size;
    if ((newTable->items = malloc(sizeof(item *) * size)) == NULL) {
        return NULL;
    }

    for(int i = 0; i < size; i++) { 
		newTable->items[i] = NULL;	
	}

    return newTable;
}

/**
 * @brief Traverses the hashtable and deallocates all items then deallocates self
 * @param hashTable to be deallocated from memory
 */
void hashTableDelete(table *hashTable)
{
    int i;
    item *theItem, *temp;

    if (hashTable == NULL) return;

    for(int i = 0; i < hashTable->size; i++) {
        theItem = hashTable->items[i];
        while(theItem != NULL) {
            temp = theItem;
            theItem = theItem->next;
            free(temp->value);
            free(temp);
        }
    }
    free(hashTable->items);
    free(hashTable);
}

/* 
 * String type management 
 * */
void hashTablePutString(table *hashTable, char *key, char *value) {
	int index = hashTableGetHash(hashTable, key);
	printf("The index: %d\n", index);
	if(!hashTable->items[index]) {
		hashTable->items[index] = malloc(sizeof(item));
	}
	hashTable->items[index]->value = strdup(value);  // allocate memory and copy string to item->value
}

char *hashTableGetString(table *hashTable, char *key) {
	int index = hashTableGetHash(hashTable, key);
	return hashTable->items[index]->value;
}

/*
 *  Integer type management
 * */
void hashTablePutInteger(table *hashTable, char *key, int value) {
	int index = hashTableGetHash(hashTable, key);
	printf("The index: %d\n", index);
	if(!hashTable->items[index]) {
		hashTable->items[index] = malloc(sizeof(item));
	}
	hashTable->items[index]->value = malloc(sizeof(int *));
	memcpy(hashTable->items[index]->value, &value, sizeof(int));
}

int hashTableGetInteger(table *hashTable, char *key) {
	int index = hashTableGetHash(hashTable, key);
	int *value = hashTable->items[index]->value;
	return *value;
}
