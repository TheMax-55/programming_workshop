#ifndef LIST_H
#define LIST_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Item {
  int value;
  struct Item *next;
} Item;
Item *create_item(int data);
void push_front(Item **head, int data);
void push_back(Item **head, int data);
void push_middle(Item **head, int data, int index);
void delete_item(Item **head, int value);
Item *find_by_index(Item *head, int index);
int count_items(Item *head);
void print_list(Item *head);
void free_list(Item **head);

#endif
