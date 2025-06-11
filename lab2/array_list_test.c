#include "array_list.h"
#include "linear_allocator.h"
#include <assert.h>

void test_init() {
  linear_allocator *allocator = linear_allocator_init(1024);
  assert(allocator != NULL);

  ArrayList list;
  arraylist_init(&list, allocator, sizeof(int));
  assert(list.size == 0);
  assert(list.capacity == 0);
  assert(list.data == NULL);
  assert(list.element_size == sizeof(int));

  arraylist_free(&list);
  linear_allocator_deinit(allocator);
}

void test_add_get() {
  linear_allocator *allocator = linear_allocator_init(1024);
  ArrayList list;
  arraylist_init(&list, allocator, sizeof(int));

  int a = 10, b = 20, c = 30, d = 40;

  arraylist_add(&list, &a, 0);
  assert(list.size == 1);
  assert(*(int *)arraylist_get(&list, 0) == 10);

  arraylist_add(&list, &b, 0);
  arraylist_add(&list, &c, 2);
  assert(list.size == 3);
  assert(*(int *)arraylist_get(&list, 0) == 20);
  assert(*(int *)arraylist_get(&list, 1) == 10);
  assert(*(int *)arraylist_get(&list, 2) == 30);

  arraylist_free(&list);
  linear_allocator_deinit(allocator);
}

void test_delete() {
  linear_allocator *allocator = linear_allocator_init(1024);
  ArrayList list;
  arraylist_init(&list, allocator, sizeof(int));

  int values[] = {10, 20, 30, 40, 50};
  for (int i = 0; i < 5; i++) {
    arraylist_add(&list, &values[i], i);
  }

  arraylist_del(&list, 0);
  arraylist_del(&list, 2);
  assert(list.size == 3);
  assert(*(int *)arraylist_get(&list, 0) == 20);
  assert(*(int *)arraylist_get(&list, 1) == 30);
  assert(*(int *)arraylist_get(&list, 2) == 50);

  arraylist_free(&list);
  linear_allocator_deinit(allocator);
}

void test_reallocation() {
  linear_allocator *allocator = linear_allocator_init(1024);
  ArrayList list;
  arraylist_init(&list, allocator, sizeof(int));

  int value = 42;
  arraylist_add(&list, &value, 0);
  assert(list.capacity == 16);

  for (size_t i = 1; i < list.capacity; i++) {
    arraylist_add(&list, &value, i);
  }
  assert(list.size == list.capacity);

  arraylist_add(&list, &value, list.size);
  assert(list.size == 17);
  assert(list.capacity == 32);

  arraylist_free(&list);
  linear_allocator_deinit(allocator);
}

int main() {
  test_init();
  test_add_get();
  test_delete();
  test_reallocation();
  return 0;
}
