#include "linear_allocator.h"

linear_allocator *linear_allocator_init(size_t size) {
  if (size == 0)
    return NULL;

  linear_allocator *allocator =
      (linear_allocator *)malloc(sizeof(linear_allocator));
  if (allocator == NULL) {
    return NULL;
  }

  allocator->memory_block = malloc(size);
  if (allocator->memory_block == NULL) {
    free(allocator);
    return NULL;
  }

  allocator->total_size = size;
  allocator->offset = 0;
  return allocator;
}

void linear_allocator_deinit(linear_allocator *allocator) {
  if (allocator == NULL) {
    return;
  }

  if (allocator->memory_block != NULL) {
    free(allocator->memory_block);
  }
  free(allocator);
}

void *linear_allocator_alloc(linear_allocator *allocator, size_t size) {
  if (!allocator || size == 0) {
    return NULL;
  }

  if (allocator->offset > allocator->total_size ||
      size > allocator->total_size - allocator->offset) {
    return NULL;
  }

  void *address = (char *)allocator->memory_block + allocator->offset;
  allocator->offset += size;
  return address;
}

void linear_allocator_reset(linear_allocator *allocator) {
  if (allocator == NULL) {
    return;
  }
  allocator->offset = 0;
}

void *linear_alloc(void *allocator, size_t size) {
  return linear_allocator_alloc((linear_allocator *)allocator, size);
}

void linear_reset(void *allocator) {
  linear_allocator_reset((linear_allocator *)allocator);
}
