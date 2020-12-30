#include "chess.h"
#include "test.h"

int
test_clear_board()
{
    int errors = 0;
    piece_t board[8][8];
    clear_board(board);

    for (int x = 0; x < 8; x++) {
        t_assert_true(&errors, compare_pieces(board[x][1], PIECE(Pawn, White)),
                "no white pawn at (%d, %d)\n", x, 1);
        t_assert_true(&errors, compare_pieces(board[x][6], PIECE(Pawn, Black)),
                "no black pawn at (%d, %d)\n", x, 6);
        for (int y = 2; y < 6; y++) {
            t_assert_true(&errors, compare_pieces(board[x][y], EmptySquare),
                    "nonvacant square at (%d, %d)\n", x, y);
        }
    }

    // black back row
    t_assert_true(&errors, compare_pieces(board[H][7], PIECE(Rook, Black)),
            "no black rook at (%d, %d)\n", H, 7);
    t_assert_true(&errors, compare_pieces(board[G][7], PIECE(Knight, Black)),
            "no black knight at (%d, %d\n", G, 7);
    t_assert_true(&errors, compare_pieces(board[F][7], PIECE(Bishop, Black)),
            "no black bishop at (%d, %d\n", F, 7);
    t_assert_true(&errors, compare_pieces(board[E][7], PIECE(King, Black)),
            "no black king at (%d, %d)\n", E, 7);
    t_assert_true(&errors, compare_pieces(board[D][7], PIECE(Queen, Black)),
            "no black queen at (%d, %d)\n", D, 7);
    t_assert_true(&errors, compare_pieces(board[C][7], PIECE(Bishop, Black)),
            "no black bishop at (%d, %d)\n", C, 7);
    t_assert_true(&errors, compare_pieces(board[B][7], PIECE(Knight, Black)),
            "no black knight at (%d, %d)\n", B, 7);
    t_assert_true(&errors, compare_pieces(board[A][7], PIECE(Rook, Black)),
            "no black rook at (%d, %d)\n", A, 7);

    // white back row
    t_assert_true(&errors, compare_pieces(board[A][0], PIECE(Rook, White)),
            "no white rook at (%d, %d)\n", A, 0);
    t_assert_true(&errors, compare_pieces(board[B][0], PIECE(Knight, White)),
            "no white knight at (%d, %d)\n", B, 0);
    t_assert_true(&errors, compare_pieces(board[C][0], PIECE(Bishop, White)),
            "no white bishop at (%d, %d)\n", C, 0);
    t_assert_true(&errors, compare_pieces(board[D][0], PIECE(Queen, White)),
            "no white queen at (%d, %d)\n", D, 0);
    t_assert_true(&errors, compare_pieces(board[E][0], PIECE(King, White)),
            "no white king at (%d, %d)\n", E, 0);
    t_assert_true(&errors, compare_pieces(board[F][0], PIECE(Bishop, White)),
            "no white bishop at (%d, %d)\n", F, 0);
    t_assert_true(&errors, compare_pieces(board[G][0], PIECE(Knight, White)),
            "no white knight at (%d, %d)\n", G, 0);
    t_assert_true(&errors, compare_pieces(board[H][0], PIECE(Rook, White)),
            "no white rook at (%d, %d)\n", H, 0);

    return errors == 0;
}
