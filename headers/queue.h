#ifndef QUEUE_H
#define QUEUE_H

#include <stdbool.h>

typedef int Item;


typedef struct Queue
{
  struct Node
  {
    Item item;
    struct Node *next;
  } *first, *last;

  int size;
  int operationCounter;
} Queue;


typedef struct ForwardIterator
{
  struct Node *current;
  Queue *queue;
  // Used for comparison with queue.operationCounter field
  int currentOperationCounter;
} Iterator;


// Constructs and returns an Queue with n elements. Each element is a copy.
Queue queueConstruct(int n, ...);
void queueDestruct(Queue *const restrict queue);
void queueCopy(Queue *const dest, const Queue *const src);

// Returns an Iterator pointing to the first Item in the Queue. The Iterator is
// a fail-fast one, meaning no modifier function should be called on Queue while
// using the iterator.
Iterator queueFirst(Queue *const restrict queue);
// Returns an Iterator pointing to the last Item in the Queue. The Iterator is
// a fail-fast one, meaning no modifier function should be called on Queue while
// using the iterator.
Iterator queueLast(Queue *const restrict queue);
bool queueHasNext(const Iterator *const restrict itr);
// Returns a pointer to the next Item. Function queueHasNext should be tested
// before calling this function.
Item *queueNext(Iterator *const restrict itr);

bool queueIsEmpty(const Queue *const restrict queue);
int queueSize(const Queue *const restrict queue);

void queueEnqueue(Queue *const restrict queue, const Item *const restrict item);
// Removes and returns the oldest Item from the Queue. Function queueHasNext
// should be tested before calling this function.
Item queueDequeue(Queue *const restrict queue);

#endif // QUEUE_H
