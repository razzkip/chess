#include "chess.h"
#include "test.h"

int
test_pawn_movement_clear_board()
{
    int errors = 0;
    piece_t chessboard[8][8];
    clear_board(chessboard);

    // test from cleared position
    for (int x = 0; x < 8; x++) {
        // white pawns
        mov_t moves[64];
        int mlen = pawn_moves(chessboard, moves, x, 1);
        t_assert_int(&errors, mlen, 2,
                "returned more than two moves for pawn at (%d, %d)\n", x, 1);
        for (int i = 0; i < mlen; i++) {
            t_assert_true(&errors,
                    moves[i].loc.x == x
                    && (moves[i].loc.y == 2 || moves[i].loc.y == 3),
                    "invalid move: (%d, %d), for pawn at: (%d, %d)\n",
                    moves[i].loc.x, moves[i].loc.y, x, 1);
        }

        // black pawns
        mlen = pawn_moves(chessboard, moves, x, 6);
        t_assert_int(&errors, mlen, 2,
                "returned more than two moves for pawn at (%d, %d\n", x, 6);
        for (int i = 0; i < mlen; i++) {
            t_assert_true(&errors,
                    moves[i].loc.x == x
                    && (moves[i].loc.y == 4 || moves[i].loc.y == 5),
                    "invaild move: (%d, %d), for pawn at: (%d, %d)\n",
                    moves[i].loc.x, moves[i].loc.y, x, 6);
        }
    }

    return errors == 0;
}

int
test_pawn_taking_moves()
{
    int errors = 0;
    piece_t chessboard[8][8];
    clear_board(chessboard);


    return errors == 0;
}
