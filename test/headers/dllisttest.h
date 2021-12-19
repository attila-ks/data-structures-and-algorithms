#ifndef DLLISTTEST_H
#define DLLISTTEST_H

void runDllistTestCase(void);

static void testDllistConstruct(void);
static void testDllistDestruct(void);
static void testDllistCopy(void);

static void testDllistFirst(void);
static void testDllistLast(void);
static void testDllistHasPrevious(void);
static void testDllistHasNext(void);
static void testDllistPrevious(void);
static void testDllistNext(void);

static void testDllistIsEmpty(void);
static void testDllistSize(void);

static void testDllistPushFront(void);
static void testDllistPopFront(void);
static void testDllistPushBack(void);
static void testDllistPopBack(void);
static void testDllistInsert(void);
static void testDllistErase(void);

static void testDllistRemoveIf(void);

#endif // DLLISTTEST_H
