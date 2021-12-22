#include "../headers/stacktest.h"
#include "../../headers/stack.h"
#include <assert.h>
#include <stdio.h>

void runStackTestCase(void)
{
  testStackConstruct();
  testStackDestruct();
  testStackCopy();

  testStackFirst();
  testStackHasNext();
  testStackNext();

  testStackIsEmpty();
  testStackSize();

  testStackTop();

  testStackPush();
  testStackPop();

  puts("- Stack test case ran without any error!");
}


void testStackConstruct(void)
{
  // TODO: Test stackConstruct with negative argument!
  // TODO: Test stackConstruct with different number of items than ellipsis!

  // Test func stackConstruct to construct an empty Stack
  Stack stack = stackConstruct(0);
  assert
  (
    stack.first == NULL &&
    stack.size == 0 &&
    stack.operationCounter == 0
  );

  // Test func stackConstruct to construct a multi-Item Stack
  stack = stackConstruct(4, 0, 1, 2, 3);
  const struct Node *current = stack.first;
  for (int i = 3; i >= 0; --i)
  {
    assert(current->item == i);
    current = current->next;
  }
  assert(current == NULL);
  assert(stack.size == 4 && stack.operationCounter == 4);

  stackDestruct(&stack);
}


void testStackDestruct(void)
{
  // Test func stackDestruct to destruct an empty Stack
  Stack stack = stackConstruct(0);
  stackDestruct(&stack);
  assert
  (
    stack.first == NULL &&
    stack.size == 0 &&
    stack.operationCounter == 0
  );

  // Test func stackDestruct to destruct a multi-Item Stack
  stack = stackConstruct(4, 0, 1, 2, 3);
  stackDestruct(&stack);
  assert
  (
    stack.first == NULL &&
    stack.size == 0 &&
    stack.operationCounter == 0
  );
}


void testStackCopy(void)
{
  // Test func stackCopy to copy empty Stack into other empty Stack
  Stack src = stackConstruct(0);
  Stack dest = stackConstruct(0);
  stackCopy(&dest, &src);
  assert
  (
    dest.first == NULL &&
    dest.size == 0 &&
    dest.operationCounter == 0
  );

  // Test func stackCopy to copy empty Stack into a multi-Item Stack
  dest = stackConstruct(4, 0, 1, 2, 3);
  stackCopy(&dest, &src);
  assert
  (
    dest.first == NULL &&
    dest.size == 0 &&
    dest.operationCounter == 0
  );

  stackDestruct(&dest);

  // Test func stackCopy to copy a multi-Item Stack into empty Stack
  src = stackConstruct(4, 0, 1, 2, 3);
  stackCopy(&dest, &src);
  struct Node *current = dest.first;
  for (int i = 3; i >= 0; --i)
  {
    assert(current->item == i);
    current = current->next;
  }
  assert(current == NULL);
  assert(dest.size == 4 && dest.operationCounter == 4);

  stackDestruct(&dest);

  // Test func stackCopy to copy a multi-Item Stack into a multi-Item Stack
  dest = stackConstruct(5, 0, 10, 20, 30, 40);
  stackCopy(&dest, &src);
  current = dest.first;
  for (int i = 3; i >= 0; --i)
  {
    assert(current->item == i);
    current = current->next;
  }
  assert(current == NULL);
  assert(dest.size == 4 && dest.operationCounter == 4);

  stackDestruct(&src);
  stackDestruct(&dest);
}


void testStackFirst(void)
{
  // Test func stackFirst with one-Item Stack
  Stack stack = stackConstruct(1, 5);
  Iterator itr = stackFirst(&stack);
  assert
  (
    itr.current == stack.first &&
    itr.operationCounterPtr == &(stack.operationCounter) &&
    itr.currentOperationCounter == stack.operationCounter
  );

  stackDestruct(&stack);
}


void testStackHasNext(void)
{
  // TODO: Test the iterator's fail-fast functionality

  // Test func stackHasNext with empty Stack
  Stack stack = stackConstruct(0);
  Iterator itr = stackFirst(&stack);
  assert(stackHasNext(&itr) == false);

  // Test func stackHasNext with multi-Item Stack
  stack = stackConstruct(4, 0, 1, 2, 3);
  itr = stackFirst(&stack);
  int i = 0;
  while (stackHasNext(&itr))
  {
    stackNext(&itr);
    ++i;
  }
  assert(i == 4);

  stackDestruct(&stack);
}


void testStackNext(void)
{
  // TODO: Test the iterator's fail-fast functionality
  // TODO: Test func stackNext with empty Stack

  // Test func stackNext with multi-Item Stack
  Stack stack = stackConstruct(4, 0, 1, 2, 3);
  Iterator itr = stackFirst(&stack);
  for (int i = 3; i >= 0; --i)
  {
    const Item *const item = stackNext(&itr);
    assert(*item == i);
  }
  // TODO: Test whether itr points to NULL

  stackDestruct(&stack);
}


void testStackIsEmpty(void)
{
  // Test func stackIsEmpty with empty Stack
  Stack stack = stackConstruct(0);
  assert(stackIsEmpty(&stack) == true);

  // Test func stackIsEmpty with multi-Item Stack
  stack = stackConstruct(3, 0, 1, 2);
  assert(stackIsEmpty(&stack) == false);

  stackDestruct(&stack);
}


void testStackSize(void)
{
  // Test func stackSize with empty Stack
  Stack stack = stackConstruct(0);
  assert(stackSize(&stack) == 0);

  // Test func stackSize with multi-Item Stack
  stack = stackConstruct(3, 0, 1, 2);
  assert(stackSize(&stack) == 3);

  stackDestruct(&stack);
}


void testStackTop(void)
{
  // TODO: Test func stackTop with empty Stack

  // Test func stackTop with multi-Item Stack
  Stack stack = stackConstruct(4, 0, 1, 2, 3);
  for (int i = 3; i >= 0; --i)
  {
    const Item *const item = stackTop(&stack);
    assert(*item == i);
    stackPop(&stack);
  }
}


void testStackPush(void)
{
  // Test func stackPush with empty Stack
  Stack stack = stackConstruct(0);
  stackPush(&stack, &((Item){5}));
  assert
  (
    stack.first->item == 5 &&
    stack.first->next == NULL &&
    stack.size == 1 &&
    stack.operationCounter == 1
  );

  stackDestruct(&stack);

  // Test func stackPush with multi-Item Stack
  stack = stackConstruct(4, 0, 1, 2, 3);
  stackPush(&stack, &((Item){4}));
  const struct Node *current = stack.first;
  for (int i = 4; i >= 0; --i)
  {
    assert(current->item == i);
    current = current->next;
  }
  assert(current == NULL);
  assert(stack.size == 5 && stack.operationCounter == 5);

  stackDestruct(&stack);
}


void testStackPop(void)
{
  // TODO: Test func stackPop with empty Stack

  // Test func stackPop with multi-Item Stack
  Stack stack = stackConstruct(4, 0, 1, 2, 3);
  for (int i = 3; i >= 0; --i)
  {
    const Item item = stackPop(&stack);
    assert(item == i);
    assert(stack.size == i && stack.operationCounter == 8 - i);
  }
  assert(stack.first == NULL);

  stackDestruct(&stack);
}
