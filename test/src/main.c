#include "../headers/sllisttest.h"
#include "../headers/dllisttest.h"
#include <stdio.h>

int main(void)
{
  void (*testCases[])(void) =
  {
    runSllistTestCase,
    runDllistTestCase
  };

  const int arraySize = 2;
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
