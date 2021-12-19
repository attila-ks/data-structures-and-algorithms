#include "../headers/dllisttest.h"
#include "../../headers/dllist.h"
#include <assert.h>
#include <stdio.h>

static const Item itemToRemove = 3;

// Helper functions
static bool predicate(const Item *const restrict item);


void runDllistTestCase(void)
{
  TestDllistConstruct();
  TestDllistDestruct();
  TestDllistCopy();

  TestDllistFirst();
  TestDllistLast();
  TestDllistHasNext();
  TestDllistNext();

  TestDllistIsEmpty();
  TestDllistSize();

  TestDllistPushFront();
  TestDllistPopFront();
  TestDllistPushBack();
  TestDllistPopBack();
  TestDllistInsert();
  TestDllistErase();

  TestDllistRemoveIf();

  puts("- Doubly Linked List test case ran without any error!");
}


void TestDllistConstruct(void)
{
  // TODO: Test dllistConstruct with negative argument!
  // TODO: Test dllistConstruct with different number of items than ellipsis!

  // Test func dllistConstruct with empty DLList construction
  DLList list = dllistConstruct(0);
  assert
  (
    list.first == NULL &&
    list.last == NULL &&
    list.size == 0 &&
    list.operationCounter == 0
  );

  // Test func dllistConstruct with not empty DLList construction
  list = dllistConstruct(5, 0, 1, 2, 3, 4);
  const struct Node *current = list.first;
  for (int i = 0; i < list.size; ++i)
  {
    assert(current->item == i);
    current = current->next;
  }
  assert(current == NULL);
  assert
  (
    list.first->prev == NULL &&
    list.last->item == 4 &&
    list.size == 5 &&
    list.operationCounter == 5
  );

  dllistDestruct(&list);
}


void TestDllistDestruct(void)
{
  // Test func dllistDestruct with empty DLList destruction
  DLList list = dllistConstruct(0);
  dllistDestruct(&list);
  assert
  (
    list.first == NULL &&
    list.last == NULL &&
    list.size == 0 &&
    list.operationCounter == 0
  );

  // Test func dllistDestruct with not empty DLList destruction
  list = dllistConstruct(0, 1, 2, 3, 4);
  dllistDestruct(&list);
  assert
  (
    list.first == NULL &&
    list.last == NULL &&
    list.size == 0 &&
    list.operationCounter == 0
  );
}

void TestDllistCopy(void)
{
  // TODO: Should be tested if the source DLList is modified?

  // Test func dllistCopy to copy empty DLList into empty DLList
  DLList src = dllistConstruct(0);
  DLList dest = dllistConstruct(0);
  dllistCopy(&dest, &src);
  assert
  (
    dest.first == NULL &&
    dest.last == NULL &&
    dest.size == 0 &&
    dest.operationCounter == 0
  );

  // Test func dllistCopy to copy empty DLList into not empty DLList
  dest = dllistConstruct(5, 0, 1, 2, 3, 4);
  dllistCopy(&dest, &src);
  assert
  (
    dest.first == NULL &&
    dest.last == NULL &&
    dest.size == 0 &&
    dest.operationCounter == 0
  );

  // Test func dllistCopy to copy not empty DLList into empty DLList
  src = dllistConstruct(5, 0, 1, 2, 3, 4);
  dllistCopy(&dest, &src);
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

  dllistDestruct(&src);

  // Test func dllistCopy to copy not empty DLList into not empty DLList
  src = dllistConstruct(3, 0, 1, 2);
  dllistCopy(&dest, &src);
  destCurrent = dest.first;
  for (int i = 0; i < dest.size; ++i)
  {
    assert(destCurrent->item == i);
    destCurrent = destCurrent->next;
  }
  assert(destCurrent == NULL);
  assert
  (
    dest.last->item == 2 &&
    dest.size == 3 &&
    dest.operationCounter == 3
  );

  dllistDestruct(&src);
  dllistDestruct(&dest);
}


void TestDllistFirst(void)
{
  // Test func dllistFirst with empty DLList
  DLList list = dllistConstruct(0);
  const Iterator itr = dllistFirst(&list);
  assert
  (
    itr.list == &list &&
    itr.current == list.first &&
    itr.currentOperationCounter == list.operationCounter
  );
}


void TestDllistLast(void)
{
  // Test func dllistFirst with empty DLList
  DLList list = dllistConstruct(0);
  const Iterator itr = dllistLast(&list);
  assert
  (
    itr.list == &list &&
    itr.current == list.last &&
    itr.currentOperationCounter == list.operationCounter
  );
}


void TestDllistHasPrevious(void)
{
  // TODO: Test the iterator's fail-fast functionality

  // Test func dllistHasPrevious with empty DLList
  DLList list = dllistConstruct(0);
  Iterator itr = dllistFirst(&list);
  assert(dllistHasPrevious(&itr) == false);

  // Test func dllistHasPrevious with not empty DLList
  list = dllistConstruct(5, 0, 1, 2, 3, 4);
  itr = dllistLast(&list);
  int i = 0;
  while (dllistHasPrevious(&itr))
  {
    dllistPrevious(&itr);
    ++i;
  }
  assert(i == 5);

  dllistDestruct(&list);
}


void TestDllistHasNext(void)
{
  // TODO: Test the iterator's fail-fast functionality

  // Test func dllistFirst with empty DLList
  DLList list = dllistConstruct(0);
  Iterator itr = dllistFirst(&list);
  assert(dllistHasNext(&itr) == false);

  // Test func dllistFirst with not empty DLList
  list = dllistConstruct(5, 0, 1, 2, 3, 4);
  itr = dllistFirst(&list);
  int i = 0;
  while (dllistHasNext(&itr))
  {
    dllistNext(&itr);
    ++i;
  }
  assert(i == list.size);

  dllistDestruct(&list);
}


void TestDllistPrevious(void)
{
  // TODO: Test the iterator's fail-fast functionality
  // TODO: Test func dllistPrevious with empty DLList

  // Test func dllistPrevious with not empty DLList
  DLList list = dllistConstruct(5, 0, 1, 2, 3, 4);
  Iterator itr = dllistLast(&list);
  for (int i = 4; i >= 0; --i)
  {
    const Item *const item = dllistPrevious(&itr);
    assert(*item == i);
  }

  dllistDestruct(&list);
}


void TestDllistNext(void)
{
  // TODO: Test the iterator's fail-fast functionality
  // TODO: Test func dllistNext with empty DLList

  // Test func dllistNext with not empty DLList
  DLList list = dllistConstruct(5, 0, 1, 2, 3, 4);
  Iterator itr = dllistFirst(&list);
  for (int i = 0; i < 5; ++i)
  {
    const Item *const item = dllistNext(&itr);
    assert(*item == i);
  }

  dllistDestruct(&list);
}


void TestDllistIsEmpty(void)
{
  // Test func dllistIsEmpty with empty DLList
  DLList list = dllistConstruct(0);
  assert(dllistIsEmpty(&list) == true);

  // Test func dllistIsEmpty with not empty DLList
  list = dllistConstruct(5, 0, 1, 2, 3, 4);
  assert(dllistIsEmpty(&list) == false);

  dllistDestruct(&list);
}


void TestDllistSize(void)
{
  // Test func dllistSize with empty DLList
  DLList list = dllistConstruct(0);
  assert(dllistSize(&list) == 0);

  // Test func dllistSize with not empty DLList
  list = dllistConstruct(5, 0, 1, 2, 3, 4);
  assert(dllistSize(&list) == 5);

  dllistDestruct(&list);
}


void TestDllistPushFront(void)
{
  // Test func dllistPushFront with empty DLList
  DLList list = dllistConstruct(0);
  dllistPushFront(&list, &((Item){5}));
  assert
  (
    list.first->prev == NULL &&
    list.first->item == 5 &&
    list.first == list.last &&
    list.last->next == NULL &&
    list.size == 1 &&
    list.operationCounter == 1
  );

  // Test func dllistPushFront with not empty DLList
  dllistPushFront(&list, &((Item){10}));
  assert
  (
    list.first->prev == NULL &&
    list.first->item == 10 &&
    list.first->next->item == 5 &&
    list.first->next == list.last &&
    list.last->next == NULL &&
    list.size == 2 &&
    list.operationCounter == 2
  );

  dllistDestruct(&list);
}


void TestDllistPopFront(void)
{
  // TODO: Test func dllistPopFront with empty DLList

  // Test func dllistPopFront with one-Item DLList
  DLList list = dllistConstruct(1, 5);
  Item item = dllistPopFront(&list);
  assert
  (
    list.first == NULL &&
    list.last == NULL &&
    list.size == 0 &&
    list.operationCounter == 2 &&
    item == 5
  );

  dllistDestruct(&list);

  // Test func dllistPopFront with two-Items DLList
  list = dllistConstruct(2, 0, 1);
  item = dllistPopFront(&list);
  assert
  (
    list.first->prev == NULL &&
    list.first->item == 1 &&
    list.first == list.last &&
    list.last->next == NULL &&
    list.size == 1 &&
    list.operationCounter == 3 &&
    item == 0
  );

  dllistDestruct(&list);

  // Test func dllistPopFront with three-Items DLList
  list = dllistConstruct(3, 0, 1, 2);
  item = dllistPopFront(&list);
  assert
  (
    list.first->prev == NULL &&
    list.first->item == 1 &&
    list.first->next->item == 2 &&
    list.first->next == list.last &&
    list.last->next == NULL &&
    list.size == 2 &&
    list.operationCounter == 4 &&
    item == 0
  );

  dllistDestruct(&list);
}


void TestDllistPushBack(void)
{
  // Test func dllistPushBack with empty DLList
  DLList list = dllistConstruct(0);
  dllistPushBack(&list, &((Item){5}));
  assert
  (
    list.first->prev == NULL &&
    list.first->item == 5 &&
    list.first == list.last &&
    list.last->next == NULL &&
    list.size == 1 &&
    list.operationCounter == 1
  );

  dllistDestruct(&list);

  // Test func dllistPushBack with one-Items DLList
  list = dllistConstruct(1, 0);
  dllistPushBack(&list, &((Item){1}));
  assert
  (
    list.first->item == 0 &&
    list.first->next->item == 1 &&
    list.first->next == list.last &&
    list.size == 2 &&
    list.operationCounter == 2
  );

  dllistDestruct(&list);

  // Test func dllistPushBack with two-Items DLList
  list = dllistConstruct(2, 0, 1);
  dllistPushBack(&list, &((Item){2}));
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

  dllistDestruct(&list);
}


void TestDllistPopBack(void)
{
    // TODO: Test func dllistPopBack with empty DLList

  // Test func dllistPopBack with one-Item DLList
  DLList list = dllistConstruct(1, 5);
  Item item = dllistPopBack(&list);
  assert
  (
    list.first == NULL &&
    list.last == NULL &&
    list.size == 0 &&
    list.operationCounter == 2 &&
    item == 5
  );

  dllistDestruct(&list);

  // Test func dllistPopBack with two-Items DLList
  list = dllistConstruct(2, 0, 1);
  item = dllistPopBack(&list);
  assert
  (
    list.first->prev == NULL &&
    list.first->item == 0 &&
    list.first == list.last &&
    list.last->next == NULL &&
    list.size == 1 &&
    list.operationCounter == 3 &&
    item == 1
  );

  dllistDestruct(&list);

  // Test func dllistPopBack with three-Items DLList
  list = dllistConstruct(3, 0, 1, 2);
  item = dllistPopBack(&list);
  assert
  (
    list.first->item == 0 &&
    list.first->next->item == 1 &&
    list.first->next == list.last &&
    list.last->next == NULL &&
    list.size == 2 &&
    list.operationCounter == 4 &&
    item == 2
  );

  dllistDestruct(&list);
}


void TestDllistInsert(void)
{
  // Test func dllistInsert with empty DLList
  DLList list = dllistConstruct(0);
  Iterator itr = dllistFirst(&list);
  dllistInsert(&itr, &((Item){1}));
  assert
  (
    list.first->prev == NULL &&
    list.first->item == 1 &&
    list.first == list.last &&
    list.last->next == NULL &&
    list.size == 1 &&
    list.operationCounter == 1
  );

  dllistDestruct(&list);

  // Test func dllistInsert to insert before the first Item of the one-Item
  // DLList which is also the last Item
  list = dllistConstruct(1, 0);
  itr = dllistFirst(&list);
  dllistInsert(&itr, &((Item){1}));
  assert
  (
    list.first->prev == NULL &&
    list.first->item == 1 &&
    list.first->next->item == 0 &&
    list.first->next == list.last &&
    list.last->next == NULL &&
    list.size == 2 &&
    list.operationCounter == 2
  );

  dllistDestruct(&list);

  // Test func dllistInsert to insert in the middle of the DLList
  list = dllistConstruct(4, 0, 1, 3, 4);
  itr = dllistFirst(&list);
  dllistNext(&itr);
  dllistNext(&itr);
  dllistInsert(&itr, &((Item){2}));
  struct Node *current = list.first;
  for (int i = 0; i < 5; ++i)
  {
    assert(current->item == i);
    current = current->next;
  }
  assert(current == NULL);
  assert(list.size == 5 && list.operationCounter == 5);

  dllistDestruct(&list);
}


void TestDllistErase(void)
{
  // TODO: Test func dllistErase with empty DLList

  // Test func dllistErase to erase the first Item of the one-Item DLList
  // which is also the last Item
  DLList list = dllistConstruct(1, 0);
  Iterator itr = dllistFirst(&list);
  Item item = dllistErase(&itr);
  assert
  (
    list.first == NULL &&
    list.last == NULL &&
    list.size == 0 &&
    list.operationCounter == 2 &&
    itr.current == NULL &&
    item == 0
  );

  dllistDestruct(&list);

  // Test func dllistErase to erase the first Item from a two-Items DLList
  list = dllistConstruct(2, 0, 1);
  itr = dllistFirst(&list);
  item = dllistErase(&itr);
  assert
  (
    list.first->prev == NULL &&
    list.first->item == 1 &&
    list.first == list.last &&
    list.last->next == NULL &&
    list.size == 1 &&
    list.operationCounter == 3 &&
    itr.current == list.first &&
    item == 0
  );

  dllistDestruct(&list);

  // Test func dllistErase to erase the last Item from a two-Items DLList
  list = dllistConstruct(2, 0, 1);
  itr = dllistFirst(&list);
  dllistNext(&itr);
  item = dllistErase(&itr);
  assert
  (
    list.first->prev == NULL &&
    list.first->item == 0 &&
    list.first == list.last &&
    list.last->next == NULL &&
    list.size == 1 &&
    list.operationCounter == 3 &&
    itr.current == NULL &&
    item == 1
  );

  dllistDestruct(&list);

  // Test func dllistErase to erase from the middle of the DLList
  list = dllistConstruct(5, 0, 1, 10, 2, 3);
  itr = dllistFirst(&list);
  dllistNext(&itr);
  dllistNext(&itr);
  item = dllistErase(&itr);
  struct Node *current = list.first;
  for (int i = 0; i < 4; ++i)
  {
    assert(current->item == i);
    current = current->next;
  }
  assert(current == NULL);
  assert
  (
    list.size == 4 &&
    list.operationCounter == 6 &&
    itr.current->item == 2 &&
    item == 10
  );

  dllistDestruct(&list);
}


void TestDllistRemoveIf(void)
{
  // Test func dllistRemoveIf with empty DLList
  DLList list = dllistConstruct(0);
  dllistRemoveIf(&list, predicate);
  assert
  (
    list.first == NULL &&
    list.last == NULL &&
    list.size == 0 &&
    list.operationCounter == 0
  );

  // Test func dllistRemoveIf with no Item to remove in one-Item DLList
  list = dllistConstruct(1, 5);
  dllistRemoveIf(&list, predicate);
  assert
  (
    list.first->prev == NULL &&
    list.first->item == 5 &&
    list.first == list.last &&
    list.last->next == NULL &&
    list.size == 1 &&
    list.operationCounter == 1
  );

  dllistDestruct(&list);

  // Test func dllistRemoveIf with one Item to remove in one-Item DLList
  list = dllistConstruct(1, itemToRemove);
  dllistRemoveIf(&list, predicate);
  assert
  (
    list.first == NULL &&
    list.last == NULL &&
    list.size == 0 &&
    list.operationCounter == 2
  );

  dllistDestruct(&list);

  // Test func dllistRemoveIf with one Item to remove from beginning of a
  // two-Items DLList
  list = dllistConstruct(2, itemToRemove, 4);
  dllistRemoveIf(&list, predicate);
  assert
  (
    list.first->prev == NULL &&
    list.first->item == 4 &&
    list.first == list.last &&
    list.last->next == NULL &&
    list.size == 1 &&
    list.operationCounter == 3
  );

  dllistDestruct(&list);

  // Test func dllistRemoveIf with one Item to remove from end of a two-Items
  // DLList
  list = dllistConstruct(2, 4, itemToRemove);
  dllistRemoveIf(&list, predicate);
  assert
  (
    list.first->item == 4 &&
    list.first == list.last &&
    list.last->next == NULL &&
    list.size == 1 &&
    list.operationCounter == 3
  );

  dllistDestruct(&list);

  // Test func DLListRemmove with more Items to remove from DLList
  list = dllistConstruct(9, itemToRemove, 0, 1, itemToRemove, 2, 4, 5,
                         itemToRemove, itemToRemove);
  dllistRemoveIf(&list, predicate);

  const Item remainingItems[] = {0, 1, 2, 4, 5};
  const int arraySize = 5;
  struct Node *current = list.first;
  assert(list.first->prev == NULL);

  for (int i = 0; i < arraySize; ++i)
  {
    assert(current != NULL);
    assert(current->item == remainingItems[i]);
    current = current->next;
  }
  assert(current == NULL && list.size == arraySize);

  dllistDestruct(&list);
}


bool predicate(const Item *const restrict item)
{
  return *item == itemToRemove;
}
