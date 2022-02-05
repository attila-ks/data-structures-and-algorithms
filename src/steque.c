#include "../headers/steque.h"
#include <assert.h>
#include <stdarg.h>
#include <stdlib.h>

Steque stequeConstruct(const bool push, const int n, ...)
{
  // TODO: Is the following assert redundant to establish an invariant?
  assert(n >= 0);

  Steque steque = {
      .first = NULL, .last = NULL, .size = 0, .operationCounter = 0};
  va_list initList;
  va_start(initList, n);
  void (*func)(Steque *const restrict, const Item *const restrict) =
      push ? stequePush : stequeEnqueue;

  for (int i = 0; i < n; ++i)
  {
    const Item item = va_arg(initList, Item);
    func(&steque, &item);
  }

  va_end(initList);
  return steque;
}


void stequeDestruct(Steque *const restrict steque)
{
  struct Node *current = steque->first;

  while (current)
  {
    steque->first = steque->first->next;
    free(current);
    current = steque->first;
  }

  steque->first = NULL;
  steque->last = NULL;
  steque->size = 0;
  steque->operationCounter = 0;
}


void stequeCopy(Steque *const dest, const Steque *const src)
{
  stequeDestruct(dest);

  const struct Node *current = src->first;

  while (current)
  {
    stequeEnqueue(dest, &(current->item));
    current = current->next;
  }
}


Iterator stequeFirst(Steque *const restrict steque)
{
  return (Iterator)
  {
    .steque = steque,
    .current = steque->first,
    .currentOperationCounter = steque->operationCounter
  };
}


Iterator stequeLast(Steque *const restrict steque)
{
  return (Iterator)
  {
    .steque = steque,
    .current = steque->last,
    .currentOperationCounter = steque->operationCounter
  };
}


bool stequeHasNext(const Iterator *const restrict itr)
{
  assert(itr->currentOperationCounter == itr->steque->operationCounter);

  return itr->current != NULL;
}


Item *stequeNext(Iterator *const restrict itr)
{
  assert
  (
    itr->current != NULL &&
    itr->currentOperationCounter == itr->steque->operationCounter
  );

  Item *item = &(itr->current->item);
  itr->current = itr->current->next;
  return item;
}


bool stequeIsEmpty(const Steque *const restrict steque)
{
  return steque->size == 0;
}


int stequeSize(const Steque *const restrict steque)
{
  return steque->size;
}


Item *stequeTop(Steque *const restrict steque)
{
  assert(steque->size > 0);
  return &(steque->first->item);
}


void stequePush(Steque *const restrict steque, const Item *const restrict item)
{
  struct Node *const oldFirst = steque->first;
  // TODO: Test against memory allocation failure!
  steque->first = (struct Node *)malloc(sizeof(struct Node));
  steque->first->item = *item;
  steque->first->next = oldFirst;

  if (steque->size == 0)
  {
    steque->last = steque->first;
  }

  ++(steque->size);
  ++(steque->operationCounter);
}


void stequeEnqueue(Steque *const restrict steque,
                   const Item *const restrict item)
{
  struct Node *const oldLast = steque->last;
  // TODO: Test against memory allocation failure!
  steque->last = (struct Node *)malloc(sizeof(struct Node));
  steque->last->item = *item;
  steque->last->next = NULL;

  if (steque->size == 0)
  {
    steque->first = steque->last;
  }
  else
  {
    oldLast->next = steque->last;
  }

  ++(steque->size);
  ++(steque->operationCounter);
}


Item stequePop(Steque *const restrict steque)
{
  assert(steque->size > 0);

  const Item item = steque->first->item;
  struct Node *oldFirst = steque->first;
  steque->first = steque->first->next;
  free(oldFirst);

  --(steque->size);
  ++(steque->operationCounter);

  if (steque->size == 0)
  {
    steque->last = NULL;
  }

  return item;
}
