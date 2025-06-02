#include "pool_allocator.h"
#include <assert.h>

void test_pool_init() {
  int block_size = 64;
  int blocks_num = 10;
  PoolAllocator *alloc = (PoolAllocator *)pool_init(block_size, blocks_num);
  assert(alloc != NULL);
  assert(alloc->mem_pool != NULL);
  assert(alloc->block_size == block_size);
  assert(alloc->blocks_num == blocks_num);
  assert(alloc->first_free_block == blocks_num);
  for (int i = 0; i < blocks_num; i++) {
    void *test_blocks = (char *)alloc->mem_pool + i * block_size;
    assert(alloc->free_blocks[i] == test_blocks);
  }

  pool_deinit(alloc);
}
void test_single_allocation() {
  int block_size = 64;
  int blocks_num = 10;
  PoolAllocator *alloc = (PoolAllocator *)pool_init(block_size, blocks_num);
  void *block = pool_alloc(alloc);
  assert(block != NULL);
  pool_free(alloc, block);
  pool_deinit(alloc);
}
void test_full_allocation() {
  int block_size = 64;
  int blocks_num = 5;
  PoolAllocator *alloc = (PoolAllocator *)pool_init(block_size, blocks_num);
  void *blocks[5];
  for (int i = 0; i < blocks_num; i++) {
    blocks[i] = pool_alloc(alloc);
    assert(blocks[i] != NULL);
  }
  assert(pool_alloc(alloc) == NULL);

  for (int i = 0; i < blocks_num; i++) {
    pool_free(alloc, blocks[i]);
  }
  pool_deinit(alloc);
}
void test_reuse() {
  int block_size = 64;
  int blocks_num = 2;
  PoolAllocator *alloc = (PoolAllocator *)pool_init(block_size, blocks_num);
  void *block1 = pool_alloc(alloc);
  void *block2 = pool_alloc(alloc);
  pool_free(alloc, block1);
  void *block1_reuse = pool_alloc(alloc);
  assert(block1 == block1_reuse);
  pool_free(alloc, block2);
  pool_free(alloc, block1_reuse);
  pool_deinit(alloc);
}
int main() {
  test_pool_init();
  test_single_allocation();
  test_full_allocation();
  test_reuse();
  return 0;
}
