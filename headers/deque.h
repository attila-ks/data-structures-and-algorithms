#ifndef DEQUE_H
#define DEQUE_H

#include <stdbool.h>

typedef int Item;


typedef struct Deque
{
  struct Node
  {
    Item item;
    struct Node *prev;
    struct Node *next;
  } *first, *last;
  int size;
  int operationCounter;
} Deque;


// TODO: It should be Random-access iterator.
typedef struct BidirectionalIterator
{
  Deque *deque;
  struct Node *current;
  // Used for comparison with deque.operationCounter field
  int currentOperationCounter;
} Iterator;


// Constructs and returns a Deque with n elements. Each element is a copy.
Deque dequeConstruct(int n, ...);
void dequeDestruct(Deque *const restrict deque);
void dequeCopy(Deque *const dest, const Deque *const src);

// Returns an Iterator pointing to the first Item in the Deque. The Iterator is
// a fail-fast one, meaning no modifier function should be called on Deque while
// using the iterator.
Iterator dequeFirst(Deque *const restrict deque);
// Returns an Iterator pointing to the last Item in the Deque. The Iterator is
// a fail-fast one, meaning no modifier function should be called on Deque while
// using the iterator.
Iterator dequeLast(Deque *const restrict deque);
bool dequeHasPrevious(const Iterator *const restrict itr);
// Returns a pointer to the previous Item. Function dequeHasPrevious should be
// tested before calling this function.
Item *dequePrevious(Iterator *const restrict itr);
bool dequeHasNext(const Iterator *const restrict itr);
// Returns a pointer to the next Item. Function dequeHasNext should be tested
// before calling this function.
Item *dequeNext(Iterator *const restrict itr);

int dequeSize(const Deque *const restrict deque);
bool dequeIsEmpty(const Deque *const restrict deque);

void dequePushFront(Deque *const restrict deque,
                    const Item *const restrict item);
void dequePushBack(Deque *const restrict deque,
                   const Item *const restrict item);
// Returns the popped Item from the beginning of the Deque. deque's size should
// be tested before calling the function.
Item dequePopFront(Deque *const restrict deque);
// Returns the popped Item from the end of the Deque. deque's size should
// be tested before calling the function.
Item dequePopBack(Deque *const restrict deque);
// Inserts item before the Item at the specified position of the Deque.
void dequeInsert(Iterator *const position, const Item *const restrict item);
// Returns the removed Item from the specified position of the Deque. Deque's
// size should be tested before calling the function.
// Updates the iterator to point to the Item that followed the Item erased by
// the function call.
Item dequeErase(Iterator *const position);

#endif // DEQUE_H
