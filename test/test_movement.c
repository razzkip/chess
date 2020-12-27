#include "chess.h"
#include "test.h"

int
test_pawn_movement_clear_board()
{
    int errors = 0;
    enum Piece chessboard[8][8];
    clear_board(chessboard);

    // test from cleared position
    for (int x = 0; x < 8; x++) {
    }

    return errors == 0;
}
