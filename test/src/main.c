#include "../headers/sllisttest.h"
#include <stdio.h>

int main(void)
{
  void (*testCases[])(void) =
  {
    runSllistTestCase
  };

  const int arraySize = 1;
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
