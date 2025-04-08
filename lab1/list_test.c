#include "list.h"
#include <assert.h>
#include <stdio.h>

void test_create_item() {
  Item *item = create_item(10);
  assert(item != NULL);
  assert(item->value == 10);
  assert(item->next == NULL);
  free(item);
}

void test_push_front() {
  Item *head = NULL;

  push_front(&head, 10);
  assert(head != NULL);
  assert(head->value == 10);
  assert(head->next == NULL);

  push_front(&head, 20);
  assert(head != NULL);
  assert(head->value == 20);
  assert(head->next != NULL);
  assert(head->next->value == 10);

  free_list(&head);
  assert(head == NULL);
}

void test_push_back() {
  Item *head = NULL;

  push_back(&head, 10);
  assert(head != NULL);
  assert(head->value == 10);
  assert(head->next == NULL);

  push_back(&head, 20);
  assert(head != NULL);
  assert(head->value == 10);
  assert(head->next != NULL);
  assert(head->next->value == 20);

  free_list(&head);
}

void test_push_middle() {
  Item *head = NULL;

  push_middle(&head, 10, 0);
  assert(head != NULL);
  assert(head->value == 10);

  push_middle(&head, 20, 0);
  assert(head->value == 20);
  assert(head->next->value == 10);

  push_middle(&head, 15, 1);
  assert(head->value == 20);
  assert(head->next->value == 15);
  assert(head->next->next->value == 10);

  push_middle(&head, 5, 3);
  assert(head->next->next->next->value == 5);

  free_list(&head);
}

void test_delete_item() {
  Item *head = NULL;

  push_back(&head, 10);
  push_back(&head, 20);
  push_back(&head, 30);

  delete_item(&head, 20);
  assert(head->value == 10);
  assert(head->next->value == 30);
  assert(head->next->next == NULL);

  delete_item(&head, 10);
  assert(head->value == 30);
  assert(head->next == NULL);

  delete_item(&head, 30);
  assert(head == NULL);

  free_list(&head);
}

void test_find_by_index() {
  Item *head = NULL;

  assert(find_by_index(head, 0) == NULL);

  push_back(&head, 10);
  push_back(&head, 20);
  push_back(&head, 30);

  Item *found = find_by_index(head, 0);
  assert(found != NULL && found->value == 10);

  found = find_by_index(head, 1);
  assert(found != NULL && found->value == 20);

  found = find_by_index(head, 2);
  assert(found != NULL && found->value == 30);

  assert(find_by_index(head, 3) == NULL);

  free_list(&head);
}

void test_count_items() {
  Item *head = NULL;

  assert(count_items(head) == 0);

  push_back(&head, 10);
  assert(count_items(head) == 1);

  push_back(&head, 20);
  push_back(&head, 30);
  assert(count_items(head) == 3);

  delete_item(&head, 20);
  assert(count_items(head) == 2);

  free_list(&head);
}

int main() {
  test_create_item();
  test_push_front();
  test_push_back();
  test_push_middle();
  test_delete_item();
  test_find_by_index();
  test_count_items();
  return 0;
}
