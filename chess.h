#ifndef CHESS_H
#define CHESS_H

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "chess.h"

enum File { A = 0, B, C, D, E, F, G, H };

// Castling value for both x, y values in move_list
enum NonordinaryMove { CastleKingSide = -2, CastleQueenSide = -1 };
enum Piece { EmptySquare,
    BlackPawn, BlackKnight, BlackBishop, BlackRook, BlackQueen, BlackKing,
    WhitePawn, WhiteKnight, WhiteBishop, WhiteRook, WhiteQueen, WhiteKing,
};

struct Square {
    int x;
    int y;
};

struct Move {
    enum Piece piece;
    struct Square square;
};

int bishop_moves(int _x, int _y, int cursor_pos);
int black_piece(enum Piece board[8][8], int _x, int _y);
void clear_board(enum Piece board[8][8]);
int file_to_num(char _x);
int king_can_move(int to_x, int to_y);
int king_moves(int _x, int _y, int cursor_pos);
int knight_moves(int _x, int _y);
void move(char* buf, enum Piece, int _x, int _y);
char num_to_file(int num);
int pawn_moves(int _x, int _y);
void position(char* position, int _x, int _y);
int queen_moves(int _x, int _y);
int rook_moves(int _x, int _y, int cursor_pos);
void search_board(enum Piece chessboard[8][8], enum Piece piece);
int white_piece(enum Piece board[8][8], int _x, int _y);

extern struct Move black_history[1024];
extern int can_castle;
extern enum Piece chessboard[8][8];
extern struct Move moves[64];
extern struct Move white_history[1024];

#endif /* CHESS_H */
