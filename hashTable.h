/**
 * @brief The item linked list structure & accompanying functions
 */
typedef struct _item {
	char *key;
	char *value;
	struct _item *next;
} item;

item *itemSearch(item *theItem, char *key);

/**
* @brief The Hash Table & accompanying functions
*/
typedef struct {
	int size;
	struct _item **items;
} table;

int hashTableGetHash(table *hashTable, char *key);
table *hashTableCreate(int size);
void hashTableDestroy(table *hashTable);
item *hashTableSearch(table *hashTable, char *key);
void hashTableInsert(table *hashTable, char *key, void *value);
void hashTableRemove(table *hashTable, char *key);
void hashTablePrint(table *hashTable);

/**
 * @brief This Hash table allows for the storage of strings
 */
void hashTableSet(table *hashTable, char *key, char *value);
char *hashTableGet(table *hashTable, char *key);