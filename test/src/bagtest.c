#include "../headers/bagtest.h"
#include "../../headers/bag.h"
#include <assert.h>
#include <stdio.h>

void runBagTestCase(void)
{
  testBagConstruct();
  testBagDestruct();
  testBagCopy();

  testBagIterator();
  testBagHasNext();
  testBagNext();

  testBagIsEmpty();
  testBagSize();

  testBagAdd();

  puts("- Bag test case ran without any error!");
}


void testBagConstruct(void)
{
  // TODO: Test bagConstruct with negative argument!
  // TODO: Test bagConstruct with different number of items than ellipsis!

  // Test func bagConstruct to construct an empty Bag
  Bag bag = bagConstruct(0);
  assert(bag.first == NULL && bag.size == 0);

  // Test func bagConstruct to construct a multi-Item Bag
  bag = bagConstruct(4, 0, 1, 2, 3);
  assert(bag.size == 4);
  const struct Node *current = bag.first;
  for (int i = 3; i >= 0; --i)
  {
    assert(current->item == i);
    current = current->next;
  }
  assert(current == NULL);

  bagDestruct(&bag);
}


void testBagDestruct(void)
{
  // Test func bagConstruct to destruct an empty Bag
  Bag bag = bagConstruct(0);
  bagDestruct(&bag);
  assert(bag.first == NULL && bag.size == 0);

  // Test func bagConstruct to destruct a multi-Item Bag
  bag = bagConstruct(4, 0, 1, 2, 3);
  bagDestruct(&bag);
  assert(bag.first == NULL && bag.size == 0);
}


void testBagCopy(void)
{
  // Test func bagCopy to copy empty Bag into other empty Bag
  Bag src = bagConstruct(0);
  Bag dest = bagConstruct(0);
  bagCopy(&dest, &src);
  assert(dest.first == NULL && dest.size == 0);

  // Test func bagCopy to copy empty Bag into a multi-Item Bag
  dest = bagConstruct(4, 0, 1, 2, 3);
  bagCopy(&dest, &src);
  assert(dest.first == NULL && dest.size == 0);

  // Test func bagCopy to copy a multi-Item Bag into empty Bag
  src = bagConstruct(4, 0, 1, 2, 3);
  bagCopy(&dest, &src);
  assert(dest.size == 4);
  const struct Node *current = dest.first;
  for (int i = 3; i >= 0; --i)
  {
    assert(current->item == i);
    current = current->next;
  }
  assert(current == NULL);

  bagDestruct(&dest);

  // Test func bagCopy to copy a multi-Item Bag into a multi-Item Bag
  dest = bagConstruct(5, 0, 10, 20, 30, 40);
  bagCopy(&dest, &src);
  assert(dest.size == 4);
  current = dest.first;
  for (int i = 3; i >= 0; --i)
  {
    assert(current->item == i);
    current = current->next;
  }
  assert(current == NULL);

  bagDestruct(&src);
  bagDestruct(&dest);
}


void testBagIterator(void)
{
  // Test func bagIterator with one-Item Bag
  Bag bag = bagConstruct(1, 5);
  Iterator itr = bagIterator(&bag);
  assert(itr.current == bag.first);

  bagDestruct(&bag);
}


void testBagHasNext(void)
{
  // Test func bagHasNext with empty Bag
  Bag bag = bagConstruct(0);
  Iterator itr = bagIterator(&bag);
  assert(bagHasNext(&itr) == false);

  // Test func bagHasNext with multi-Item Bag
  bag = bagConstruct(4, 0, 1, 2, 3);
  itr = bagIterator(&bag);
  int i = 0;
  while (bagHasNext(&itr))
  {
    bagNext(&itr);
    ++i;
  };
  assert(i == bag.size);

  bagDestruct(&bag);
}


void testBagNext(void)
{
  // TODO: Test func bagNext with empty Bag

  // Test func bagNext with multi-Item Bag
  Bag bag = bagConstruct(4, 0, 1, 2, 3);
  Iterator itr = bagIterator(&bag);
  for (int i = 3; i >= 0; --i)
  {
    const Item *item = bagNext(&itr);
    assert(i == *item);
  }

  // TODO: Test whether itr points to NULL

  bagDestruct(&bag);
}


void testBagIsEmpty(void)
{
  // Test func bagIsEmpty with empty Bag
  Bag bag = bagConstruct(0);
  assert(bagIsEmpty(&bag) == true);

  // Test func bagIsEmpty with not empty Bag
  bag = bagConstruct(4, 0, 1, 2, 3);
  assert(bagIsEmpty(&bag) == false);

  bagDestruct(&bag);
}


void testBagSize(void)
{
  // Test func bagSize with empty Bag
  Bag bag = bagConstruct(0);
  assert(bagSize(&bag) == 0);

  // Test func bagSize with multi-Item Bag
  bag = bagConstruct(4, 0, 1, 2, 3);
  assert(bagSize(&bag) == 4);

  bagDestruct(&bag);
}


void testBagAdd(void)
{
  Bag bag = bagConstruct(0);

  for (int i = 0; i < 4; ++i)
  {
    bagAdd(&bag, &i);
  }

  assert(bag.size == 4);
  const struct Node *current = bag.first;
  for (int i = 3; i >= 0; --i)
  {
    assert(current->item == i);
    current = current->next;
  }
  assert(current == NULL);

  bagDestruct(&bag);
}
