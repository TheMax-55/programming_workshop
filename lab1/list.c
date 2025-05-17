#include "list.h"

Item *create_item(int data) {
  Item *new_item = (Item *)malloc(sizeof(Item));
  if (new_item == NULL) {
    exit(1);
  }

  new_item->value = data;
  new_item->next = NULL;
  return new_item;
}

void push_front(Item **head, int data) {
  Item *new_item = create_item(data);
  new_item->next = *head;
  *head = new_item;
}

void push_back(Item **head, int data) {
  Item *new_item = create_item(data);

  if (*head == NULL) {
    *head = new_item;
    return;
  }

  Item *current = *head;
  while (current->next != NULL) {
    current = current->next;
  }

  current->next = new_item;
}

void push_middle(Item **head, int data, int index) {

  if (index == 0) {
    push_front(head, data);
    return;
  }

  if (index < 0) {
    return;
  }

  Item *current = *head;
  int i = 0;

  while (current != NULL && i < index - 1) {
    current = current->next;
    i++;
  }

  if (current == NULL) {
    return;
  }

  Item *new_item = create_item(data);
  new_item->next = current->next;
  current->next = new_item;
}

void delete_item(Item **head, int value) {
  if (*head == NULL) {
    return;
  }

  if ((*head)->value == value) {
    Item *temp = *head;
    *head = (*head)->next;
    free(temp);
    return;
  }

  Item *current = *head;
  while (current->next != NULL && current->next->value != value) {
    current = current->next;
  }

  if (current->next != NULL) {
    Item *temp = current->next;
    current->next = temp->next;
    free(temp);
  }
}

Item *find_by_index(Item *head, int index) {
  if (index < 0) {
    return NULL;
  }

  Item *current = head;
  int i = 0;

  while (current != NULL && i < index) {
    current = current->next;
    i++;
  }

  return current;
}

int count_items(Item *head) {
  int count = 0;
  Item *current = head;

  while (current != NULL) {
    count++;
    current = current->next;
  }
  return count;
}

void print_list(Item *head) {
  if (head == NULL) {
    return;
  }
  Item *current = head;

  while (current != NULL) {
    current = current->next;
  }
}

void free_list(Item **head) {
  Item *current = *head;
  Item *next;

  while (current != NULL) {
    next = current->next;
    free(current);
    current = next;
  }
  *head = NULL;
}
