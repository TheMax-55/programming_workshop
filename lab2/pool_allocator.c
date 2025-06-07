#include "pool_allocator.h"
#include <stdlib.h>

void *pool_init(int block_size, int blocks_num) {
  PoolAllocator *allocator = (PoolAllocator *)malloc(sizeof(PoolAllocator));
  if (!allocator)
    return NULL;

  allocator->block_size = block_size;
  allocator->blocks_num = blocks_num;
  allocator->first_free_block = blocks_num;

  allocator->mem_pool = malloc(block_size * blocks_num);
  if (!allocator->mem_pool) {
    free(allocator);
    return NULL;
  }
  allocator->free_blocks = (void **)malloc((size_t)blocks_num * sizeof(void *));
  if (!allocator->free_blocks) {
    free(allocator->mem_pool);
    free(allocator);
    return NULL;
  }

  for (int i = 0; i < blocks_num; i++) {
    allocator->free_blocks[i] = (char *)allocator->mem_pool + i * block_size;
  }

  return allocator;
}

void pool_deinit(void *allocator) {
  if (!allocator)
    return;
  PoolAllocator *alloc = (PoolAllocator *)allocator;
  free(alloc->free_blocks);
  free(alloc->mem_pool);
  free(alloc);
}

void *pool_alloc(void *allocator) {
  if (!allocator)
    return NULL;
  PoolAllocator *alloc = (PoolAllocator *)allocator;
  if (alloc->first_free_block == 0)
    return NULL;

  return alloc->free_blocks[--alloc->first_free_block];
}

void pool_free(void *allocator, void *ptr) {
  PoolAllocator *alloc = (PoolAllocator *)allocator;
  if (!allocator || !ptr || alloc->first_free_block >= alloc->blocks_num)
    return;
  alloc->free_blocks[alloc->first_free_block++] = ptr;
}
