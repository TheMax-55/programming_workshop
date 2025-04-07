#include <stdbool.h>
#define OVERFLOW_ERROR -1
#define UNDERFLOW_ERROR -2

typedef struct {
  int top;
  int *elem;
  int size;
} Stack;

void init_stack(Stack *s, int size);
bool is_empty(Stack *s);
bool is_full(Stack *s);
int push(Stack *s, int num);
int pop(Stack *s, int *outnum);
