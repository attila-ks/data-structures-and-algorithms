#ifndef SLLISTTEST_H
#define SLLISTTEST_H

void runSllistTestCase(void);

static void testSllistConstruct(void);
static void testSllistDestruct(void);
static void testSllistCopy(void);

static void testSllistFirst(void);
static void testSllistLast(void);
static void testSllistHasNext(void);
static void testSllistNext(void);

static void testSllistIsEmpty(void);
static void testSllistSize(void);

static void testSllistPushFront(void);
static void testSllistPopFront(void);
static void testSllistPushBack(void);

static void testSllistRemoveIf(void);

#endif // SLLISTTEST_H
