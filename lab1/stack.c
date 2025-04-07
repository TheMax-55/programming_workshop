#include "stack.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

void init_stack(Stack *s, int size) {
  s->top = -1;
  s->size = size;
  s->elem = (int *)malloc(size * sizeof(int));
}

bool is_empty(Stack *s) { return s->top == -1; }

bool is_full(Stack *s) { return s->top == s->size - 1; }

int push(Stack *s, int num) {
  if (is_full(s)) {
    return OVERFLOW_ERROR;
  }
  s->elem[++s->top] = num;
  return 0;
}

int pop(Stack *s, int *outnum) {
  if (is_empty(s)) {
    return UNDERFLOW_ERROR;
  }
  *outnum = s->elem[s->top];
  return s->elem[--s->top];
}
