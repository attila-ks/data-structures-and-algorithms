#ifndef DLLIST_H
#define DLLIST_H

#include <stdbool.h>

typedef int Item;


typedef struct DLList
{
  struct Node
  {
    Item item;
    struct Node *prev;
    struct Node *next;
  } *first, *last;
  int size;
  int operationCounter;
} DLList;


typedef struct BidirectionalIterator
{
  DLList *list;
  struct Node *current;
  // Used for comparison with list.operationCounter field
  int currentOperationCounter;
} Iterator;


typedef bool (*func)(const Item *const restrict item);


// Constructs and returns an DLList with n elements. Each element is a copy.
DLList dllistConstruct(int n, ...);
void dllistDestruct(DLList *const restrict list);
void dllistCopy(DLList *const dest, const DLList *const src);

// Constructs and returns a fail-fast iterator, meaning no modifier function
// should be called on DLList while using the iterator.
Iterator dllistFirst(DLList *const restrict list);
Iterator dllistLast(DLList *const restrict list);
bool dllistHasPrevious(const Iterator *const restrict itr);
bool dllistHasNext(const Iterator *const restrict itr);
// Returns a pointer to the previous Item. Function dllistHasPrevious should be
// tested before calling this function.
Item *dllistPrevious(Iterator *const restrict itr);
// Returns a pointer to the next Item. Function dllistHasNext should be tested
// before calling this function.
Item *dllistNext(Iterator *const restrict itr);

bool dllistIsEmpty(const DLList *const restrict list);
int dllistSize(const DLList *const restrict list);

void dllistPushFront(DLList *const restrict list,
                     const Item *const restrict item);
// Returns the popped Item from the beginning of the DLList. list's size should
// be tested before calling the function.
Item dllistPopFront(DLList *const restrict list);
void dllistPushBack(DLList *const restrict list,
                    const Item *const restrict item);
// Returns the popped Item from the end of the DLList. list's size should
// be tested before calling the function.
Item dllistPopBack(DLList *const restrict list);
// Inserts item before the Item at the specified position of the DLList.
void dllistInsert(Iterator *const position, const Item *const restrict item);
// Returns the removed Item from the specified position of the DLList. DLList's
// size should be tested before calling the function.
// Updates the iterator to point to the Item that followed the Item erased by
// the function call.
Item dllistErase(Iterator *const position);

// Remove elements fulfilling condition
void dllistRemoveIf(DLList *const restrict list, func predicate);

#endif // DLLIST_H
