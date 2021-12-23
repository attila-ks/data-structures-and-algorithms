#include "../headers/queue.h"
#include <assert.h>
#include <stdarg.h>
#include <stdlib.h>

Queue queueConstruct(int n, ...)
{
  // TODO: Is the following assert redundant to establish an invariant?
  assert(n >= 0);

  Queue queue = {.first = NULL, .last = NULL, .size = 0, .operationCounter = 0};
  va_list initList;
  va_start(initList, n);

  for (int i = 0; i < n; ++i)
  {
    const Item item = va_arg(initList, Item);
    queueEnqueue(&queue, &item);
  }

  va_end(initList);
  return queue;
}


void queueDestruct(Queue *const restrict queue)
{
  struct Node *current = queue->first;

  while (current)
  {
    queue->first = queue->first->next;
    free(current);
    current = queue->first;
  }

  queue->last = NULL;
  queue->size = 0;
  queue->operationCounter = 0;
}


void queueCopy(Queue *const dest, const Queue *const src)
{
  queueDestruct(dest);

  const struct Node *current = src->first;

  while (current)
  {
    queueEnqueue(dest, &(current->item));
    current = current->next;
  }
}


Iterator queueFirst(Queue *const restrict queue)
{
  return (Iterator)
  {
    .current = queue->first,
    .queue = queue,
    .currentOperationCounter = queue->operationCounter
  };
}


Iterator queueLast(Queue *const restrict queue)
{
  return (Iterator)
  {
    .current = queue->last,
    .queue = queue,
    .currentOperationCounter = queue->operationCounter
  };
}


bool queueHasNext(const Iterator *const restrict itr)
{
  assert(itr->currentOperationCounter == itr->queue->operationCounter);
  return itr->current != NULL;
}


Item *queueNext(Iterator *const restrict itr)
{
  assert
  (
    itr->currentOperationCounter == itr->queue->operationCounter &&
    itr->current != NULL
  );

  Item *item = &(itr->current->item);
  itr->current = itr->current->next;
  return item;
}


bool queueIsEmpty(const Queue *const restrict queue)
{
  return queue->size == 0;
}


int queueSize(const Queue *const restrict queue)
{
  return queue->size;
}


void queueEnqueue(Queue *const restrict queue, const Item *const restrict item)
{
  struct Node *oldLast = queue->last;
  // TODO: Test against memory allocation failure!
  queue->last = (struct Node *)malloc(sizeof(struct Node));
  queue->last->item = *item;
  queue->last->next = NULL;

  if (queue->size == 0)
  {
    queue->first = queue->last;
  }
  else
  {
    oldLast->next = queue->last;
  }

  ++(queue->size);
  ++(queue->operationCounter);
}


Item queueDequeue(Queue *const restrict queue)
{
  assert(queue->size >= 0);

  const Item item = queue->first->item;
  struct Node *oldFirst = queue->first;
  queue->first = queue->first->next;
  free(oldFirst);

  --(queue->size);
  ++(queue->operationCounter);

  if (queue->size == 0)
  {
    queue->last = NULL;
  }

  return item;
}
