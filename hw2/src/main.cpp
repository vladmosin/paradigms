#include "model.h"
#include "view.h"

int main(int argc, char* argv[]) {
    Board board;
    View viewer(board);
    if (argc > 1) 
        board.set_silent();
    viewer.doGameCycle();
    return 0;
}
