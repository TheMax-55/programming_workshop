#ifndef LINEAR_ALLOCATOR_H
#define LINEAR_ALLOCATOR_H

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
  void *memory_block;
  size_t total_size;
  size_t offset;
} linear_allocator;

linear_allocator *linear_allocator_init(size_t size);
void linear_allocator_deinit(linear_allocator *allocator);

void *linear_alloc(void *allocator, size_t size);
void linear_reset(void *allocator);

void *linear_allocator_alloc(linear_allocator *allocator, size_t size);
void linear_allocator_reset(linear_allocator *allocator);

#endif
