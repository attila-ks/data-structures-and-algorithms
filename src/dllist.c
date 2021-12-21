#include "../headers/dllist.h"
#include <stdarg.h>
#include <stdlib.h>
#include <assert.h>

DLList dllistConstruct(int n, ...)
{
  // TODO: Is the following assert redundant to establish an invariant?
  assert(n >= 0);

  DLList list = {NULL, NULL, 0, 0};
  va_list initList;
  va_start(initList, n);

  for (int i = 0; i < n; ++i)
  {
    const Item item = va_arg(initList, Item);
    dllistPushBack(&list, &item);
  }

  va_end(initList);
  return list;
}


void dllistDestruct(DLList *const restrict list)
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


void dllistCopy(DLList *const dest, const DLList *const src)
{
  dllistDestruct(dest);

  struct Node *current = src->first;
  while (current)
  {
    dllistPushBack(dest, &(current->item));
    current = current->next;
  }
}


Iterator dllistFirst(DLList *const restrict list)
{
  return (Iterator)
  {
    list,
    list->first,
    list->operationCounter
  };
}


Iterator dllistLast(DLList *const restrict list)
{
  return (Iterator)
  {
    list,
    list->last,
    list->operationCounter
  };
}


bool dllistHasPrevious(const Iterator *const restrict itr)
{
  return dllistHasNext(itr);
}


bool dllistHasNext(const Iterator *const restrict itr)
{
  assert
  (
    itr->list->operationCounter == itr->currentOperationCounter
  );

  return itr->current != NULL;
}


Item *dllistPrevious(Iterator *const restrict itr)
{
  assert
  (
    itr->list->operationCounter == itr->currentOperationCounter
  );

  Item *item = &(itr->current->item);
  itr->current = itr->current->prev;
  return item;
}


Item *dllistNext(Iterator *const restrict itr)
{
  assert
  (
    itr->list->operationCounter == itr->currentOperationCounter
  );

  Item *item = &(itr->current->item);
  itr->current = itr->current->next;
  return item;
}


bool dllistIsEmpty(const DLList *const restrict list)
{
  return list->size == 0;
}


int dllistSize(const DLList *const restrict list)
{
  return list->size;
}


void dllistPushFront(DLList *const restrict list,
                     const Item *const restrict item)
{
  struct Node *const oldFirst = list->first;
  // TODO: Test against memory allocation failure!
  list->first = (struct Node *const)malloc(sizeof(struct Node));
  list->first->item = *item;
  list->first->prev = NULL;
  list->first->next = oldFirst;

  if (list->size == 0)
  {
    list->last = list->first;
  }
  else
  {
    oldFirst->prev = list->first;
  }

  ++list->size;
  ++list->operationCounter;
}


Item dllistPopFront(DLList *const restrict list)
{
  assert(list->size > 0);

  struct Node *const oldFirst = list->first;
  const Item item = oldFirst->item;
  list->first = list->first->next;
  free(oldFirst);

  --list->size;
  ++list->operationCounter;

  if (list->size == 0)
  {
    list->last = NULL;
  }
  else
  {
    list->first->prev = NULL;
  }

  return item;
}


void dllistPushBack(DLList *const restrict list,
                    const Item *const restrict item)
{
  struct Node *const oldLast = list->last;
  // TODO: Test against memory allocation failure!
  list->last = (struct Node *const)malloc(sizeof(struct Node));
  list->last->item = *item;
  list->last->prev = oldLast;
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


Item dllistPopBack(DLList *const restrict list)
{
  assert(list->size > 0);

  struct Node *oldLast = list->last;
  const Item item = oldLast->item;
  list->last = list->last->prev;
  free(oldLast);

  --list->size;
  ++list->operationCounter;

  if (list->size == 0)
  {
    list->first = NULL;
  }
  else
  {
    list->last->next = NULL;
  }

  return item;
}


void dllistInsert(Iterator *const position, const Item *const restrict item)
{
  if (position->list->size == 0 || position->current == position->list->first)
  {
    dllistPushFront(position->list, item);
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

    ++position->list->size;
    ++position->list->operationCounter;
  }
}


// TODO: Test whether iterator is already at the end of the list?!
Item dllistErase(Iterator *const position)
{
  assert(position->list->size > 0);

  Item item;

  if (position->current == position->list->first)
  {
    position->current = position->current->next;
    item = dllistPopFront(position->list);
  }
  else if (position->current == position->list->last)
  {
    position->current = position->current->next;
    item = dllistPopBack(position->list);
  }
  else
  {
    struct Node *const oldCurrent = position->current;
    position->current = position->current->next;
    oldCurrent->prev->next = oldCurrent->next;
    oldCurrent->next->prev = oldCurrent->prev;
    item = oldCurrent->item;
    free(oldCurrent);

    --position->list->size;
    ++position->list->operationCounter;
  }

  return item;
}


// TODO: Can it be simplified?
// TODO: Can it be more efficient? Because it creates a new DLList and items
// are copied to the new list. Maybe implement and use
// std::forward_list::erase_after -like function.
void dllistRemoveIf(DLList *const restrict list, func predicate)
{
  DLList newList = dllistConstruct(0);
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
      dllistPushBack(&newList, &(current->item));
    }

    current = current->next;
  }

  if (modified)
  {
    dllistCopy(list, &newList);
    list->operationCounter = operationCounter;
  }

  dllistDestruct(&newList);
}
