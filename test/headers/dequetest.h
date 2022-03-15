#ifndef DEQUETEST_H
#define DEQUETEST_H

void runDequeTestCase(void);

static void testDequeConstruct(void);
static void testDequeDestruct(void);
static void testDequeCopy(void);

static void testDequeFirst(void);
static void testDequeLast(void);
static void testDequeHasPrevious(void);
static void testDequePrevious(void);
static void testDequeHasNext(void);
static void testDequeNext(void);

static void testDequeSize(void);
static void testDequeIsEmpty(void);

static void testDequePushFront(void);
static void testDequePushBack(void);
static void testDequePopFront(void);
static void testDequePopBack(void);
static void testDequeInsert(void);
static void testDequeErase(void);

#endif // DEQUETEST_H
