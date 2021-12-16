#ifndef DLLISTTEST_H
#define DLLISTTEST_H

void runDllistTestCase(void);

static void TestDllistConstruct(void);
static void TestDllistDestruct(void);
static void TestDllistCopy(void);

static void TestDllistFirst(void);
static void TestDllistLast(void);
static void TestDllistHasNext(void);
static void TestDllistNext(void);

static void TestDllistIsEmpty(void);
static void TestDllistSize(void);

static void TestDllistPushFront(void);
static void TestDllistPopFront(void);
static void TestDllistPushBack(void);
static void TestDllistPopBack(void);
static void TestDllistInsert(void);
static void TestDllistErase(void);

static void TestDllistRemoveIf(void);

#endif // DLLISTTEST_H
