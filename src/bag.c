#include "../headers/bag.h"
#include <assert.h>
#include <stdarg.h>
#include <stdlib.h>

Bag bagConstruct(int n, ...)
{
  // TODO: Is the following assert redundant to establish an invariant?
  assert(n >= 0);

  Bag bag = {.first = NULL, .size = 0};
  va_list initList;
  va_start(initList, n);

  for (int i = 0; i < n; ++i)
  {
    const Item item = va_arg(initList, Item);
    bagAdd(&bag, &item);
  }

  va_end(initList);
  return bag;
}


void bagDestruct(Bag *const restrict bag)
{
  struct Node *current = bag->first;

  while (current)
  {
    bag->first = bag->first->next;
    free(current);
    current = bag->first;
  }

  bag->size = 0;
}


void bagCopy(Bag *const dest, const Bag *const src)
{
  // TODO: Is there a faster way to copy a Bag?
  Item items[src->size];
  const struct Node *current = src->first;

  for (int i = 0; i < src->size; ++i)
  {
    items[i] = current->item;
    current = current->next;
  }

  bagDestruct(dest);

  for (int i = src->size - 1; i >= 0; --i)
  {
    bagAdd(dest, &(items[i]));
  }
}


Iterator bagIterator(Bag *const restrict bag)
{
  return (Iterator){.current = bag->first};
}


bool bagHasNext(Iterator *const restrict itr)
{
  return itr->current != NULL;
}


// Returns a pointer to the next Item. Function bagHasNext should be tested
// before calling this function.
Item *bagNext(Iterator *const restrict itr)
{
  assert(itr->current != NULL);

  Item *item = &(itr->current->item);
  itr->current = itr->current->next;
  return item;
}


bool bagIsEmpty(const Bag *const restrict bag)
{
  return bag->size == 0;
}


int bagSize(const Bag *const restrict bag)
{
  return bag->size;
}


void bagAdd(Bag *const restrict bag, const Item *const restrict item)
{
  struct Node *oldFirst = bag->first;
  bag->first = (struct Node *)malloc(sizeof(struct Node));
  bag->first->item = *item;
  bag->first->next = oldFirst;
  ++(bag->size);
}
