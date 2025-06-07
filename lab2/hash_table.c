#include "hash_table.h"
#include <stdlib.h>
#include <string.h>

static unsigned int generate_hash(const char *key, size_t capacity) {
  unsigned int hash = 0;
  while (*key) {
    hash = (hash * 31) + *key++;
  }
  return hash % capacity;
}

void hashtable_init(HashTable *table, size_t capacity,
                    PoolAllocator *allocator) {
  table->capacity = capacity;
  table->allocator = allocator;
  table->buckets = calloc(capacity, sizeof(HashTableEntry *));
}

void hashtable_insert(HashTable *table, const char *key, void *value) {
  if (table == NULL || key == NULL)
    return;

  unsigned int bucket_index = generate_hash(key, table->capacity);
  HashTableEntry *current_entry = table->buckets[bucket_index];

  while (current_entry != NULL) {
    if (strcmp(current_entry->key, key) == 0) {
      current_entry->value = value;
      return;
    }
    current_entry = current_entry->next;
  }

  HashTableEntry *new_entry = pool_alloc(table->allocator);
  if (new_entry == NULL)
    return;

  new_entry->key = strdup(key);
  new_entry->value = value;
  new_entry->next = table->buckets[bucket_index];
  table->buckets[bucket_index] = new_entry;
}

void *hashtable_get(HashTable *table, const char *key) {
  if (table == NULL || key == NULL)
    return NULL;

  unsigned int bucket_index = generate_hash(key, table->capacity);
  HashTableEntry *current_entry = table->buckets[bucket_index];

  while (current_entry != NULL) {
    if (strcmp(current_entry->key, key) == 0) {
      return current_entry->value;
    }
    current_entry = current_entry->next;
  }
  return NULL;
}

void hashtable_del(HashTable *table, const char *key) {
  if (table == NULL || key == NULL)
    return;

  unsigned int bucket_index = generate_hash(key, table->capacity);
  HashTableEntry **entry_ptr = &table->buckets[bucket_index];

  while (*entry_ptr != NULL) {
    HashTableEntry *entry = *entry_ptr;
    if (strcmp(entry->key, key) == 0) {
      *entry_ptr = entry->next;
      free(entry->key);
      pool_free(table->allocator, entry);
      return;
    }
    entry_ptr = &entry->next;
  }
}

void hashtable_free(HashTable *table) {
  if (table == NULL)
    return;

  for (size_t i = 0; i < table->capacity; i++) {
    HashTableEntry *entry = table->buckets[i];
    while (entry != NULL) {
      HashTableEntry *next_entry = entry->next;
      free(entry->key);
      pool_free(table->allocator, entry);
      entry = next_entry;
    }
  }

  free(table->buckets);
  table->buckets = NULL;
  table->capacity = 0;
  table->allocator = NULL;
}
