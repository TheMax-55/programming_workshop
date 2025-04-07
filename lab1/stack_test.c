#include "stack.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

void init_stack_test() {
  Stack s;
  init_stack(&s, 5);
  assert(s.top == -1);
  assert(s.size == 5);
}

void empty_stack_test() {
  Stack s;
  init_stack(&s, 2);
  assert(is_empty(&s) == 1);
}

void full_stack_test() {
  Stack s;
  init_stack(&s, 3);
  push(&s, 5);
  push(&s, 6);
  push(&s, 7);
  assert(is_full(&s) == 1);
}

void push_test() {
  Stack s;
  init_stack(&s, 2);
  push(&s, 45);
  assert(s.top == 0);
  assert(s.elem[0] == 45);
  push(&s, 60);
  assert(s.top == 1);
  assert(s.elem[1] == 60);
}

void pop_test() {
  Stack s;
  int val;
  init_stack(&s, 3);
  push(&s, 10);
  push(&s, 20);
  push(&s, 30);

  pop(&s, &val);
  assert(val == 30);
  assert(s.top == 1);
  pop(&s, &val);
  assert(val == 20);
  assert(s.top == 0);
  pop(&s, &val);
  assert(val == 10);
  assert(s.top == -1);
}

void stack_underflow_test() {
  Stack s;
  int val;
  init_stack(&s, 2);
  assert(pop(&s, &val) == UNDERFLOW_ERROR);
}

void stack_overflow_test() {
  Stack s;
  init_stack(&s, 2);
  push(&s, 5);
  push(&s, 10);
  push(&s, 15);
  assert(s.top == 1);
  assert(s.elem[1] == 10);
}

int main() {
  init_stack_test();
  empty_stack_test();
  full_stack_test();
  push_test();
  pop_test();
  stack_underflow_test();
  stack_overflow_test();
  return 0;
}
