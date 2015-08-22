#include "hashTable.h"

int main(int argc, char **argv)
{
	printf("Program Start!\n");
	table *hashTable = hashTableCreate(100);
	hashTablePutString(hashTable, "Tester", "Cool Stuff");
	hashTablePutInteger(hashTable, "Testeri", 1245);
	char *theValue = hashTableGetString(hashTable, "Tester");
	int theOtherValue = hashTableGetInteger(hashTable, "Testeri");
	printf("The value: %s!!!\n", theValue);
	printf("The other value: %d!!!\n", theOtherValue);
}

