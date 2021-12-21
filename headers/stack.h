#ifndef STACK_H
#define STACK_H

#include <stdbool.h>

typedef int Item;

typedef struct Stack
{
  struct Node
  {
    Item item;
    struct Node *next;
  } *first;

  int size;
  int operationCounter;
} Stack;


typedef struct ForwardIterator
{
  struct Node *current;
  // Points to the operationCounter field of a Stack
  int *operationCounterPtr;
  // Used for comparison with operationCounterPtr field
  int currentOperationCounter;
} Iterator;


// Constructs and returns an Stack with n elements. Each element is a copy.
Stack stackConstruct(int n, ...);
void stackDestruct(Stack *const restrict stack);
void stackCopy(Stack *const dest, const Stack *const src);

// Constructs and returns a fail-fast iterator, meaning no modifier function
// should be called on Stack while using the iterator.
Iterator stackFirst(Stack *const restrict stack);
bool stackHasNext(const Iterator *const restrict itr);
// Returns a pointer to the next Item. Function stackHasNext should be tested
// before calling this function.
Item *stackNext(Iterator *const restrict itr);

bool stackIsEmpty(const Stack *const restrict stack);
int stackSize(const Stack *const restrict stack);

// Returns a pointer to the top Item in the Stack. Function stackIsEmpty should
// be tested before calling this function.
Item *stackTop(Stack *const restrict stack);

void stackPush(Stack *const restrict stack, const Item *const restrict item);
// Removes the Item on top of the Stack and returns it. Function stackIsEmpty
// should be tested before calling this function.
Item stackPop(Stack *const restrict stack);

#endif // STACK_H
