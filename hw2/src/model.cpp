#include "model.h"
#include <cstdio>
#include <algorithm>

Board::Board() {
    for (int i = 0; i < 10; i++)
        for (int j = 0; j < 10; j++)
            board[i][j] = '.';
}

bool correct_coordinate(int coordinate, int size) {
    return coordinate < size && coordinate >= 0;
}

int Board::getsize() {
    return size;
}

void Board::move(int x, int y, char sign) {
    last_x = x;
    last_y = y;
    last_sign = sign;
    fullness++;
    board[x][y] = sign;
}

States Board::getState() {
    return state;
}

char Board::getchar(int x, int y) {
    return board[x][y];
}

bool Board::canMove(int x, int y, char sign) {
    if (correct_coordinate(x, size) && correct_coordinate(y, size))
        return board[x][y] == '.';
    return false;
}

bool Board::check() {
    int quantity = 0;
    for (int i = std::max(last_x - quan_to_win + 1, 0); i < std::min(last_x + quan_to_win, size); i++)
        if (board[i][last_y] == last_sign) {
            quantity++;
            if (quantity == quan_to_win)
                return true;
        } else {
            quantity = 0;
        }
    quantity = 0;
    for (int i = std::max(last_y - quan_to_win + 1, 0); i < std::min(last_y + quan_to_win, size); i++)
        if (board[last_x][i] == last_sign) {
            quantity++;
            if (quantity == quan_to_win)
                return true;
        } else {
            quantity = 0;
        }
    quantity = 0;
    int start_x = std::max(0, last_x - last_y);
    int start_y = std::max(0, last_y - last_x);
    for (int i = 0; i < size - std::max(start_x, start_y); i++)
        if (board[start_x + i][start_y + i] == last_sign) {
            quantity++;
            if (quantity == quan_to_win)
                return true;
        } else {
            quantity = 0;
        }
    quantity = 0;
    start_x = std::max(0, last_x - (size - 1 - last_y));
    start_y = std::min(size - 1, last_y + last_x);
    for (int i = 0; i <= std::min(size - 1 - start_x, start_y); i++)
        if (board[start_x + i][start_y - i] == last_sign) {
            quantity++;
            if (quantity == quan_to_win)
                return true;
        } else {
            quantity = 0;
        }
    return false;
}

bool Board::is_silent() {
    return silent == true;
}

void Board::set_silent() {
    silent = true;
}

States Board::isWin() {
    if (check()) {
        if (last_sign == 'O') {
            state = States::OWIN;
            return States::OWIN;
        } else {
            state = States::XWIN;
            return States::XWIN;
        }
    }
    if (fullness == size * size) {
        state = States::DRAW;
        return States::DRAW;
    }
    return States::CONTINUE;
}
