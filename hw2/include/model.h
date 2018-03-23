#pragma once

const int SIZE = 10;
const int TO_WIN = 5;

enum class States {XWIN, OWIN, DRAW, CONTINUE};

class Board {
public:
    Board();
    bool check();
    bool is_silent();
    void set_silent();
    char getchar(int x, int y);
    States getState();
    void move(int x, int y, char sign);
    int getsize();
    bool canMove(int x, int y, char sign);
    States isWin();
private:
    char board[SIZE][SIZE]; 
    bool silent = false;
    int size = SIZE;
    int last_x = -1;
    int last_y = -1;
    int fullness = 0;
    char last_sign = '.';
    int quan_to_win = TO_WIN;
    States state = States::CONTINUE;
};
