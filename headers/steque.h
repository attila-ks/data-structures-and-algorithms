#ifndef STEQUE_H
#define STEQUE_H

#include <stdbool.h>

typedef int Item;

typedef struct Steque
{
  struct Node
  {
    Item item;
    struct Node *next;
  } *first, *last;

  int size;
  int operationCounter;
} Steque;


typedef struct ForwardIterator
{
  Steque *steque;
  struct Node *current;
  // Used for comparison with steque.operationCounter field
  int currentOperationCounter;
} Iterator;

// Constructs and returns a Steque with n elements. Each element is a copy.
// The first param is used to determine which method (push or enqueue) to use.
Steque stequeConstruct(bool push, int n, ...);
void stequeDestruct(Steque *const restrict steque);
void stequeCopy(Steque *const dest, const Steque *const src);

// Returns an Iterator pointing to the first Item in the Steque. The Iterator is
// a fail-fast one, meaning no modifier function should be called on Steque
// while using the iterator.
Iterator stequeFirst(Steque *const restrict steque);
// Returns an Iterator pointing to the last Item in the Steque. The Iterator is
// a fail-fast one, meaning no modifier function should be called on Steque
// while using the iterator.
Iterator stequeLast(Steque *const restrict steque);
bool stequeHasNext(const Iterator *const restrict itr);
// Returns a pointer to the next Item. Function stequeHasNext should be tested
// before calling this function.
Item *stequeNext(Iterator *const restrict itr);

bool stequeIsEmpty(const Steque *const restrict steque);
int stequeSize(const Steque *const restrict steque);

// Returns a pointer to the top Item in the Steque. Function stequeIsEmpty
// should be tested before calling this function.
Item *stequeTop(Steque *const restrict steque);

void stequePush(Steque *const restrict steque, const Item *const restrict item);
void stequeEnqueue(Steque *const restrict steque,
                   const Item *const restrict item);
// Removes the Item on top of the Steque and returns it. Function stequeIsEmpty
// should be tested before calling this function.
Item stequePop(Steque *const restrict steque);

#endif // STEQUE_H
