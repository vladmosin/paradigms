#include "BoardTest.h"
#include "model.h"
#include "Test.h"

#define DO_CHECK(EXPR) Test::check(EXPR, __FUNCTION__, __FILE__, __LINE__)

void BoardTest::testIsWin() {
    Board b;
    b.move(0, 1, 'X');
    b.move(1, 1, 'X');
    b.move(2, 1, 'X');
    b.move(6, 1, 'X');
    b.move(8, 1, 'X');
    DO_CHECK(b.isWin() == States::CONTINUE);
    
    b.move(3, 1, 'X');
    b.move(4, 1, 'X');
    DO_CHECK(b.isWin() == States::XWIN);
    
    Board b1;
    b1.move(0, 0, 'O');
    b1.move(1, 1, 'O');
    b1.move(2, 2, 'O');
    b1.move(3, 3, 'O');
    b1.move(4, 4, 'O');
    DO_CHECK(b1.isWin() == States::OWIN); 
     
    Board b2;
    b2.move(0, 1, 'O');
    b2.move(1, 2, 'O');
    b2.move(2, 3, 'O');
    b2.move(1, 3, 'O');
    b2.move(1, 4, 'O');
    b2.move(7, 0, 'O');
    b2.move(8, 1, 'O');
    b2.move(8, 2, 'O');
    b2.move(8, 3, 'O');
    b2.move(8, 4, 'O');   
    b2.move(7, 0, 'O');
    b2.move(5, 7, 'O');
    b2.move(6, 8, 'O');
    b2.move(9, 8, 'O');
    b2.move(9, 9, 'O');
    DO_CHECK(b2.isWin() == States::CONTINUE);           
} 

void BoardTest::testcanMove() {
    Board b;
    DO_CHECK(b.canMove(0, 0, 'O'));
    DO_CHECK(b.canMove(4, 5, 'O'));
    DO_CHECK(!b.canMove(-1, 7, 'O'));
    DO_CHECK(!b.canMove(6, 10, 'O'));
}  

void BoardTest::testcheck() {
    Board b;
    b.move(2, 0, 'X');
    b.move(2, 1, 'X');
    b.move(2, 3, 'X');
    b.move(2, 6, 'X');
    b.move(2, 7, 'X');
    DO_CHECK(!b.check());
    
    b.move(2, 4, 'X');
    b.move(2, 2, 'X');
    DO_CHECK(b.check());
    
    Board b1;
    b1.move(0, 9, 'O');
    b1.move(1, 8, 'O');
    b1.move(2, 7, 'O');
    b1.move(4, 5, 'O');
    b1.move(3, 6, 'O');
    DO_CHECK(b1.check());
    
    b1.move(7, 3, 'X');
    b1.move(8, 2, 'X');
    b1.move(9, 1, 'X');
    b1.move(5, 5, 'X');
    b1.move(6, 4, 'X');
    DO_CHECK(b1.check());
    
    Board b2;
    b2.move(0, 1, 'X');
    b2.move(1, 2, 'O');
    b2.move(2, 3, 'X');
    b2.move(1, 3, 'O');
    b2.move(1, 4, 'X');
    b2.move(7, 0, 'O');
    b2.move(8, 1, 'X');
    b2.move(8, 2, 'O');
    b2.move(8, 3, 'X');
    b2.move(8, 4, 'O');   
    b2.move(7, 0, 'X');
    b2.move(5, 7, 'O');
    b2.move(6, 8, 'X');
    b2.move(9, 8, 'O');
    b2.move(9, 9, 'X');
    b2.move(0, 5, 'O');
    DO_CHECK(!b2.check());
}

void BoardTest::testis_silent() {
    Board b;
    DO_CHECK(!b.is_silent());
    b.set_silent();
    DO_CHECK(b.is_silent());
}

void BoardTest::testgetchar() {
    Board b;
    b.move(1, 1, 'g');
    b.move(1, 6, 'X');
    DO_CHECK(b.getchar(1, 1) == 'g');
    DO_CHECK(b.getchar(0, 0) == '.');
    DO_CHECK(b.getchar(1, 6) == 'X');
}

void BoardTest::testgetState() {
    Board b;
    b.move(0, 7, 'X');
    b.move(1, 7, 'X');
    b.move(2, 7, 'X');
    b.move(6, 7, 'X');
    b.move(8, 7, 'X');
    b.isWin();
    DO_CHECK(b.getState() == States::CONTINUE);
    b.move(3, 7, 'X');
    b.move(4, 7, 'X');
    b.isWin();
    DO_CHECK(b.getState() == States::XWIN);
    Board b1;
    b1.move(0, 0, 'O');
    b1.move(1, 1, 'O');
    b1.move(2, 2, 'O');
    b1.move(3, 3, 'O');
    b1.move(4, 4, 'O');
    b1.isWin();
    DO_CHECK(b1.getState() == States::OWIN);
}

void BoardTest::testgetsize() {
    Board b;
    DO_CHECK(b.getsize() == 10);
}

void BoardTest::runAllTests() {
    testIsWin();
    testcanMove();
    testcheck();
    testis_silent();
    testgetchar();
    testgetState();
    testgetsize();
    showFinalResult();
}

int main() {
    BoardTest bt;
    bt.runAllTests();
    Board b;
}

