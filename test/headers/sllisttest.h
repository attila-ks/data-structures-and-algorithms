#ifndef SLLISTTEST_H
#define SLLISTTEST_H

void runSllistTestCase(void);

static void TestSllistConstruct(void);
static void TestSllistDestruct(void);
static void TestSllistCopy(void);

static void TestSllistFirst(void);
static void TestSllistLast(void);
static void TestSllistHasNext(void);
static void TestSllistNext(void);

static void TestSllistIsEmpty(void);
static void TestSllistSize(void);

static void TestSllistPushFront(void);
static void TestSllistPopFront(void);
static void TestSllistPushBack(void);

static void TestSllistRemove(void);

#endif // SLLISTTEST_H
