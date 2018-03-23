#include "model.h"
#include "view.h"
#include <cstdio>


View::View(Board &board) {
    this->board = &board;
}

void View::showBoard() {
    printf("\n");
    for (int i = 0; i < board->getsize(); i++) {
        for (int j = 0; j < board->getsize(); j++)
            printf("%c", board->getchar(i, j));
        printf("\n");
    }
}

void View::doGameCycle() {
    bool end_game = false;
    bool bad_move = false;
    char current_sign = 'O';
    int x = -1, y = -1;
    while(!end_game) {
        if (!board->is_silent())
            showBoard();
        bad_move = false;
        do {
            if (bad_move)
                printf("Bad move!\n");
            printf("%c move: ", current_sign);
            bad_move = true;
            if (scanf("%d%d", &x, &y) == 2)
                if (x == -1 && y == -1)
                    return;
        } while(!board->canMove(x, y, current_sign));
        board->move(x, y, current_sign);
        if (board->isWin() != States::CONTINUE)
            end_game = true;
        if (current_sign == 'O')
            current_sign = 'X';
        else
            current_sign = 'O';
    }
    showBoard();
    if (board->getState() == States::DRAW) {
        printf("Draw");
        return;
    }
    if (board->getState() == States::XWIN) {
        printf("X wins!");
        return;
    }
    printf("O wins!");
}
