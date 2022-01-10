#include "../headers/queuetest.h"
#include "../../headers/queue.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

void runQueueTestCase(void)
{
  testQueueConstruct();
  testQueueDestruct();
  testQueueCopy();

  testQueueFirst();
  testQueueLast();
  testQueueHasNext();
  testQueueNext();

  testQueueIsEmpty();
  testQueueSize();

  testQueueEnqueue();
  testQueueDequeue();

  puts("- Queue test case ran without any error!");
}


void testQueueConstruct(void)
{
  // TODO: Test queueConstruct with negative argument!
  // TODO: Test queueConstruct with different number of items than ellipsis!

  // Test func queueConstruct to construct an empty Queue
  Queue queue = queueConstruct(0);
  assert
  (
    queue.first == NULL &&
    queue.last == NULL &&
    queue.size == 0 &&
    queue.operationCounter == 0
  );

  // Test func queueConstruct to construct a multi-Item Queue
  queue = queueConstruct(4, 0, 1, 2, 3);
  const struct Node *current = queue.first;
  for (int i = 0; i < 4; ++i)
  {
    assert(current->item == i);
    current = current->next;
  }
  assert(current == NULL);
  assert(queue.size == 4 && queue.operationCounter == 4);

  queueDestruct(&queue);
}


void testQueueDestruct(void)
{
  // Test func queueDestruct to destruct an empty Queue
  Queue queue = queueConstruct(0);
  queueDestruct(&queue);
  assert
  (
    queue.first == NULL &&
    queue.last == NULL &&
    queue.size == 0 &&
    queue.operationCounter == 0
  );

  // Test func queueDestruct to destruct a multi-Item Queue
  queue = queueConstruct(4, 0, 1, 2, 3);
  queueDestruct(&queue);
  assert
  (
    queue.first == NULL &&
    queue.last == NULL &&
    queue.size == 0 &&
    queue.operationCounter == 0
  );

}


void testQueueCopy(void)
{
  // Test func queueCopy to copy empty Queue into other empty Queue
  Queue src = queueConstruct(0);
  Queue dest = queueConstruct(0);
  queueCopy(&dest, &src);
  assert
  (
    dest.first == NULL &&
    dest.last == NULL &&
    dest.size == 0 &&
    dest.operationCounter == 0
  );

  // Test func queueCopy to copy empty Queue into a multi-Item Queue
  dest = queueConstruct(4, 0, 1, 2, 3);
  queueCopy(&dest, &src);
  assert
  (
    dest.first == NULL &&
    dest.last == NULL &&
    dest.size == 0 &&
    dest.operationCounter == 0
  );

  queueDestruct(&dest);

  // Test func queueCopy to copy a multi-Item Queue into empty Queue
  src = queueConstruct(4, 0, 1, 2, 3);
  queueCopy(&dest, &src);
  struct Node *current = dest.first;
  for (int i = 0; i < 4; ++i)
  {
    assert(current->item == i);
    current = current->next;
  }
  assert(current == NULL);
  assert(dest.size == 4 && dest.operationCounter == 4);

  queueDestruct(&dest);

  // Test func queueCopy to copy a multi-Item Queue into a multi-Item Queue
  dest = queueConstruct(5, 0, 10, 20, 30, 40);
  queueCopy(&dest, &src);
  current = dest.first;
  for (int i = 0; i < 4; ++i)
  {
    assert(current->item == i);
    current = current->next;
  }
  assert(current == NULL);
  assert(dest.size == 4 && dest.operationCounter == 4);

  queueDestruct(&src);
  queueDestruct(&dest);
}


void testQueueFirst(void)
{
  // Test func queueFirst with one-Item Queue
  Queue queue = queueConstruct(1, 5);
  Iterator itr = queueFirst(&queue);
  assert
  (
    itr.current == queue.first &&
    itr.queue == &queue &&
    itr.currentOperationCounter == queue.operationCounter
  );

  queueDestruct(&queue);
}


void testQueueLast(void)
{
  // Test func queueLast with one-Item Queue
  Queue queue = queueConstruct(1, 5);
  Iterator itr = queueLast(&queue);
  assert
  (
    itr.current == queue.last &&
    itr.queue == &queue &&
    itr.currentOperationCounter == queue.operationCounter
  );

  queueDestruct(&queue);
}


void testQueueHasNext(void)
{
  // TODO: Test the iterator's fail-fast functionality

  // Test func queueHasNext with empty Queue
  Queue queue = queueConstruct(0);
  Iterator itr = queueFirst(&queue);
  assert(queueHasNext(&itr) == false);

  // Test func queueHasNext with multi-Item Queue
  queue = queueConstruct(4, 0, 1, 2, 3);
  itr = queueFirst(&queue);
  int i = 0;
  while (queueHasNext(&itr))
  {
    queueNext(&itr);
    ++i;
  }
  assert(i == 4);

  queueDestruct(&queue);
}


void testQueueNext(void)
{
  // TODO: Test the iterator's fail-fast functionality
  // TODO: Test func queueNext with empty Queue

  // Test func queueNext with multi-Item Queue
  Queue queue = queueConstruct(4, 0, 1, 2, 3);
  Iterator itr = queueFirst(&queue);
  for (int i = 0; i < 4; ++i)
  {
    const Item *const item = queueNext(&itr);
    assert(*item == i);
  }

  queueDestruct(&queue);

  // TODO: Test whether itr points to NULL
}


void testQueueIsEmpty(void)
{
  // Test func queueIsEmpty with empty Queue
  Queue queue = queueConstruct(0);
  assert(queueIsEmpty(&queue) == true);

  // Test func queueIsEmpty with multi-Item Queue
  queue = queueConstruct(3, 0, 1, 2);
  assert(queueIsEmpty(&queue) == false);

  queueDestruct(&queue);
}


void testQueueSize(void)
{
  // Test func queueSize with empty Queue
  Queue queue = queueConstruct(0);
  assert(queueSize(&queue) == 0);

  // Test func queueSize with multi-Item Queue
  queue = queueConstruct(3, 0, 1, 2);
  assert(queueSize(&queue) == 3);

  queueDestruct(&queue);
}


void testQueueEnqueue(void)
{
  // Test func queueEnqueue with empty Queue
  Queue queue = queueConstruct(0);
  queueEnqueue(&queue, &((Item){5}));
  assert
  (
    queue.last->item == 5 &&
    queue.first == queue.last &&
    queue.last->next == NULL &&
    queue.size == 1 &&
    queue.operationCounter == 1
  );

  // Test func queueEnqueue with one-Item Queue
  queueEnqueue(&queue, &((Item){10}));
  assert
  (
    queue.first->item == 5 &&
    queue.last->item == 10 &&
    queue.first->next == queue.last &&
    queue.last->next == NULL &&
    queue.size == 2 &&
    queue.operationCounter == 2
  );

  queueDestruct(&queue);
}


void testQueueDequeue(void)
{
  // TODO: Test func queueDequeue with empty Queue

  // Test func queueDequeue with multi-Item Queue
  int size = 4;
  Queue queue = queueConstruct(size, 0, 1, 2, 3);
  int operationCounter = 4;

  for (int i = 0; i < 4; ++i)
  {
    const Item item = queueDequeue(&queue);
    --size;
    ++operationCounter;

    assert(item == i);
    assert(queue.size == size && queue.operationCounter == operationCounter);
  }

  assert(queue.first == NULL && queue.last == NULL);

  queueDestruct(&queue);
}
