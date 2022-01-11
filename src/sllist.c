#include "../headers/sllist.h"
#include <assert.h>
#include <stdarg.h>
#include <stdlib.h>

SLList sllistConstruct(int n, ...)
{
  // TODO: Is the following assert redundant to establish an invariant?
  assert(n >= 0);

  SLList list = {NULL, NULL, 0, 0};
  va_list initList;
  va_start(initList, n);

  for (int i = 0; i < n; ++i)
  {
    const Item item = va_arg(initList, Item);
    sllistPushBack(&list, &item);
  }

  va_end(initList);
  return list;
}


void sllistDestruct(SLList *const restrict list)
{
  struct Node *current = list->first;

  while (current)
  {
    list->first = list->first->next;
    free(current);
    current = list->first;
  }

  list->last = NULL;
  list->size = 0;
  list->operationCounter = 0;
}


void sllistCopy(SLList *const dest, const SLList *const src)
{
  sllistDestruct(dest);

  const struct Node *current = src->first;

  while (current)
  {
    sllistPushBack(dest, &(current->item));
    current = current->next;
  }
}


Iterator sllistFirst(SLList *const restrict list)
{
  return (Iterator)
  {
    list->first,
    &(list->operationCounter),
    list->operationCounter
  };
}


Iterator sllistLast(SLList *const restrict list)
{
  return (Iterator)
  {
    list->last,
    &(list->operationCounter),
    list->operationCounter
  };
}


bool sllistHasNext(const Iterator *const restrict itr)
{
  assert
  (
    *(itr->operationCounterPtr) == itr->currentOperationCounter
  );

  return itr->current != NULL;
}


Item *sllistNext(Iterator *const restrict itr)
{
  assert
  (
    *(itr->operationCounterPtr) == itr->currentOperationCounter &&
    itr->current != NULL
  );

  Item *item = &(itr->current->item);
  itr->current = itr->current->next;
  return item;
}


bool sllistIsEmpty(const SLList *const restrict list)
{
  return list->size == 0;
}


int sllistSize(const SLList *const restrict list)
{
  return list->size;
}


void sllistPushFront(SLList *const restrict list,
                     const Item *const restrict item)
{
  struct Node *const oldFirst = list->first;
  // TODO: Test against memory allocation failure!
  list->first = (struct Node *const)malloc(sizeof(struct Node));
  list->first->item = *item;
  list->first->next = oldFirst;

  if (list->size == 0)
  {
    list->last = list->first;
  }

  ++list->size;
  ++list->operationCounter;
}


Item sllistPopFront(SLList *const restrict list)
{
  assert(list->size > 0);

  struct Node *const oldFirst = list->first;
  list->first = list->first->next;
  Item item = oldFirst->item;
  free(oldFirst);

  --list->size;
  ++list->operationCounter;

  if (list->size == 0)
  {
    list->last = NULL;
  }

  return item;
}


void sllistPushBack(SLList *const restrict list,
                    const Item *const restrict item)
{
  struct Node *const oldLast = list->last;
  // TODO: Test against memory allocation failure!
  list->last = (struct Node *const)malloc(sizeof(struct Node));
  list->last->item = *item;
  list->last->next = NULL;

  if (list->size == 0)
  {
    list->first = list->last;
  }
  else
  {
    oldLast->next = list->last;
  }

  ++list->size;
  ++list->operationCounter;
}


// TODO: Can it be simplified?
// TODO: Can it be more efficient? Because it creates a new SLList and items
// are copied to the new list. Maybe implement and use
// std::forward_list::erase_after -like function.
void sllistRemoveIf(SLList *const restrict list, func predicate)
{
  SLList newList = sllistConstruct(0);
  struct Node *current = list->first;
  int operationCounter = list->operationCounter;
  bool modified = false;

  while (current)
  {
    if (predicate(&(current->item)))
    {
      modified = true;
      ++operationCounter;
    }
    else
    {
      sllistPushBack(&newList, &(current->item));
    }

    current = current->next;
  }

  if (modified)
  {
    sllistCopy(list, &newList);
    list->operationCounter = operationCounter;
  }

  sllistDestruct(&newList);
}
