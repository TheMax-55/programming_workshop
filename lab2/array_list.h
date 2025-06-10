#include "linear_allocator.h"

typedef struct {
  void **data;
  size_t size;
  size_t capacity;
  size_t element_size;
  linear_allocator *allocator;
} ArrayList;

void arraylist_init(ArrayList *list, linear_allocator *allocator,
                    size_t element_size);
void arraylist_add(ArrayList *list, void *data, size_t index);
void *arraylist_get(ArrayList *list, size_t index);
void arraylist_del(ArrayList *list, size_t index);
void arraylist_free(ArrayList *list);
