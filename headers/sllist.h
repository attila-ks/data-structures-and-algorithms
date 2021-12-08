#ifndef SLLIST_H
#define SLLIST_H

#include <stdbool.h>

typedef int Item;


typedef struct SLList
{
  struct Node
  {
    Item item;
    struct Node *next;
  } *first, *last;
  int size;
  int operationCounter;
} SLList;


typedef struct ForwardIterator
{
  struct Node *current;
  // Points to the operationCounter field of a SLList
  const int *const operationCounterPtr;
  // Used for comparison with operationCounterPtr field
  const int currentOperationCounter;
} Iterator;


typedef bool (*func)(const Item *const restrict item);


// Constructs and returns an SLList with n elements. Each element is a copy.
SLList sllistConstruct(int n, ...);
void sllistDestruct(SLList *const restrict list);
void sllistCopy(SLList *const dest, const SLList *const src);

// Constructs and returns a fail-fast iterator, meaning no modifier function
// should be called on SLList while using the iterator.
Iterator sllistFirst(SLList *const restrict list);
Iterator sllistLast(SLList *const restrict list);
bool sllistHasNext(const Iterator *const restrict itr);
Item *sllistNext(Iterator *const restrict itr);

bool sllistIsEmpty(const SLList *const restrict list);
int sllistSize(const SLList *const restrict list);

void sllistPushFront(SLList *const restrict list,
                     const Item *const restrict item);
// Returns the popped item from the beginning of the SLList. list's size should
// be tested before calling the function.
Item sllistPopFront(SLList *const restrict list);
void sllistPushBack(SLList *const restrict list,
                    const Item *const restrict item);

// Remove elements fulfilling condition
void sllistRemoveIf(SLList *const restrict list, func predicate);

#endif // SLLIST_H
