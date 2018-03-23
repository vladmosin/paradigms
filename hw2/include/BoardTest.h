#pragma once
#include "Test.h"

class BoardTest: public Test {
public:
    void testIsWin();
    void testcanMove();
    void testcheck();
    void testis_silent();
    void testgetchar();
    void testgetState();
    void testgetsize();
    void runAllTests();
};
