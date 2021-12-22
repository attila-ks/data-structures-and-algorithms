#include "../headers/dllisttest.h"
#include "../headers/sllisttest.h"
#include "../headers/stacktest.h"
#include <stdio.h>

int main(void)
{
  void (*testCases[])(void) =
  {
    runSllistTestCase,
    runDllistTestCase,
    runStackTestCase
  };

  const int arraySize = 3;
  int testCaseCounter = 0;

  for (int i = 0; i < arraySize; ++i)
  {
    testCases[i]();
    ++testCaseCounter;
  }

  printf("%d / %d test case(s) ran successfully!\n", arraySize,
         testCaseCounter);

  return 0;
}
