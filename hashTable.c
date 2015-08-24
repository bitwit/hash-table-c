#include <stdlib.h>
#include <string.h>
#include "hashTable.h"

#define FNV_OFFSET_BASIS 2166136261
#define FNV_PRIME 16777619

/**
 * @brief Traverses a linked list of items for one with the correct 'key'
 * @param theItem
 * @param key
 * @return theItem || NULL
 */
item *itemSearch(item *theItem, char *key) {
	if(theItem && strcmp(key, theItem->key) == 0) {
		return theItem;
	} else if (theItem && theItem->next) {
		return itemSearch(theItem->next, key);
	}
	return NULL;
}

/**
 * @brief Hashing function for the hash table implementation. Currently uses division method
 *        Uses a 32bit FNV1-a hashing algorithm
 *        See: http://programmers.stackexchange.com/questions/49550/which-hashing-algorithm-is-best-for-uniqueness-and-speed
 * @param hashTable - current hash table 
 * @param key - key to lookup the value by
 * @return index in our items array where we can find the value
 */
int hashTableGetHash(table *hashTable, char *key)
{
	unsigned long hash = FNV_OFFSET_BASIS;
	unsigned char *k = (unsigned char *)key;
	while(*k != '\0') {  // Iterate over each character of the string
		hash = (((int)k ^ hash) * FNV_PRIME);
		k++;
	}
	return hash % hashTable->size; //return an index within the bounds of our hash table size
}

/**
 * @brief Creates a new hash table with a few safety checks for size and enough memory space
 * @param size
 * @return the new hash table || NULL if there is an issue allocating the table
 */
table *hashTableCreate(int size){
	printf("\n\nCreating table of size: %d\n", size);
	
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
void hashTableDestroy(table *hashTable)
{
    int i;
    item *theItem, *temp;

    if (hashTable == NULL) return;

    for(int i = 0; i < hashTable->size; i++) {
        theItem = hashTable->items[i];
        while(theItem != NULL) {
            temp = theItem;
            theItem = theItem->next;
			free(temp->key);
            free(temp->value);
            free(temp);
        }
    }
    free(hashTable->items);
    free(hashTable);
	hashTable = NULL;
}

/**
 * @brief Looks up an item in the hashtable, 
 *        Starts by traversing the linked list from the hash index
 * @param hashTable
 * @param key
 * @return item * || NULL
 */
item *hashTableSearch(table *hashTable, char *key) {
	int index = hashTableGetHash(hashTable, key);
	return itemSearch(hashTable->items[index], key);
}

/**
 * @brief Inserts a new item into the table. Makes sure the key's space is available and overwrites if necessary.
 *        When there is a collision with another item, it will prepend to top of the linked list.
 *        Designed generically to allow any type of pointer value to be set (though this hash map currently uses strings only)
 * @param hashTable
 * @param key
 * @param value
 */
void hashTableInsert(table *hashTable, char *key, void *value) {
	printf("Inserting value for '%s'\n", key);
	int index = hashTableGetHash(hashTable, key);
	item *firstItem = hashTable->items[index];

	if(firstItem == NULL) { //nothing occupies to space so allocate away
		printf("--- no item at this index yet\n");
		item *newItem = malloc(sizeof(item));
		newItem->key = strdup(key);
		newItem->value = value;
		newItem->next = NULL;
		hashTable->items[index] = newItem;
	} else { //there's something there, so we should traverse and check if it exists at all
	    printf("--- space is already occupied by {%s, %s} \n", firstItem->key, firstItem->value);
		item *existingItem = itemSearch(firstItem, key);
		if(existingItem == NULL) { //nothing is already occupying that key
			printf("--- key '%s' doesn't previously exist\n", key);
			item *newItem = malloc(sizeof(item));
			newItem->key = strdup(key);
			newItem->value = value;
			newItem->next = firstItem;
			hashTable->items[index] = newItem;
		} else { //the item exists so we only need to replace its value
		    printf("--- key '%s' already exists\n", key);
			free(existingItem->value); //deallocate the previous
			existingItem->value = value; 
		}
	}

}

/**
 * @brief Removes a single item from the hashTable and properly connects the linked list befor removal
 * @param hashTable
 * @param key
 */
void hashTableRemove(table *hashTable, char *key)
{
	int index = hashTableGetHash(hashTable, key);
	item *firstItem = hashTable->items[index];
	item *currentItem = firstItem;
	item *previousItem = NULL;
	if(firstItem == NULL) { //nothing exists at that index
		return;
	}
	while(currentItem) {
		if(currentItem && strcmp(key, currentItem->key) == 0) {
			//make sure we reassign our 'next' reference before deallocating
			if(previousItem) {
				previousItem->next = currentItem->next;
			} else {
				hashTable->items[index] = currentItem->next;
			}
			free(currentItem->key);
			free(currentItem->value);
			free(currentItem);
		}
		previousItem = currentItem;
		currentItem = currentItem->next;
	}	
}

/**
 * @brief Prints an unsorted list of all values in the hashTable
 * @param hashTable
 */
void hashTablePrint(table *hashTable) {
	int i = 0;
	printf("\nHash Table Contents \n");
	printf("------------------- \n");
	while(i < hashTable->size) {
		item *nextItem = hashTable->items[i];
		while(nextItem != NULL) {
			printf("'%s': %s\n", nextItem->key, nextItem->value);
			nextItem = nextItem->next;
		}
		i++;
	}
	printf("\n");
}

/**
 * @brief sets a string value on an item, on the hash table
 * @param hashTable
 * @param key
 * @param value
 */
void hashTableSet(table *hashTable, char *key, char *value) {
	hashTableInsert(hashTable, key, strdup(value));
}

/**
 * @brief get the string value of an item, from the hash table
 * @param hashTable
 * @param key
 * @return value || NULL
 */
char *hashTableGet(table *hashTable, char *key) {
	item* theItem = hashTableSearch(hashTable, key);
	if(theItem) {
		return theItem->value;
	}
	return NULL;
}
