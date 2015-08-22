typedef struct _item {
	void *value;
	struct _item *next;
} item;

typedef struct {
	int size;
	struct _item **items;
} table;

int hashTableGetHash(table *hashTable, char *key);
table *hashTableCreate(int size);
void hashTableDelete(table *hashTable);

/**
 * @brief This Hash table allows for the storage of strings and integers
 */
void hashTablePutString(table *hashTable, char *key, char *value);
char *hashTableGetString(table *hashTable, char *key);

void hashTablePutInteger(table *hashTable, char *key, int value);
int hashTableGetInteger(table *hashTable, char *key);