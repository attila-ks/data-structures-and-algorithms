#include "../headers/stequetest.h"
#include "../../headers/steque.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

void runStequeTestCase(void)
{
  testStequeConstruct();
  testStequeDestruct();
  testStequeCopy();

  testStequeFirst();
  testStequeLast();
  testStequeHasNext();
  testStequeNext();

  testStequeIsEmpty();
  testStequeSize();

  testStequeTop();

  testStequePush();
  testStequeEnqueue();
  testStequePop();

  puts("- Stack-ended Queue test case ran without any error!");
}


static void testStequeConstruct(void)
{
  // TODO: Test stequeConstruct with negative argument!
  // TODO: Test stequeConstruct with different number of items than ellipsis!

  // Test func stequeConstruct to construct an empty Steque using stequePush
  // function.
  Steque steque = stequeConstruct(true, 0);

  assert
  (
    steque.first == NULL &&
    steque.last == NULL &&
    steque.size == 0 &&
    steque.operationCounter == 0
  );

  // Test func stequeConstruct to construct an empty Steque using stequeEnqueue
  // function.
  steque = stequeConstruct(false, 0);

  assert
  (
    steque.first == NULL &&
    steque.last == NULL &&
    steque.size == 0 &&
    steque.operationCounter == 0
  );

  // Test func stequeConstruct to construct a multi-Item Steque using stequePush
  // function.
  steque = stequeConstruct(true, 4, 0, 1, 2, 3);
  assert(steque.size == 4 && steque.operationCounter == 4);
  const struct Node *current = steque.first;
  for (int i = 3; i >= 0; --i)
  {
    assert(current->item == i);
    current = current->next;
  }
  assert(current == NULL);

  stequeDestruct(&steque);

  // Test func stequeConstruct to construct a multi-Item Steque using
  // stequeEnqueue function.
  steque = stequeConstruct(false, 4, 0, 1, 2, 3);
  assert(steque.size == 4 && steque.operationCounter == 4);
  current = steque.first;
  for (int i = 0; i < 4; ++i)
  {
    assert(current->item == i);
    current = current->next;
  }
  assert(current == NULL);

  stequeDestruct(&steque);
}


static void testStequeDestruct(void)
{
  // Test func stequeDestruct to destruct an empty Steque
  Steque steque = stequeConstruct(true, 0);
  stequeDestruct(&steque);
  assert
  (
    steque.first == NULL &&
    steque.last == NULL &&
    steque.size == 0 &&
    steque.operationCounter == 0
  );

  // Test func stequeDestruct to destruct a multi-Item Steque
  steque = stequeConstruct(true, 4, 0, 1, 2, 3);
  stequeDestruct(&steque);
  assert
  (
    steque.first == NULL &&
    steque.last == NULL &&
    steque.size == 0 &&
    steque.operationCounter == 0
  );

  stequeDestruct(&steque);
}


static void testStequeCopy(void)
{
  // Test func stequeCopy to copy empty Steque into other empty Steque
  Steque src = stequeConstruct(true, 0);
  Steque dest = stequeConstruct(true, 0);
  stequeCopy(&dest, &src);
  assert
  (
    dest.first == NULL &&
    dest.last == NULL &&
    dest.size == 0 &&
    dest.operationCounter == 0
  );

  // Test func stequeCopy to copy empty Steque into a multi-Item Steque
  dest = stequeConstruct(true, 4, 0, 1, 2, 3);
  stequeCopy(&dest, &src);
  assert
  (
    dest.first == NULL &&
    dest.last == NULL &&
    dest.size == 0 &&
    dest.operationCounter == 0
  );

  // Test func stequeCopy to copy a multi-Item Steque into empty Steque
  src = stequeConstruct(false, 4, 0, 1, 2, 3);
  stequeCopy(&dest, &src);
  assert(dest.size == 4 && dest.operationCounter == 4);
  struct Node *current = dest.first;
  for (int i = 0; i < 4; ++i)
  {
    assert(current->item == i);
    current = current->next;
  }
  assert(current == NULL);

  stequeDestruct(&dest);

  // Test func stequeCopy to copy a multi-Item Steque into a multi-Item Steque
  dest = stequeConstruct(false, 5, 0, 10, 20, 30, 40);
  stequeCopy(&dest, &src);
  assert(dest.size == 4 && dest.operationCounter == 4);
  current = dest.first;
  for (int i = 0; i < 4; ++i)
  {
    assert(current->item == i);
    current = current->next;
  }
  assert(current == NULL);

  stequeDestruct(&src);
  stequeDestruct(&dest);
}


static void testStequeFirst(void)
{
  // Test func stequeFirst with one-Item Steque
  Steque steque = stequeConstruct(true, 1, 5);
  Iterator itr = stequeFirst(&steque);
  assert
  (
    itr.steque == &steque &&
    itr.current == steque.first &&
    itr.currentOperationCounter == steque.operationCounter
  );

  stequeDestruct(&steque);
}


static void testStequeLast(void)
{
  // Test func stequeLast with one-Item Steque
  Steque steque = stequeConstruct(true, 1, 5);
  Iterator itr = stequeLast(&steque);
  assert
  (
    itr.steque == &steque &&
    itr.current == steque.last &&
    itr.currentOperationCounter == steque.operationCounter
  );

  stequeDestruct(&steque);
}


static void testStequeHasNext(void)
{
  // TODO: Test the iterator's fail-fast functionality

  // Test func stequeHasNext with empty Steque
  Steque steque = stequeConstruct(true, 0);
  Iterator itr = stequeFirst(&steque);
  assert(stequeHasNext(&itr) == false);

  // Test func stequeHasNext with multi-Item Steque
  steque = stequeConstruct(true, 4, 0, 1, 2, 3);
  itr = stequeFirst(&steque);
  int i = 0;
  while (stequeHasNext(&itr))
  {
    stequeNext(&itr);
    ++i;
  }
  assert(i == 4);

  stequeDestruct(&steque);
}


static void testStequeNext(void)
{
  // TODO: Test the iterator's fail-fast functionality
  // TODO: Test func stequeNext with empty Steque

  // Test func stequeNext with multi-Item Steque
  Steque steque = stequeConstruct(false, 4, 0, 1, 2, 3);
  Iterator itr = stequeFirst(&steque);
  for (int i = 0; i < 4; ++i)
  {
    const Item *const item = stequeNext(&itr);
    assert(*item == i);
  }

  stequeDestruct(&steque);

  // TODO: Test whether itr points to NULL
}


static void testStequeIsEmpty(void)
{
  // Test func stequeIsEmpty with empty Steque
  Steque steque = stequeConstruct(true, 0);
  assert(stequeIsEmpty(&steque) == true);

  // Test func stequeIsEmpty with multi-Item Steque
  steque = stequeConstruct(true, 3, 0, 1, 2);
  assert(stequeIsEmpty(&steque) == false);

  stequeDestruct(&steque);
}


static void testStequeSize(void)
{
  // Test func stequeSize with empty Steque
  Steque steque = stequeConstruct(true, 0);
  assert(stequeSize(&steque) == 0);

  // Test func stequeSize with multi-Item Steque
  steque = stequeConstruct(true, 3, 0, 1, 2);
  assert(stequeSize(&steque) == 3);

  stequeDestruct(&steque);
}

static void testStequeTop(void)
{
  // TODO: Test func stequeTop with empty Steque

  // Test func stequeTop with multi-Item Steque
  Steque steque = stequeConstruct(false, 4, 0, 1, 2, 3);
  for (int i = 0; i < 4; ++i)
  {
    const Item *const item = stequeTop(&steque);
    assert(*item == i);
    stequePop(&steque);
  }
}


static void testStequePush(void)
{
  // Test func stequePush with empty Steque
  Steque steque = stequeConstruct(false, 0);
  stequePush(&steque, &((Item){5}));
  assert
  (
    steque.first->item == 5 &&
    steque.first == steque.last &&
    steque.last->next == NULL &&
    steque.size == 1 &&
    steque.operationCounter == 1
  );

  // Test func stequePush with one-Item Steque
  stequePush(&steque, &((Item){10}));
  assert
  (
    steque.first->item == 10 &&
    steque.first->next == steque.last &&
    steque.last->item == 5 &&
    steque.last->next == NULL &&
    steque.size == 2 &&
    steque.operationCounter == 2
  );

  stequeDestruct(&steque);
}


static void testStequeEnqueue(void)
{
  // Test func stequeEnqueue with empty Steque
  Steque steque = stequeConstruct(false, 0);
  stequeEnqueue(&steque, &((Item){5}));
  assert
  (
    steque.first->item == 5 &&
    steque.first == steque.last &&
    steque.last->next == NULL &&
    steque.size == 1 &&
    steque.operationCounter == 1
  );

  // Test func stequeEnqueue with one-Item Steque
  stequeEnqueue(&steque, &((Item){10}));
  assert
  (
    steque.first->item == 5 &&
    steque.first->next == steque.last &&
    steque.last->item == 10 &&
    steque.last->next == NULL &&
    steque.size == 2 &&
    steque.operationCounter == 2
  );

  stequeDestruct(&steque);
}


static void testStequePop(void)
{
  // TODO: Test func stackPop with empty Stack

  // Test func stequePop with one-Item Steque
  Steque steque = stequeConstruct(false, 1, 5);
  Item item = stequePop(&steque);
  assert(item == 5);
  assert
  (
    steque.first == NULL &&
    steque.last == NULL &&
    steque.size == 0 &&
    steque.operationCounter == 2
  );

  // Test func stequePop with two-Items Steque
  steque = stequeConstruct(false, 2, 5, 10);
  item = stequePop(&steque);
  assert(item == 5);
  assert
  (
    steque.first->item == 10 &&
    steque.first == steque.last &&
    steque.last->next == NULL &&
    steque.size == 1 &&
    steque.operationCounter == 3
  );

  stequeDestruct(&steque);
}
