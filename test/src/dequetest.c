#include "../headers/dequetest.h"
#include "../../headers/deque.h"
#include <assert.h>
#include <stdio.h>

void runDequeTestCase(void)
{
  testDequeConstruct();
  testDequeDestruct();
  testDequeCopy();

  testDequeFirst();
  testDequeLast();
  testDequeHasPrevious();
  testDequePrevious();
  testDequeHasNext();
  testDequeNext();

  testDequeSize();
  testDequeIsEmpty();

  testDequePushFront();
  testDequePushBack();
  testDequePopFront();
  testDequePopBack();
  testDequeInsert();
  testDequeErase();

  puts("- Double-ended Queue test case ran without any error!");
}


static void testDequeConstruct(void)
{
  // TODO: Test dequeConstruct with negative argument!
  // TODO: Test dequeConstruct with different number of items than ellipsis!

  // Test func dequeConstruct with empty Deque construction
  Deque deque = dequeConstruct(0);
  assert
  (
    deque.first == NULL &&
    deque.last == NULL &&
    deque.size == 0 &&
    deque.operationCounter == 0
  );

  // Test func dequeConstruct with one-Item Deque construction
  deque = dequeConstruct(1, 5);
  assert
  (
    deque.first->item == 5 &&
    deque.first->prev == NULL &&
    deque.first->next == NULL &&
    deque.first == deque.last &&
    deque.size == 1 &&
    deque.operationCounter == 1
  );

  dequeDestruct(&deque);

  // Test func dequeConstruct with multi-Item Deque construction
  deque = dequeConstruct(2, 5, 6);
  assert
  (
    deque.first->item == 5 &&
    deque.first->prev == NULL &&
    deque.first->next == deque.last &&
    deque.last->prev == deque.first &&
    deque.last->next == NULL &&
    deque.size == 2 &&
    deque.operationCounter == 2
  );

  dequeDestruct(&deque);
}


static void testDequeDestruct(void)
{
  // Test func dequeDestruct with empty Deque destruction
  Deque deque = dequeConstruct(0);
  dequeDestruct(&deque);
  assert
  (
    deque.first == NULL &&
    deque.last == NULL &&
    deque.size == 0 &&
    deque.operationCounter == 0
  );

  // Test func dequeDestruct with not empty Deque destruction
  deque = dequeConstruct(5, 0, 1, 2, 3, 4);
  dequeDestruct(&deque);
  assert
  (
    deque.first == NULL &&
    deque.last == NULL &&
    deque.size == 0 &&
    deque.operationCounter == 0
  );
}


static void testDequeCopy(void)
{
  // TODO: Should be tested if the source Deque is modified?

  // Test func dequeCopy to copy empty Deque into empty Deque
  Deque src = dequeConstruct(0);
  Deque dest = dequeConstruct(0);
  dequeCopy(&dest, &src);
  assert
  (
    dest.first == NULL &&
    dest.last == NULL &&
    dest.size == 0 &&
    dest.operationCounter == 0
  );

  // Test func dequeCopy to copy empty Deque into not empty Deque
  dest = dequeConstruct(5, 0, 1, 2, 3, 4);
  dequeCopy(&dest, &src);
  assert
  (
    dest.first == NULL &&
    dest.last == NULL &&
    dest.size == 0 &&
    dest.operationCounter == 0
  );

  // Test func dequeCopy to copy not empty Deque into empty Deque
  src = dequeConstruct(5, 0, 1, 2, 3, 4);
  dequeCopy(&dest, &src);
  const struct Node *current = dest.first;
  for (int i = 0; i < 5; ++i)
  {
    assert(current->item == i);
    current = current->next;
  }
  assert
  (
    dest.first->prev == NULL &&
    dest.last->next == NULL &&
    dest.size == 5 &&
    dest.operationCounter == 5
  );

  dequeDestruct(&dest);

  // Test func dequeCopy to copy not empty Deque into not empty Deque
  dest = dequeConstruct(3, 10, 20, 30);
  dequeCopy(&dest, &src);
  current = dest.first;
  for (int i = 0; i < 5; ++i)
  {
    assert(current->item == i);
    current = current->next;
  }
  assert
  (
    dest.first->prev == NULL &&
    dest.last->next == NULL &&
    dest.size == 5 &&
    dest.operationCounter == 5
  );

  dequeDestruct(&src);
  dequeDestruct(&dest);
}


static void testDequeFirst(void)
{
  // Test func dequeFirst with one-Item Deque
  Deque deque = dequeConstruct(1, 5);
  Iterator itr = dequeFirst(&deque);
  assert
  (
    itr.deque == &deque &&
    itr.current == deque.first &&
    itr.currentOperationCounter == deque.operationCounter
  );

  dequeDestruct(&deque);
}


static void testDequeLast(void)
{
  // Test func dequeLast with one-Item Deque
  Deque deque = dequeConstruct(1, 5);
  Iterator itr = dequeLast(&deque);
  assert
  (
    itr.deque == &deque &&
    itr.current == deque.first &&
    itr.currentOperationCounter == deque.operationCounter
  );

  dequeDestruct(&deque);
}


static void testDequeHasPrevious(void)
{
  // TODO: Test the iterator's fail-fast functionality

  // Test func dequeHasPrevious with multi-Item Deque
  Deque deque = dequeConstruct(5, 0, 1, 2, 3, 4);
  Iterator itr = dequeLast(&deque);
  int i = 0;
  while (dequeHasPrevious(&itr))
  {
    dequePrevious(&itr);
    ++i;
  }
  assert(i == 5 && dequeHasPrevious(&itr) == false);

  dequeDestruct(&deque);
}


static void testDequePrevious(void)
{
  // TODO: Test the iterator's fail-fast functionality

  // Test func dequePrevious with not empty Deque
  Deque deque = dequeConstruct(5, 0, 1, 2, 3, 4);
  Iterator itr = dequeLast(&deque);
  for (int i = 4; i >= 0; --i)
  {
    const Item *const item = dequePrevious(&itr);
    assert(*item == i);
  }

  dequeDestruct(&deque);
}


static void testDequeHasNext(void)
{
  // TODO: Test the iterator's fail-fast functionality

  // Test func dequeHasNext with multi-Item Deque
  Deque deque = dequeConstruct(5, 0, 1, 2, 3, 4);
  Iterator itr = dequeFirst(&deque);
  int i = 0;
  while (dequeHasNext(&itr))
  {
    dequeNext(&itr);
    ++i;
  }
  assert(i == 5 && dequeHasNext(&itr) == false);

  dequeDestruct(&deque);
}


static void testDequeNext(void)
{
  // TODO: Test the iterator's fail-fast functionality

  // Test func dequeNext with not empty Deque
  Deque deque = dequeConstruct(5, 0, 1, 2, 3, 4);
  Iterator itr = dequeFirst(&deque);
  for (int i = 0; i < 5; ++i)
  {
    const Item *const item = dequeNext(&itr);
    assert(*item == i);
  }

  dequeDestruct(&deque);
}


static void testDequeSize(void)
{
  // Test func dequeSize with empty Deque
  Deque deque = dequeConstruct(0);
  assert(dequeSize(&deque) == 0);

  // Test func dequeSize with multi-Item Deque
  deque = dequeConstruct(5, 0, 1, 2, 3, 4);
  assert(dequeSize(&deque) == 5);

  dequeDestruct(&deque);
}


static void testDequeIsEmpty(void)
{
  // Test func dequeIsEmpty with empty Deque
  Deque deque = dequeConstruct(0);
  assert(dequeIsEmpty(&deque) == true);

  // Test func dequeIsEmpty with not empty Deque
  deque = dequeConstruct(5, 0, 1, 2, 3, 4);
  assert(dequeIsEmpty(&deque) == false);

  dequeDestruct(&deque);
}


static void testDequePushFront(void)
{
  // Test func dequePushFront with empty Deque
  Deque deque = dequeConstruct(0);
  dequePushFront(&deque, &((Item){5}));
  assert
  (
    deque.first->item == 5 &&
    deque.first->prev == NULL &&
    deque.first->next == NULL &&
    deque.first == deque.last &&
    deque.size == 1 &&
    deque.operationCounter == 1
  );

  // Test func dequePushFront with not empty Deque
  dequePushFront(&deque, &((Item){10}));
  assert
  (
    deque.first->item == 10 &&
    deque.first->prev == NULL &&
    deque.first->next == deque.last &&
    deque.last->item == 5 &&
    deque.last->prev == deque.first &&
    deque.last->next == NULL &&
    deque.size == 2 &&
    deque.operationCounter == 2
  );

  dequeDestruct(&deque);
}


static void testDequePushBack(void)
{
  // Test func dequePushBack with empty Deque
  Deque deque = dequeConstruct(0);
  dequePushBack(&deque, &((Item){5}));
  assert
  (
    deque.first->item == 5 &&
    deque.first->prev == NULL &&
    deque.first->next == NULL &&
    deque.first == deque.last &&
    deque.size == 1 &&
    deque.operationCounter == 1
  );

  // Test func dequePushBack with not empty Deque
  dequePushBack(&deque, &((Item){10}));
  assert
  (
    deque.first->item == 5 &&
    deque.first->prev == NULL &&
    deque.first->next == deque.last &&
    deque.last->item == 10 &&
    deque.last->prev == deque.first &&
    deque.last->next == NULL &&
    deque.size == 2 &&
    deque.operationCounter == 2
  );

  dequeDestruct(&deque);
}


static void testDequePopFront(void)
{
  // TODO: Test func dequePopFront with empty Deque

  // Test func dequePopFront with one-Item Deque
  Deque deque = dequeConstruct(1, 5);
  Item item = dequePopFront(&deque);
  assert
  (
    deque.first == NULL &&
    deque.last == NULL &&
    deque.size == 0 &&
    deque.operationCounter == 2 &&
    item == 5
  );

  // Test func dequePopFront with two-Items Deque
  deque = dequeConstruct(2, 5, 6);
  item = dequePopFront(&deque);
  assert
  (
    deque.first->item == 6 &&
    deque.first->prev == NULL &&
    deque.first->next == NULL &&
    deque.first == deque.last &&
    deque.size == 1 &&
    deque.operationCounter == 3 &&
    item == 5
  );

  dequeDestruct(&deque);

  // Test func dequePopFront with three-Items Deque
  deque = dequeConstruct(3, 5, 6, 7);
  item = dequePopFront(&deque);
  assert
  (
    deque.first->item == 6 &&
    deque.first->prev == NULL &&
    deque.first->next == deque.last &&
    deque.last->item == 7 &&
    deque.last->prev == deque.first &&
    deque.last->next == NULL &&
    deque.size == 2 &&
    deque.operationCounter == 4 &&
    item == 5
  );

  dequeDestruct(&deque);
}


static void testDequePopBack(void)
{
  // TODO: Test func dequePopBack with empty Deque

  // Test func dequePopBack with one-Item Deque
  Deque deque = dequeConstruct(1, 5);
  Item item = dequePopBack(&deque);
  assert
  (
    deque.first == NULL &&
    deque.last == NULL &&
    deque.size == 0 &&
    deque.operationCounter == 2 &&
    item == 5
  );

  // Test func dequePopBack with two-Items Deque
  deque = dequeConstruct(2, 5, 6);
  item = dequePopBack(&deque);
  assert
  (
    deque.first->item == 5 &&
    deque.first->prev == NULL &&
    deque.first->next == NULL &&
    deque.first == deque.last &&
    deque.size == 1 &&
    deque.operationCounter == 3 &&
    item == 6
  );

  dequeDestruct(&deque);

  // Test func dequePopBack with three-Items Deque
  deque = dequeConstruct(3, 5, 6, 7);
  item = dequePopBack(&deque);
  assert
  (
    deque.first->item == 5 &&
    deque.first->prev == NULL &&
    deque.first->next == deque.last &&
    deque.last->item == 6 &&
    deque.last->prev == deque.first &&
    deque.last->next == NULL &&
    deque.size == 2 &&
    deque.operationCounter == 4 &&
    item == 7
  );

  dequeDestruct(&deque);
}


static void testDequeInsert(void)
{
  // Test func dequeInsert with empty Deque
  Deque deque = dequeConstruct(0);
  Iterator itr = dequeFirst(&deque);
  dequeInsert(&itr, &((Item){6}));
  assert
  (
    deque.first->item == 6 &&
    deque.first->prev == NULL &&
    deque.first->next == NULL &&
    deque.first == deque.last &&
    deque.size == 1 &&
    deque.operationCounter == 1
  );

  // Test func dequeInsert to insert before the first Item of the one-Item
  // Deque which is also the last Item
  itr = dequeFirst(&deque);
  dequeInsert(&itr, &((Item){4}));
  assert
  (
    deque.first->item == 4 &&
    deque.first->prev == NULL &&
    deque.first->next == deque.last &&
    deque.last->item == 6 &&
    deque.last->prev == deque.first &&
    deque.last->next == NULL &&
    deque.size == 2 &&
    deque.operationCounter == 2
  );

  // Test func dequeInsert to insert in the middle of the Deque
  itr = dequeLast(&deque);
  dequeInsert(&itr, &((Item){5}));
  assert
  (
    deque.first->item == 4 &&
    deque.first->prev == NULL &&
    deque.first->next->item == 5 &&
    deque.first->next->prev == deque.first &&
    deque.first->next->next == deque.last &&
    deque.last->prev == deque.first->next &&
    deque.last->next == NULL &&
    deque.size == 3 &&
    deque.operationCounter == 3
  );

  dequeDestruct(&deque);
}


static void testDequeErase(void)
{
  // TODO: Test func dequeErase with empty Deque

  // Test func dequeErase to erase the first Item of the one-Item Deque
  // which is also the last Item
  Deque deque = dequeConstruct(1, 5);
  Iterator itr = dequeFirst(&deque);
  Item item = dequeErase(&itr);
  assert
  (
    deque.first == NULL &&
    deque.last == NULL &&
    deque.size == 0 &&
    deque.operationCounter == 2 &&
    item == 5
  );

  // Test func dequeErase to erase the first Item from a two-Items Deque
  deque = dequeConstruct(2, 5, 6);
  itr = dequeFirst(&deque);
  item = dequeErase(&itr);
  assert
  (
    deque.first->item == 6 &&
    deque.first->prev == NULL &&
    deque.first->next == NULL &&
    deque.first == deque.last &&
    deque.size == 1 &&
    deque.operationCounter == 3 &&
    item == 5
  );

  dequeDestruct(&deque);

  // Test func dequeErase to erase the last Item from a two-Items Deque
  deque = dequeConstruct(2, 5, 6);
  itr = dequeLast(&deque);
  item = dequeErase(&itr);
  assert
  (
    deque.first->item == 5 &&
    deque.first->prev == NULL &&
    deque.first->next == NULL &&
    deque.first == deque.last &&
    deque.size == 1 &&
    deque.operationCounter == 3 &&
    item == 6
  );

  dequeDestruct(&deque);

  // Test func dequeErase to erase from the middle of the Deque
  deque = dequeConstruct(3, 0, 1, 2);
  itr = dequeFirst(&deque);
  dequeNext(&itr);
  item = dequeErase(&itr);
  assert
  (
    deque.first->item == 0 &&
    deque.first->prev == NULL &&
    deque.first->next == deque.last &&
    deque.last->item == 2 &&
    deque.last->prev == deque.first &&
    deque.last->next == NULL &&
    deque.size == 2 &&
    deque.operationCounter == 4 &&
    item == 1
  );

  dequeDestruct(&deque);
}
