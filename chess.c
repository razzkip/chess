#include "chess.h"

struct Move black_history[1024];
int can_castle = 1;
enum Piece chessboard[8][8];
struct Move moves[64];
struct Move white_history[1024];

int
bishop_moves(int _x, int _y, int cursor_pos)
{
    // up, left
    int cursor = cursor_pos;
    for (int x = _x - 1, y = _y + 1; 
        x >= 0 && y < 8 && cursor < 64;
        x--, y++) 
    {
        moves[cursor].square.x = x;
        moves[cursor].square.y = y;
        moves[cursor].piece = chessboard[_x][_y];
        cursor++;
        if (chessboard[x][y] != EmptySquare) { break; }
    }

    // up, right
    for (int x = _x + 1, y = _y + 1;
        x < 8 && y < 8 && cursor < 64;
        x++, y++)
    {
        moves[cursor].square.x = x;
        moves[cursor].square.y = y;
        moves[cursor].piece = chessboard[_x][_y];
        cursor++;
        if (chessboard[x][y] != EmptySquare) { break; }
    }

    // down, left
    for (int x = _x - 1, y = _y - 1;
        x >= 0 && y >= 0 && cursor < 64;
        x--, y--)
    {
        moves[cursor].square.x = x;
        moves[cursor].square.y = y;
        moves[cursor].piece = chessboard[_x][_y];
        cursor++;
        if (chessboard[x][y] != EmptySquare) { break; }
    }

    // down, right
    for (int x = _x + 1, y = _y - 1;
        x < 8 && y >= 0 && cursor < 64;
        x++, y--)
    {
        moves[cursor].square.x = x;
        moves[cursor].square.y = y;
        moves[cursor].piece = chessboard[_x][_y];
        cursor++;
        if (chessboard[x][y] != EmptySquare) { break; }
    }

    return cursor - cursor_pos;
}

int
black_piece(int _x, int _y)
{
    if (chessboard[_x][_y] >= BlackPawn 
        && chessboard[_x][_y] <= BlackKing)
    {
        return 1;
    } else {
        return 0;
    }
}

void
clear_board(enum Piece board[8][8])
{
    // clear center
    for (int x = 0; x < 8; x++) {
        for (int y = 2; y < 7; y++) {
            board[x][y] = EmptySquare;
        }
    }

    // place pawns
    for (int x = 0; x < 8; x++) {
        board[x][1] = WhitePawn;
        board[x][6] = BlackPawn;
    }

    // place knights
    board[B][7] = BlackKnight;
    board[G][7] = BlackKnight;
    board[B][0] = WhiteKnight;
    board[G][0] = WhiteKnight;

    // place bishopts
    board[C][7] = BlackBishop;
    board[F][7] = BlackBishop;
    board[C][0] = WhiteBishop;
    board[F][0] = WhiteBishop;

    // place Rooks
    board[A][7] = BlackRook;
    board[H][7] = BlackRook;
    board[A][0] = WhiteRook;
    board[H][0] = WhiteRook;

    // place Queens
    board[D][7] = BlackQueen;
    board[D][0] = WhiteQueen;

    // place King
    board[E][7] = BlackKing;
    board[E][0] = WhiteKing;
}

int
file_to_num(char _x)
{
    switch (_x) {
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

int
king_moves(int _x, int _y, int cursor_pos)
{
    int cursor = cursor_pos;
    for (int x = _x - 1; x < _x + 1; x++) {
        if (x < 8 && x >= 0) {
            if ((_y + 1) < 8) {
                moves[cursor].square.x = x;
                moves[cursor].square.y = _y + 1;
                moves[cursor].piece = chessboard[_x][_y];
                cursor++;
            }
            
            if ((_y - 1) >= 0) {
                moves[cursor].square.x = x;
                moves[cursor].square.y = _y - 1;
                moves[cursor].piece = chessboard[_x][_y];
                cursor++;
            }

            if (_y >= 0 && _y < 8 && x != _x) {
                moves[cursor].square.x = x;
                moves[cursor].square.y = _y;
                moves[cursor].piece = chessboard[_x][_y];
                cursor++;
            }
        }
    }

    // check for castling
    if (_y == 7 
        && _x == E 
        && chessboard[_x][_y] == BlackKing
        && can_castle) 
    {
        // black
        if (chessboard[F][7] == EmptySquare 
            && chessboard[G][7] == EmptySquare) 
        {
            moves[cursor].square.x = CastleKingSide;
            moves[cursor].square.y = CastleKingSide;
            moves[cursor].piece = chessboard[_x][_y];
            cursor++;
        } else if (chessboard[C][7] == EmptySquare
            && chessboard[D][7] == EmptySquare)
        {
            moves[cursor].square.x = CastleQueenSide;
            moves[cursor].square.y = CastleQueenSide;
            moves[cursor].piece = chessboard[_x][_y];
            cursor++;
        }
    } else if (_y == 0
        && _x == E 
        && chessboard[_x][_y] == WhiteKing
        && can_castle)
    {
        // white
        if (chessboard[F][0] == EmptySquare
            && chessboard[G][0] == EmptySquare)
        {
            moves[cursor].square.x = CastleKingSide;
            moves[cursor].square.y = CastleKingSide;
            moves[cursor].piece = chessboard[_x][_y];
            cursor++;
        } else if (chessboard[C][0] == EmptySquare
            && chessboard[D][0] == EmptySquare)
        {
            moves[cursor].square.x = CastleQueenSide;
            moves[cursor].square.y = CastleQueenSide;
            moves[cursor].piece = chessboard[_x][_y];
            cursor++;
        }
    }

    return cursor - cursor_pos;
}

int
knight_move(int _x, int _y)
{
    int cursor = 0;
    // up, left
    if ((_x - 1) >= 0 && (_y + 2) < 8) {
        moves[cursor].square.x = _x - 1;
        moves[cursor].square.y = _y + 1;
        cursor++;
    } else if ((_x - 2) >= 0 && (_y + 1) < 8) {
        moves[cursor].square.x = _x - 1;
        moves[cursor].square.y = _y + 1;
        cursor++;
    }

    // up, right
    if ((_x + 1) < 8 && (_y + 2) < 8) {
        moves[cursor].square.x = _x + 1;
        moves[cursor].square.y = _y + 1;
        cursor++;
    } else if ((_x + 2) < 8 && (_y + 1) < 8) {
        moves[cursor].square.x = _x + 1;
        moves[cursor].square.y = _y + 1;
        cursor++;
    }

    // down, left
    if ((_x - 1) >= 0 && (_y - 2) >= 0) {
        moves[cursor].square.x = _x + 1;
        moves[cursor].square.y = _y + 1;
        cursor++;
    } else if ((_x - 2) >= 0 && (_y - 1) >= 0) {
        moves[cursor].square.x = _x + 1;
        moves[cursor].square.y = _y + 1;
        cursor++;
    }

    // down, right
    if ((_x + 1) < 8 && (_y - 2) >= 0) {
        moves[cursor].square.x = _x + 1;
        moves[cursor].square.y = _y + 1;
        cursor++;
    } else if ((_x + 2) < 8 && (_y - 1) >= 0) {
        moves[cursor].square.x = _x + 1;
        moves[cursor].square.y = _y + 1;
        cursor++;
    }

    return cursor;
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

int
pawn_moves(int _x, int _y)
{
    int cursor = 0;
    if (chessboard[_x][_y] == BlackPawn) {
        // black
        if (chessboard[_x][_y - 1] == EmptySquare
            && (_y - 1) >= 0) {
            moves[cursor].square.x = _x;
            moves[cursor].square.y = _y - 1;
            cursor++;
        }
        // can move two spaces
        if (chessboard[_x][_y - 2] == EmptySquare && _y == 6) {
            moves[cursor].square.x = _x;
            moves[cursor].square.y = _y - 2;
            cursor++;
        }
    } else if (chessboard[_x][_y] == WhitePawn) {
        // white
        if (chessboard[_x][_y + 1] == EmptySquare && (_y + 1) < 8) {
            moves[cursor].square.x = _x;
            moves[cursor].square.y = _y + 1;
            cursor++;
        }
        // can move two spaces
        if (chessboard[_x][_y + 2] == EmptySquare && _y == 1) {
            moves[cursor].square.x = _x;
            moves[cursor].square.y = _y + 2;
            cursor++;
        }
    }

    return cursor;
}

void
position(char* position, int _x, int _y) {
    position[0] = num_to_file(_x);
    char y[2];
    sprintf(y, "%1d", _y);
    position[1] = y[0];
}

int
queen_moves(int _x, int _y)
{
    int cursor = 0;
    cursor = bishop_moves(_x, _y, cursor);
    cursor = rook_moves(_x, _y, cursor);

    return cursor;
}

int
rook_moves(int _x, int _y, int cursor_pos)
{
    // rank
    int cursor = cursor_pos;
    for (int x = 0; x < 8; x++) {
        if (x != _x) {
            moves[cursor].square.x = x;
            moves[cursor].square.y = _y;
            cursor++;
        }
    }

    // file
    for (int y = 0; y < 8; y++) {
        if (y != _y) {
            moves[cursor].square.x = _x;
            moves[cursor].square.y = y;
            cursor++;
        }
    }

    return cursor - cursor_pos;
}

int 
white_piece(int _x, int _y)
{
    if (chessboard[_x][_y] >= WhitePawn
        && chessboard[_x][_y] <= WhiteKing)
    {
        return 1;
    } else {
        return 0;
    }
}

