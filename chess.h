#ifndef CHESS_H
#define CHESS_H

#include <assert.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "chess.h"

#define PIECE(p, c) (piece_t){ p, c }
#define LOC(x, y) (loc_t){ x, y - 1 };

typedef enum { A, B, C, D, E, F, G, H } file_idx_t;

// Castling value for both x, y values in move_list
enum NonordinaryMove { CastleKingSide = -2, CastleQueenSide = -1 };
typedef enum { NoPiece, Pawn, Knight, Bishop, Rook, Queen, King, } piece_e;
typedef enum { White, Black } color_e;

typedef struct {
    uint8_t piece : 4;
    uint8_t color : 1;
} piece_t;

typedef struct {
    char x;
    char y;
} loc_t;

typedef struct {
    piece_t piece;
    loc_t loc;
} mov_t;

extern const piece_t EmptySquare;

int bishop_moves(
        piece_t board[8][8], mov_t moves[64], uint8_t _x, uint8_t _y,
        int cursor_pos);
void clear_board(piece_t board[8][8]);
int compare_pieces(piece_t left, piece_t right);
int king_can_move(piece_t board[8][8], uint8_t to_x, uint8_t to_y);
int king_moves(
        piece_t board[8][8], mov_t moves[64], uint8_t _x, uint8_t _y,
        int cursor_pos);
int knight_moves(piece_t board[8][8], mov_t moves[64], uint8_t _x, uint8_t _y);
void move(char* buf, piece_t piece, uint8_t _x, uint8_t _y);
int pawn_moves(piece_t board[8][8], mov_t moves[64], uint8_t _x, uint8_t _y);
piece_t piece(piece_t board[8][8], loc_t _loc);
void pos_to_str(char position[3], uint8_t _x, uint8_t _y);
int queen_moves(piece_t board[8][8], mov_t moves[64], uint8_t _x, uint8_t _y);
int rook_moves(
        piece_t board[8][8], mov_t moves[64], uint8_t _x, uint8_t _y,
        int cursor_pos);
void search_board(piece_t chessboard[8][8], piece_t piece);

#endif /* CHESS_H */
