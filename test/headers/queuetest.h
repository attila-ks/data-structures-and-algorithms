#ifndef QUEUETEST_H
#define QUEUETEST_H

void runQueueTestCase(void);

static void testQueueConstruct(void);
static void testQueueDestruct(void);
static void testQueueCopy(void);

static void testQueueFirst(void);
static void testQueueLast(void);
static void testQueueHasNext(void);
static void testQueueNext(void);

static void testQueueIsEmpty(void);
static void testQueueSize(void);

static void testQueueEnqueue(void);
static void testQueueDequeue(void);

#endif // QUEUETEST_H
