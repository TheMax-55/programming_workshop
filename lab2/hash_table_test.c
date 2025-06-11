#include "hash_table.h"
#include "pool_allocator.h"
#include <assert.h>
#include <stdlib.h>
#include <string.h>

void test_initialization() {
  PoolAllocator *mem = pool_init(sizeof(HashTableEntry), 5);
  HashTable ht;

  hashtable_init(&ht, 4, sizeof(int), mem);
  assert(ht.capacity == 4);
  assert(ht.buckets != NULL);
  assert(ht.allocator == mem);

  for (size_t j = 0; j < ht.capacity; j++) {
    assert(ht.buckets[j] == NULL);
  }

  hashtable_free(&ht);
  pool_deinit(mem);
}

void test_insert_retrieve() {
  PoolAllocator *mem = pool_init(sizeof(HashTableEntry), 6);
  HashTable ht;
  hashtable_init(&ht, 3, sizeof(int), mem);

  int x = 7, y = 13, z = 42;

  hashtable_insert(&ht, "alpha", &x);
  hashtable_insert(&ht, "beta", &y);
  hashtable_insert(&ht, "gamma", &z);

  assert(*(int *)hashtable_get(&ht, "alpha") == 7);
  assert(*(int *)hashtable_get(&ht, "beta") == 13);
  assert(*(int *)hashtable_get(&ht, "gamma") == 42);

  int w = 99;
  hashtable_insert(&ht, "beta", &w);
  assert(*(int *)hashtable_get(&ht, "beta") == 99);

  assert(hashtable_get(&ht, "delta") == NULL);

  hashtable_free(&ht);
  pool_deinit(mem);
}

void test_remove() {
  PoolAllocator *mem = pool_init(sizeof(HashTableEntry), 4);
  HashTable ht;
  hashtable_init(&ht, 2, sizeof(double), mem);

  double pi = 3.1415, e = 2.7182;

  hashtable_insert(&ht, "const1", &pi);
  hashtable_insert(&ht, "const2", &e);

  assert(*(double *)hashtable_get(&ht, "const1") == 3.1415);
  assert(*(double *)hashtable_get(&ht, "const2") == 2.7182);

  hashtable_del(&ht, "const1");
  assert(hashtable_get(&ht, "const1") == NULL);
  assert(*(double *)hashtable_get(&ht, "const2") == 2.7182);

  hashtable_del(&ht, "unknown");

  hashtable_free(&ht);
  pool_deinit(mem);
}

void test_collisions() {
  PoolAllocator *mem = pool_init(sizeof(HashTableEntry), 8);
  HashTable ht;
  hashtable_init(&ht, 1, sizeof(char *), mem);

  char *items[] = {"red", "green", "blue", "yellow"};

  for (int k = 0; k < 4; k++) {
    hashtable_insert(&ht, items[k], &items[k]);
  }

  for (int k = 0; k < 4; k++) {
    assert(*(char **)hashtable_get(&ht, items[k]) == items[k]);
  }

  hashtable_del(&ht, "green");
  assert(hashtable_get(&ht, "green") == NULL);
  assert(*(char **)hashtable_get(&ht, "red") == items[0]);
  assert(*(char **)hashtable_get(&ht, "blue") == items[2]);

  hashtable_free(&ht);
  pool_deinit(mem);
}

int main() {
  test_initialization();
  test_insert_retrieve();
  test_remove();
  test_collisions();

  return 0;
}
