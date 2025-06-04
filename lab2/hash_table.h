#include "pool_allocator.h"
#include <stddef.h>

typedef struct HashTableEntry {
  char *key;
  void *value;
  struct HashTableEntry *next;
} HashTableEntry;

typedef struct {
  size_t capacity;
  HashTableEntry **buckets;
  PoolAllocator *allocator;
} HashTable;

void hashtable_init(HashTable *table, size_t capacity,
                    PoolAllocator *allocator);
void hashtable_insert(HashTable *table, const char *key, void *value);
void *hashtable_get(HashTable *table, const char *key);
void hashtable_del(HashTable *table, const char *key);
void hashtable_free(HashTable *table);
