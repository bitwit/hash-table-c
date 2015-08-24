#include <stdlib.h>
#include <assert.h>
#include "hashTable.h"

table *hashTable;

/**
 * @brief Executes several proofs on the hash table algorithm
 *        Creates a large hash table first
 *        Then a small hash table to force many collisions and retest assertions
 *        Some additional info about the process is also printed to output
 */
int main(int argc, char **argv)
{
	//First create an array with lots of space
	hashTable = hashTableCreate(100);
	test_shouldStoreStrings();
	test_shouldOverwriteExistingKeys();
	test_shouldRemoveKeys();
	
	hashTablePrint(hashTable); //printed to output
	
	//Destroy and recreate table with 1 slot, to prove collision chaining
	hashTableDestroy(hashTable);
	hashTable = hashTableCreate(1);
	test_shouldStoreStrings();
	test_shouldOverwriteExistingKeys();
	test_shouldRemoveKeys();
	
	hashTablePrint(hashTable); //printed to output
	return 0;
}

/**
 * Test assertions
 */

int test_shouldStoreStrings () {
	hashTableSet(hashTable, "Test1", "Cool Stuff");
	assert(strcmp(hashTableGet(hashTable, "Test1"), "Cool Stuff") == 0);
	return 1;
}

int test_shouldOverwriteExistingKeys () {
	hashTableSet(hashTable, "Test2", "Was not overwritten"); //Should not appear in the output
	hashTableSet(hashTable, "Test2", "Was overwritten");
	assert(strcmp(hashTableGet(hashTable, "Test2"), "Was overwritten") == 0);
	return 1;
}

int test_shouldRemoveKeys () {
	hashTableSet(hashTable, "Test3", "Should be removed");
	hashTableRemove(hashTable, "Test3");
	// Test3 should be null, because it was removed
	assert(hashTableGet(hashTable, "Test3") == NULL);
	return 1;
}
