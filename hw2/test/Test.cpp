#include "Test.h"
#include <cstdio>
#include <algorithm>

int Test::totalNum = 0;
int Test::failedNum = 0;

void Test::showFinalResult() {
    if (failedNum == 0)
        printf("All tests passed\n");
    else 
        printf("Failed %d of %d\n", failedNum, totalNum);
}

void Test::check(bool expr, const char *func, const char* filename, size_t lineNum) {
    totalNum++;
    if (!expr) {
        printf("test failed: %s in %s:%zu\n", func, filename, lineNum);
        failedNum++;
    }
}
