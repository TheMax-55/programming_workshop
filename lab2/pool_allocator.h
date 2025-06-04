#ifndef POOL_ALLOCATOR_H
#define POOL_ALLOCATOR_H

#include <stdbool.h>
#include <stddef.h>

typedef struct {
  int block_size;
  int blocks_num;
  void **free_blocks;
  void *mem_pool;
  int first_free_block;
} PoolAllocator;

void *pool_init(int block_size, int blocks_num);
void pool_deinit(void *allocator);
void *pool_alloc(void *allocator);
void pool_free(void *allocator, void *ptr);

#endif
