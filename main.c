#include "chess.h"

enum File { A, B, C, D, E, F, G, H };
enum Piece { EmptySquare,
    BlackPawn, BlackKnight, BlackBishop, BlackRook, BlackQueen, BlackKing,
    WhitePawn, WhiteKnight, WhiteBishop, WhiteRook, WhiteQueen, WhiteKing,
};

void bishop_moves(int file, int rank);
int black_piece(int file, int rank);
void clear_board();
int file_to_num(char file);
void king_moves(int file, int rank);
void knight_moves(int file, int rank);
void move(char* buffer, enum Piece, int file, int rank);
char num_to_file(int num);
void pawn_moves(int file, int rank);
void position(char* position, int file, int rank);
void queen_moves(int file, int rank);
void rook_moves(int file, int rank);
int white_piece(int file, int rank);

int can_castle = 1;
int chessboard[8][8];
int move_list[64][2];

void
bishop_moves(int file, rank)
{
    // up, left
    int cursor = 0;
    for (int x = file - 1, int y = rank + 1; 
        x >= 0 && y < 8 && cursor < 64;
        x--, y++) 
    {
        movelist[cursor][0] = x;
        movelist[cursor][1] = y;
        cursor++;
        if (chessboard[x][y] != EmptySpace) { break; }
    }

    // up, right
    for (int x = file + 1, int y = rank + 1;
        x < 8 && y < 8 && (movelist - movelist) < 64;
        x++, y++)
    {
        movelist[cursor][0] = x;
        movelist[cursor][1] = y;
        cursor++;
        if (chessboard[x][y] != EmptySpace) { break; }
    }

    // down, left
    for (int x = file - 1, int y = rank - 1;
        x >= 0 && y >= 0 && (movelist - movelist) < 64;
        x--, y--)
    {
        movelist[cursor][0] = x;
        movelist[cursor][1] = y;
        cursor++;
        if (chessboard[x][y] != EmptySpace) { break; }
    }

    // down, right
    for (int x = file + 1, int y = rank - 1;
        x < 8 && y >= 0 && (movelist - movelist) < 64;
        x++, y--)
    {
        movelist[cursor][0] = x;
        movelist[cursor][1] = y;
        cursor++;
        if (chessboard[x][y] != EmptySpace) { break; }
    }
}

int
black_piece(int file, int rank)
{
    if (chessboard[file][rank] >= BlackPawn 
        && chessboard[file][rank] <= BlackKing)
    {
        return 1;
    } else {
        return 0;
    }
}

void
clear_board()
{
    // clear center
    for (int x = 0; x < 8; x++) {
        for (int y = 2; y < 7; y++) {
            chessboard[x][y] = EmptySquare;
        }
    }

    // place pawns
    for (int x = 0; x < 8; x++) {
        chessboard[x][1] = WhitePawn;
        chessboard[x][6] = BlackPawn;
    }

    // place knights
    chessboard[B][7] = BlackKnight;
    chessboard[G][7] = BlackKnight;
    chessboard[B][0] = WhiteKnight;
    chessboard[G][0] = WhiteKnight;

    // place bishopts
    chessboard[C][7] = BlackBishop;
    chessboard[F][7] = BlackBishop;
    chessboard[C][0] = WhiteBishop;
    chessboard[F][0] = WhiteBishop;

    // place Rooks
    chessboard[A][7] = BlackRook;
    chessboard[H][7] = BlackRook;
    chessboard[A][0] = WhiteRook;
    chessboard[H][0] = WhiteRook;

    // place Queens
    chessboard[D][7] = BlackQueen;
    chessboard[D][0] = WhiteQueen;

    // place King
    chessboard[E][7] = BlackKing;
    chessboard[E][0] = WhiteKing;
}

int
file_to_num(char file)
{
    switch (file) {
    case 'a':
    case 'A':
        return A;
    case 'b':
    case 'B':
        return B;
    case 'c':
    case 'C':
        return C;
    case 'd':
    case 'D':
        return D;
    case 'e':
    case 'E':
        return E;
    case 'f':
    case 'F':
        return F;
    case 'g':
    case 'G':
        return G;
    case 'h':
    case 'H':
        return H;
    
    default:
        return -1;
    }
}

void
king_moves(int file, int rank)
{
    // TODO: forgot to check if can castle
    int cursor = 0;
    for (int x = file - 1; x < file + 1; x++) {
        if (x < 8 && x >= 0) {
            if ((rank + 1) < 8) {
                movelist[cursor][0] = x;
                movelist[cursor][1] = rank + 1;
                cursor++;
            }
            
            if ((rank - 1) >= 0) {
                movelist[cursor][0] = x;
                movelist[cursor][1] = rank - 1;
                cursor++;
            }

            if (rank >= 0 && rank < 8 && x != file) {
                movelist[cursor][0] = x;
                movelist[cursor][1] = rank;
                cursor++;
            }
        }
    }
}

void
knight_move(int file, int rank)
{
    int cursor = 0;
    // up, left
    if ((file - 1) >= 0 && (rank + 2) < 8) {
        movelist[cursor][0] = file - 1;
        movelist[cursor][1] = rank + 1;
        cursor++;
    } else if ((file - 2) >= 0 && (rank + 1) < 8) {
        movelist[cursor][0] = file - 1;
        movelist[cursor][1] = rank + 1;
        cursor++;
    }

    // up, right
    if ((file + 1) < 8 && (rank + 2) < 8) {
        movelist[cursor][0] = file + 1;
        movelist[cursor][1] = rank + 1;
        cursor++;
    } else if ((file + 2) < 8 && (rank + 1) < 8) {
        movelist[cursor][0] = file + 1;
        movelist[cursor][1] = rank + 1;
        cursor++;
    }

    // down, left
    if ((file - 1) >= 0 && (rank - 2) >= 0) {
        movelist[cursor][0] = file + 1;
        movelist[cursor][1] = rank + 1;
        cursor++;
    } else if ((file - 2) >= 0 && (rank - 1) >= 0) {
        movelist[cursor][0] = file + 1;
        movelist[cursor][1] = rank + 1;
        cursor++;
    }

    // down, right
    if ((file + 1) < 8 && (rank - 2) >= 0) {
        movelist[cursor][0] = file + 1;
        movelist[cursor][1] = rank + 1;
        cursor++;
    } else if ((file + 2) < 8 && (rank - 1) >= 0) {
        movelist[cursor][0] = file + 1;
        movelist[cursor][1] = rank + 1;
        cursor++;
    }
}

char
num_to_file(int num)
{
    switch (num) {
    case A:
        return 'a';
    case B:
        return 'b';
    case C:
        return 'c';
    case D:
        return 'd';
    case E:
        return 'e';
    case F:
        return 'f';
    case G:
        return 'g';
    case H:
        return 'h';

    default:
        return '?';
    }
}

void
position(char* position, int file, int rank)
{
    position[0] = num_to_file(file);
    position[1] = rank;
}

int 
white_piece(int file, int rank)
{
    if (chessboard[file][rank] >= WhitePawn
        && chessboard[file][rank] <= WhiteKing)
    {
        return 1;
    } else {
        return 0;
    }
}

int main(int argc, char** argv) {



    return 0;
}

