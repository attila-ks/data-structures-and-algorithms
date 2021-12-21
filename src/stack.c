#include "../headers/stack.h"
#include <assert.h>
#include <stdarg.h>
#include <stdlib.h>

Stack stackConstruct(int n, ...)
{
  // TODO: Is the following assert redundant to establish an invariant?
  assert(n >= 0);

  Stack stack = {NULL, 0, 0};
  va_list initList;
  va_start(initList, n);

  for (int i = 0; i < n; ++i)
  {
    const Item item = va_arg(initList, Item);
    stackPush(&stack, &item);
  }

  va_end(initList);
  return stack;
}


void stackDestruct(Stack *const restrict stack)
{
  struct Node *current = stack->first;

  while (current)
  {
    stack->first = stack->first->next;
    free(current);
    current = stack->first;
  }

  stack->first = NULL;
  stack->size = 0;
  stack->operationCounter = 0;
}


void stackCopy(Stack *const dest, const Stack *const src)
{
  // TODO: Is there a faster way to copy a Stack?
  Item items[src->size];
  const struct Node *current = src->first;

  for (int i = 0; i < src->size; ++i)
  {
    items[i] = current->item;
    current = current->next;
  }

  stackDestruct(dest);

  for (int i = src->size - 1; i >= 0; --i)
  {
    stackPush(dest, &(items[i]));
  }
}


Iterator stackFirst(Stack *const restrict stack)
{
  return (Iterator)
  {
    stack->first,
    &(stack->operationCounter),
    stack->operationCounter
  };
}


bool stackHasNext(const Iterator *const restrict itr)
{
  assert(itr->currentOperationCounter == *(itr->operationCounterPtr));

  return itr->current != NULL;
}


Item *stackNext(Iterator *const restrict itr)
{
  assert(itr->currentOperationCounter == *(itr->operationCounterPtr));

  Item *item = &(itr->current->item);
  itr->current = itr->current->next;
  return item;
}


bool stackIsEmpty(const Stack *const restrict stack)
{
  return stack->size == 0;
}


int stackSize(const Stack *const restrict stack)
{
  return stack->size;
}


Item *stackTop(Stack *const restrict stack)
{
  assert(stack->size > 0);
  return &(stack->first->item);
}


void stackPush(Stack *const restrict stack, const Item *const restrict item)
{
  struct Node *const oldFirst = stack->first;
  // TODO: Test against memory allocation failure!
  stack->first = (struct Node *const)malloc(sizeof(struct Node));
  stack->first->item = *item;
  stack->first->next = oldFirst;
  ++(stack->size);
  ++(stack->operationCounter);
}


Item stackPop(Stack *const restrict stack)
{
  assert(stack->size > 0);

  const Item item = stack->first->item;
  stack->first = stack->first->next;
  --(stack->size);
  ++(stack->operationCounter);
  return item;
}
