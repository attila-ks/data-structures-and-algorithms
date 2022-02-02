#ifndef BAGTEST_H
#define BAGTEST_H

void runBagTestCase(void);

static void testBagConstruct(void);
static void testBagDestruct(void);
static void testBagCopy(void);

static void testBagIterator(void);
static void testBagHasNext(void);
static void testBagNext(void);

static void testBagIsEmpty(void);
static void testBagSize(void);

static void testBagAdd(void);

#endif // BAGTEST_H
