#include "../headers/deque.h"
#include <assert.h>
#include <stdarg.h>
#include <stdlib.h>

Deque dequeConstruct(int n, ...)
{
  // TODO: Is the following assert redundant to establish an invariant?
  assert(n >= 0);

  Deque deque = {.first = NULL, .last = NULL, .size = 0, .operationCounter = 0};
  va_list initList;
  va_start(initList, n);

  for (int i = 0; i < n; ++i)
  {
    const Item item = va_arg(initList, Item);
    dequePushBack(&deque, &item);
  }

  va_end(initList);
  return deque;
}


void dequeDestruct(Deque *const restrict deque)
{
  struct Node *current = deque->first;
  while (current)
  {
    deque->first = deque->first->next;
    free(current);
    current = deque->first;
  }

  deque->last = NULL;
  deque->size = 0;
  deque->operationCounter = 0;
}


void dequeCopy(Deque *const dest, const Deque *const src)
{
  dequeDestruct(dest);

  struct Node *current = src->first;
  while (current)
  {
    dequePushBack(dest, &(current->item));
    current = current->next;
  }
}


Iterator dequeFirst(Deque *const restrict deque)
{
  return (Iterator)
  {
    .deque = deque,
    .current = deque->first,
    .currentOperationCounter = deque->operationCounter
  };
}


Iterator dequeLast(Deque *const restrict deque)
{
  return (Iterator)
  {
    .deque = deque,
    .current = deque->last,
    .currentOperationCounter = deque->operationCounter
  };
}


bool dequeHasPrevious(const Iterator *const restrict itr)
{
  assert(itr->currentOperationCounter == itr->deque->operationCounter);
  return itr->current != NULL;
}


Item *dequePrevious(Iterator *const restrict itr)
{
  assert
  (
    itr->current != NULL &&
    itr->currentOperationCounter == itr->deque->operationCounter
  );

  Item *item = &(itr->current->item);
  itr->current = itr->current->prev;
  return item;
}


bool dequeHasNext(const Iterator *const restrict itr)
{
  return dequeHasPrevious(itr);
}


Item *dequeNext(Iterator *const restrict itr)
{
  assert
  (
    itr->current != NULL &&
    itr->currentOperationCounter == itr->deque->operationCounter
  );

  Item *item = &(itr->current->item);
  itr->current = itr->current->next;
  return item;
}


int dequeSize(const Deque *const restrict deque)
{
  return deque->size;
}


bool dequeIsEmpty(const Deque *const restrict deque)
{
  return deque->size == 0;
}


void dequePushFront(Deque *const restrict deque,
                    const Item *const restrict item)
{
  struct Node *oldFirst = deque->first;
  // TODO: Test against memory allocation failure!
  deque->first = (struct Node *)malloc(sizeof(struct Node));
  deque->first->item = *item;
  deque->first->prev = NULL;
  deque->first->next = oldFirst;

  if (deque->size == 0)
  {
    deque->last = deque->first;
  }
  else
  {
    deque->last->prev = deque->first;
  }

  ++(deque->size);
  ++(deque->operationCounter);
}


void dequePushBack(Deque *const restrict deque,
                   const Item *const restrict item)
{
  struct Node *const oldLast = deque->last;
  // TODO: Test against memory allocation failure!
  deque->last = (struct Node *const)malloc(sizeof(struct Node));
  deque->last->item = *item;
  deque->last->prev = oldLast;
  deque->last->next = NULL;

  if (deque->size == 0)
  {
    deque->first = deque->last;
  }
  else
  {
    oldLast->next = deque->last;
  }

  ++(deque->size);
  ++(deque->operationCounter);
}


Item dequePopFront(Deque *const restrict deque)
{
  assert(deque->size > 0);

  struct Node *const oldFirst = deque->first;
  deque->first = deque->first->next;
  const Item item = oldFirst->item;
  free(oldFirst);
  --(deque->size);
  ++(deque->operationCounter);

  if (deque->size == 0)
  {
    deque->last = NULL;
  }
  else
  {
    deque->first->prev = NULL;
  }

  return item;
}


Item dequePopBack(Deque *const restrict deque)
{
  assert(deque->size > 0);

  struct Node *const oldLast = deque->last;
  deque->last = deque->last->prev;
  const Item item = oldLast->item;
  free(oldLast);
  --(deque->size);
  ++(deque->operationCounter);

  if (deque->size == 0)
  {
    deque->first = NULL;
  }
  else
  {
    deque->last->next = NULL;
  }

  return item;
}


void dequeInsert(Iterator *const position, const Item *const restrict item)
{
  if (position->deque->size == 0 || position->current == position->deque->first)
  {
    dequePushFront(position->deque, item);
  }
  else
  {
    // TODO: Test against memory allocation failure!
    struct Node *const node = (struct Node *const)malloc(sizeof(struct Node));
    node->item = *item;
    node->prev = position->current->prev;
    position->current->prev->next = node;
    position->current->prev = node;
    node->next = position->current;

    ++position->deque->size;
    ++position->deque->operationCounter;
  }
}


// TODO: Test whether iterator is already at the end of the deque?!
Item dequeErase(Iterator *const position)
{
  assert(position->deque->size > 0);

  Item item;

  if (position->current == position->deque->first)
  {
    position->current = position->current->next;
    item = dequePopFront(position->deque);
  }
  else if (position->current == position->deque->last)
  {
    position->current = position->current->next;
    item = dequePopBack(position->deque);
  }
  else
  {
    struct Node *const oldCurrent = position->current;
    position->current = position->current->next;
    oldCurrent->prev->next = position->current;
    position->current->prev = oldCurrent->prev;
    item = oldCurrent->item;
    free(oldCurrent);

    --(position->deque->size);
    ++(position->deque->operationCounter);
  }

  return item;
}
