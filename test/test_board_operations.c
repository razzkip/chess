#include "chess.h"
#include "test.h"

int
test_clear_board()
{
    int errors = 0;
    enum Piece board[8][8];
    clear_board(board);

    for (int x = 0; x < 8; x++) {
        t_assert_true(&errors, board[x][1] == WhitePawn,
                "no white pawn at (%d, %d)\n", x, 1);
        t_assert_true(&errors, board[x][6] == BlackPawn,
                "no black pawn at (%d, %d)\n", x, 6);
        for (int y = 2; y < 6; y++) {
            t_assert_true(&errors, board[x][y] == EmptySquare,
                    "nonvacant square at (%d, %d)\n", x, y);
        }
    }

    // black back row
    t_assert_true(&errors, board[H][7] == BlackRook,
            "no black rook at (%d, %d)\n", H, 7);
    t_assert_true(&errors, board[G][7] == BlackKnight,
            "no black knight at (%d, %d\n", G, 7);
    t_assert_true(&errors, board[F][7] == BlackBishop,
            "no black bishop at (%d, %d\n", F, 7);
    t_assert_true(&errors, board[E][7] == BlackKing,
            "no black king at (%d, %d)\n", E, 7);
    t_assert_true(&errors, board[D][7] == BlackQueen,
            "no black queen at (%d, %d)\n", D, 7);
    t_assert_true(&errors, board[C][7] == BlackBishop,
            "no black bishop at (%d, %d)\n", C, 7);
    t_assert_true(&errors, board[B][7] == BlackKnight,
            "no black knight at (%d, %d)\n", B, 7);
    t_assert_true(&errors, board[A][7] == BlackRook,
            "no black rook at (%d, %d)\n", A, 7);

    // white back row
    t_assert_true(&errors, board[A][0] == WhiteRook,
            "no white rook at (%d, %d)\n", A, 0);
    t_assert_true(&errors, board[B][0] == WhiteKnight,
            "no white knight at (%d, %d)\n", B, 0);
    t_assert_true(&errors, board[C][0] == WhiteBishop,
            "no white bishop at (%d, %d)\n", C, 0);
    t_assert_true(&errors, board[D][0] == WhiteQueen,
            "no white queen at (%d, %d)\n", D, 0);
    t_assert_true(&errors, board[E][0] == WhiteKing,
            "no white king at (%d, %d)\n", E, 0);
    t_assert_true(&errors, board[F][0] == WhiteBishop,
            "no white bishop at (%d, %d)\n", F, 0);
    t_assert_true(&errors, board[G][0] == WhiteKnight,
            "no white knight at (%d, %d)\n", G, 0);
    t_assert_true(&errors, board[H][0] == WhiteRook,
            "no white rook at (%d, %d)\n", H, 0);

    return errors == 0;
}

int
test_piece_color()
{
    int errors = 0;
    enum Piece board[8][8];
    clear_board(board);

    for (int x = 0; x < 8; x++) {
        for (int y = 0; y < 2; y++) {
            t_assert(&errors, white_piece(board, x, y),
                    "white_piece check failed (%d, %d)\n", x, y);
        }

        for (int y = 6; y < 8; y++) {
            t_assert(&errors, black_piece(board, x, y),
                    "black_piece check failed (%d, %d)\n", x, y);
        }
    }

    return errors == 0;
}
