#pragma once

class View {
public:
    View(Board &board);
    void showBoard();
    void doGameCycle();
private:
    Board *board;
};
