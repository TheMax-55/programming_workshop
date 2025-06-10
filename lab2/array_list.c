#include "array_list.h"
#include <string.h>

void arraylist_init(ArrayList *list, linear_allocator *allocator,
                    size_t element_size) {
  list->data = NULL;
  list->size = 0;
  list->capacity = 0;
  list->allocator = allocator;
  list->element_size = element_size;
}

void arraylist_add(ArrayList *list, void *data, size_t index) {
  if (index > list->size)
    return;

  if (list->size == list->capacity) {
    size_t new_capacity = list->capacity ? list->capacity * 2 : 16;
    void *new_data =
        linear_alloc(list->allocator, new_capacity * list->element_size);
    if (!new_data)
      return;

    if (index > 0) {
      memcpy(new_data, list->data, index * list->element_size);
    }

    if (index < list->size) {
      memcpy((char *)new_data + (index + 1) * list->element_size,
             (char *)list->data + index * list->element_size,
             (list->size - index) * list->element_size);
    }

    list->data = new_data;
    list->capacity = new_capacity;
  } else if (index < list->size) {
    memmove((char *)list->data + (index + 1) * list->element_size,
            (char *)list->data + index * list->element_size,
            (list->size - index) * list->element_size);
  }

  memcpy((char *)list->data + index * list->element_size, data,
         list->element_size);
  list->size++;
}

void *arraylist_get(ArrayList *list, size_t index) {
  if (index >= list->size)
    return NULL;
  return (char *)list->data + index * list->element_size;
}

void arraylist_del(ArrayList *list, size_t index) {
  if (index >= list->size)
    return;

  memmove((char *)list->data + index * list->element_size,
          (char *)list->data + (index + 1) * list->element_size,
          (list->size - index - 1) * list->element_size);

  list->size--;
}

void arraylist_free(ArrayList *list) {
  list->data = NULL;
  list->size = 0;
  list->capacity = 0;
  list->allocator = NULL;
  list->element_size = 0;
}
