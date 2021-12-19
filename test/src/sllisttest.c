#include "../headers/sllisttest.h"
#include "../../headers/sllist.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

static const Item itemToRemove = 3;

// Helper functions
static bool predicate(const Item *const restrict item);


void runSllistTestCase(void)
{
  testSllistConstruct();
  testSllistDestruct();
  testSllistCopy();

  testSllistFirst();
  testSllistLast();
  testSllistHasNext();
  testSllistNext();

  testSllistIsEmpty();
  testSllistSize();

  testSllistPushFront();
  testSllistPopFront();
  testSllistPushBack();

  testSllistRemoveIf();

  puts("- Singly Linked List test case ran without any error!");
}


void testSllistConstruct(void)
{
  // TODO: Test sllistConstruct with negative argument!
  // TODO: Test sllistConstruct with different number of items than ellipsis!

  // Test empty SLList construction
  SLList list = sllistConstruct(0);
  assert
  (
    list.first == NULL &&
    list.last == NULL &&
    list.size == 0 &&
    list.operationCounter == 0
  );

  // Test not empty SLList construction
  list = sllistConstruct(5, 0, 1, 2, 3, 4);
  const struct Node *current = list.first;
  for (int i = 0; i < list.size; ++i)
  {
    assert(current->item == i);
    current = current->next;
  }
  assert(current == NULL);
  assert
  (
    list.last->item == 4 &&
    list.size == 5 &&
    list.operationCounter == 5
  );

  sllistDestruct(&list);
}


void testSllistDestruct(void)
{
  // Test empty SLList destruction
  SLList list = sllistConstruct(0);
  sllistDestruct(&list);
  assert
  (
    list.first == NULL &&
    list.last == NULL &&
    list.size == 0 &&
    list.operationCounter == 0
  );

  // Test not empty SLList destruction
  list = sllistConstruct(5, 0, 1, 2, 3, 4);
  sllistDestruct(&list);
  assert
  (
    list.first == NULL &&
    list.last == NULL &&
    list.size == 0 &&
    list.operationCounter == 0
  );

  sllistDestruct(&list);
}


void testSllistCopy(void)
{
  // Test empty SLList copy into other empty SLList
  SLList src = sllistConstruct(0);
  SLList dest = sllistConstruct(0);
  sllistCopy(&dest, &src);
  assert
  (
    dest.first == NULL &&
    dest.last == NULL &&
    dest.size == 0 &&
    dest.operationCounter == 0
  );

  // Test empty SLList copy into not empty SLList
  dest = sllistConstruct(5, 0, 1, 2, 3, 4);
  sllistCopy(&dest, &src);
  assert
  (
    dest.first == NULL &&
    dest.last == NULL &&
    dest.size == 0 &&
    dest.operationCounter == 0
  );

  sllistDestruct(&dest);

  // Test not empty SLList copy into empty SLList
  src = sllistConstruct(5, 0, 1, 2, 3, 4);
  sllistCopy(&dest, &src);
  const struct Node *destCurrent = dest.first;
  for (int i = 0; i < dest.size; ++i)
  {
    assert(destCurrent->item == i);
    destCurrent = destCurrent->next;
  }
  assert(destCurrent == NULL);
  assert
  (
    dest.last->item == 4 &&
    dest.size == 5 &&
    dest.operationCounter == 5
  );

  sllistDestruct(&dest);

  // Test not empty SLList copy into other not empty SLList
  dest = sllistConstruct(5, 10, 11, 12, 13, 14);
  sllistCopy(&dest, &src);
  const struct Node *srcCurrent = src.first;
  destCurrent = dest.first;
  for (int i = 0; i < dest.size; ++i)
  {
    assert(destCurrent->item == srcCurrent->item);
    srcCurrent = srcCurrent->next;
    destCurrent = destCurrent->next;
  }
  assert(destCurrent == NULL);
  assert
  (
    dest.last->item == 4 &&
    dest.size == 5 &&
    dest.operationCounter == 5
  );

  sllistDestruct(&dest);
  sllistDestruct(&src);
}


void testSllistFirst(void)
{
  SLList list = sllistConstruct(0);
  const Iterator itr = sllistFirst(&list);
  assert
  (
    list.first == itr.current &&
    &(list.operationCounter) == itr.operationCounterPtr &&
    list.operationCounter == itr.currentOperationCounter
  );
}


void testSllistLast(void)
{
  SLList list = sllistConstruct(0);
  const Iterator itr = sllistLast(&list);
  assert
  (
    list.last == itr.current &&
    &(list.operationCounter) == itr.operationCounterPtr &&
    list.operationCounter == itr.currentOperationCounter
  );
}


void testSllistHasNext(void)
{
  // TODO: Test the iterator's fail-fast functionality

  // Test func sllistHasNext with empty SLList
  SLList list = sllistConstruct(0);
  Iterator itr = sllistFirst(&list);
  assert(sllistHasNext(&itr) == false);

  // Test func sllistHasNext with not empty SLList
  list = sllistConstruct(5, 0, 1, 2, 3, 4);
  itr = sllistFirst(&list);
  int i = 0;
  while (sllistHasNext(&itr))
  {
    sllistNext(&itr);
    ++i;
  }
  assert(i == 5);

  sllistDestruct(&list);
}


void testSllistNext(void)
{
  // TODO: Test the iterator's fail-fast functionality
  // TODO: Test func sllistNext with empty SLList

  // Test func sllistNext with not empty SLList
  SLList list = sllistConstruct(3, 0, 1, 2);
  Iterator itr = sllistFirst(&list);
  for (int i = 0; i < list.size; ++i)
  {
    const Item *const item = sllistNext(&itr);
    assert(item != NULL && *item == i);
  }
  // TODO: Test whether itr points to NULL

  sllistDestruct(&list);
}


void testSllistIsEmpty(void)
{
  // Test func sllistIsEmpty with empty SLList
  SLList list = sllistConstruct(0);
  assert(sllistIsEmpty(&list) == true);

  // Test func sllistIsEmpty with not empty SLList
  list = sllistConstruct(5, 0, 1, 2, 3, 4);
  assert(sllistIsEmpty(&list) == false);

  sllistDestruct(&list);
}


void testSllistSize(void)
{
  // Test func sllistSize with empty SLList
  SLList list = sllistConstruct(0);
  assert(sllistSize(&list) == 0);

  // Test func sllistSize with not empty SLList
  list = sllistConstruct(5, 0, 1, 2, 3, 4);
  assert(sllistSize(&list) == 5);

  sllistDestruct(&list);
}


void testSllistPushFront(void)
{
  // Test func sllistPushFront with empty SLList
  SLList list = sllistConstruct(0);
  sllistPushFront(&list, &((Item){5}));
  assert
  (
    list.first->item == 5 &&
    list.first == list.last &&
    list.last->next == NULL &&
    list.size == 1 &&
    list.operationCounter == 1
  );

  // Test func sllistPushFront with not empty SLList
  sllistPushFront(&list, &((Item){10}));
  assert
  (
    list.first->item == 10 &&
    list.first->next->item == 5 &&
    list.first->next == list.last &&
    list.last->next == NULL &&
    list.size == 2 &&
    list.operationCounter == 2
  );

  sllistDestruct(&list);
}


void testSllistPopFront(void)
{
  // TODO: Test func sllistPopFront with empty SLList

  // Test func sllistPopFront with one-Item SLList
  SLList list = sllistConstruct(1, 5);
  Item item = sllistPopFront(&list);
  assert
  (
    list.first == NULL &&
    list.last == NULL &&
    list.size == 0 &&
    item == 5 &&
    list.operationCounter == 2
  );

  sllistDestruct(&list);

  // Test func sllistPopFront with two-Items SLList
  list = sllistConstruct(2, 0, 1);
  item = sllistPopFront(&list);
  assert
  (
    list.first->item == 1 &&
    list.first == list.last &&
    list.last->next == NULL &&
    list.size == 1 &&
    list.operationCounter == 3 &&
    item == 0
  );

  sllistDestruct(&list);

  // Test func sllistPopFront with three-Items SLList
  list = sllistConstruct(3, 0, 1, 2);
  item = sllistPopFront(&list);
  assert
  (
    list.first->item == 1 &&
    list.first->next->item == 2 &&
    list.first->next == list.last &&
    list.last->next == NULL &&
    list.size == 2 &&
    list.operationCounter == 4 &&
    item == 0
  );

  sllistDestruct(&list);
}

void testSllistPushBack(void)
{
  // Test func sllistPushBack with empty SLList
  SLList list = sllistConstruct(0);
  sllistPushBack(&list, &((Item){5}));
  assert
  (
    list.first->item == 5 &&
    list.first == list.last &&
    list.last->next == NULL &&
    list.size == 1 &&
    list.operationCounter == 1
  );

  // Test func sllistPushBack with one-Items SLList
  list = sllistConstruct(1, 0);
  sllistPushBack(&list, &((Item){1}));
  assert
  (
    list.first->item == 0 &&
    list.first->next->item == 1 &&
    list.first->next == list.last &&
    list.last->next == NULL &&
    list.size == 2 &&
    list.operationCounter == 2
  );

  sllistDestruct(&list);

  // Test func sllistPushBack with two-Items SLList
  list = sllistConstruct(2, 0, 1);
  sllistPushBack(&list, &((Item){2}));
  assert
  (
    list.first->item == 0 &&
    list.first->next->item == 1 &&
    list.first->next->next->item == 2 &&
    list.first->next->next == list.last &&
    list.last->next == NULL &&
    list.size == 3 &&
    list.operationCounter == 3
  );

  sllistDestruct(&list);
}

void testSllistRemoveIf(void)
{
  // Test func sllistRemoveIf with empty SLList
  SLList list = sllistConstruct(0);
  sllistRemoveIf(&list, predicate);
  assert
  (
    list.first == NULL &&
    list.last == NULL &&
    list.size == 0 &&
    list.operationCounter == 0
  );

  // Test func sllistRemoveIf with no Item to remove in one-Item SLList
  list = sllistConstruct(1, 5);
  sllistRemoveIf(&list, predicate);
  assert
  (
    list.first->item == 5 &&
    list.first == list.last &&
    list.last->next == NULL &&
    list.size == 1 &&
    list.operationCounter == 1
  );

  sllistDestruct(&list);

  // Test func sllistRemoveIf with one Item to remove in one-Item SLList
  list = sllistConstruct(1, itemToRemove);
  sllistRemoveIf(&list, predicate);
  assert
  (
    list.first == NULL &&
    list.last == NULL &&
    list.size == 0 &&
    list.operationCounter == 2
  );

  sllistDestruct(&list);

  // Test func sllistRemoveIf with one Item to remove from beginning of a
  // two-Items SLList
  list = sllistConstruct(2, itemToRemove, 4);
  sllistRemoveIf(&list, predicate);
  assert
  (
    list.first->item == 4 &&
    list.first == list.last &&
    list.last->next == NULL &&
    list.size == 1 &&
    list.operationCounter == 3
  );

  sllistDestruct(&list);

  // Test func sllistRemoveIf with one Item to remove from end of a two-Items
  // SLList
  list = sllistConstruct(2, 4, itemToRemove);
  sllistRemoveIf(&list, predicate);
  assert
  (
    list.first->item == 4 &&
    list.first == list.last &&
    list.last->next == NULL &&
    list.size == 1 &&
    list.operationCounter == 3
  );

  sllistDestruct(&list);

  // Test func sllistRemmove with more Items to remove from SLList
  list = sllistConstruct(9, itemToRemove, 0, 1, itemToRemove, 2, 4, 5,
                         itemToRemove, itemToRemove);
  sllistRemoveIf(&list, predicate);

  const Item remainingItems[] = {0, 1, 2, 4, 5};
  const int arraySize = 5;
  struct Node *current = list.first;

  for (int i = 0; i < arraySize; ++i)
  {
    assert(current != NULL);
    assert(current->item == remainingItems[i]);
    current = current->next;
  }
  assert(current == NULL && list.size == arraySize);

  sllistDestruct(&list);
}


bool predicate(const Item *const restrict item)
{
  return *item == itemToRemove;
}
