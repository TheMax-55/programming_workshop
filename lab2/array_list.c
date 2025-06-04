#include "array_list.h"
#include <string.h>

void arraylist_init(ArrayList *list, linear_allocator *allocator) {
  list->data = NULL;
  list->size = 0;
  list->capacity = 0;
  list->allocator = allocator;
}

void arraylist_add(ArrayList *list, void *data, size_t index) {
  if (index > list->size)
    return;

  if (list->size == list->capacity) {
    size_t new_capacity = list->capacity ? list->capacity * 2 : 16;
    void **new_data =
        linear_alloc(list->allocator, new_capacity * sizeof(void *));
    if (!new_data)
      return;

    if (index > 0) {
      memcpy(new_data, list->data, index * sizeof(void *));
    }

    if (index < list->size) {
      memcpy(new_data + index + 1, list->data + index,
             (list->size - index) * sizeof(void *));
    }

    list->data = new_data;
    list->capacity = new_capacity;
  } else if (index < list->size) {
    memmove(list->data + index + 1, list->data + index,
            (list->size - index) * sizeof(void *));
  }

  list->data[index] = data;
  list->size++;
}

void *arraylist_get(ArrayList *list, size_t index) {
  if (index >= list->size)
    return NULL;
  return list->data[index];
}

void arraylist_del(ArrayList *list, size_t index) {
  if (index >= list->size)
    return;

  memmove(list->data + index, list->data + index + 1,
          (list->size - index - 1) * sizeof(void *));

  list->size--;
}

void arraylist_free(ArrayList *list) {
  list->data = NULL;
  list->size = 0;
  list->capacity = 0;
  list->allocator = NULL;
}
