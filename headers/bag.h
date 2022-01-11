#ifndef BAG_H
#define BAG_H

#include <stdbool.h>

typedef int Item;


typedef struct Bag
{
  struct Node
  {
    Item item;
    struct Node *next;
  } *first;

  int size;

} Bag;


// TODO: Does it need to be a fail-fast iterator? Because the only modification
// is add a new Item to the bag.
typedef struct ForwardIterator
{
  struct Node *current;

} Iterator;


// Constructs and returns an Bag with n elements. Each element is a copy.
Bag bagConstruct(int n, ...);
void bagDestruct(Bag *const restrict bag);
void bagCopy(Bag *const dest, const Bag *const src);

Iterator bagIterator(Bag *const restrict bag);
bool bagHasNext(Iterator *const restrict itr);
// Returns a pointer to the next Item. Function bagHasNext should be tested
// before calling this function.
Item *bagNext(Iterator *const restrict itr);

bool bagIsEmpty(const Bag *const restrict bag);
int bagSize(const Bag *const restrict bag);

void bagAdd(Bag *const restrict bag, const Item *const restrict item);

#endif // BAG_H
