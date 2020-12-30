#include "chess.h"

const piece_t EmptySquare = PIECE(NoPiece, White);

int
bishop_moves(
        piece_t board[8][8], mov_t moves[64], uint8_t _x, uint8_t _y, 
        int cursor_pos)
{
    // up, left
    int cursor = cursor_pos;
    for (int x = _x - 1, y = _y + 1;
        x >= 0 && y < 8 && cursor < 64;
        x--, y++)
    {
        moves[cursor].piece = board[_x][_y];
        moves[cursor].loc.x = x;
        moves[cursor].loc.y = y;
        cursor++;
        if (!compare_pieces(board[x][y], EmptySquare)) { break; }
    }

    // up, right
    for (int x = _x + 1, y = _y + 1;
        x < 8 && y < 8 && cursor < 64;
        x++, y++)
    {
        moves[cursor].loc.x = x;
        moves[cursor].loc.y = y;
        moves[cursor].piece = board[_x][_y];
        cursor++;
        if (!compare_pieces(board[x][y], EmptySquare)) { break; }
    }

    // down, left
    for (int x = _x - 1, y = _y - 1;
        x >= 0 && y >= 0 && cursor < 64;
        x--, y--)
    {
        moves[cursor].loc.x = x;
        moves[cursor].loc.y = y;
        moves[cursor].piece = board[_x][_y];
        cursor++;
        if (!compare_pieces(board[x][y], EmptySquare)) { break; }
    }

    // down, right
    for (int x = _x + 1, y = _y - 1;
        x < 8 && y >= 0 && cursor < 64;
        x++, y--)
    {
        moves[cursor].loc.x = x;
        moves[cursor].loc.y = y;
        moves[cursor].piece = board[_x][_y];
        cursor++;
        if (!compare_pieces(board[x][y], EmptySquare)) { break; }
    }

    return cursor - cursor_pos;
}

void
clear_board(piece_t board[8][8])
{
    // clear center
    for (int x = 0; x < 8; x++) {
        for (int y = 2; y < 7; y++) {
            board[x][y] = EmptySquare;
        }
    }

    // place pawns
    for (int x = 0; x < 8; x++) {
        board[x][1] = PIECE(Pawn, White);
        board[x][6] = PIECE(Pawn, Black);
    }

    // place knights
    board[B][7] = PIECE(Knight, Black);
    board[G][7] = PIECE(Knight, Black);
    board[B][0] = PIECE(Knight, White);
    board[G][0] = PIECE(Knight, White);

    // place bishopts
    board[C][7] = PIECE(Bishop, Black);
    board[F][7] = PIECE(Bishop, Black);
    board[C][0] = PIECE(Bishop, White);
    board[F][0] = PIECE(Bishop, White);

    // place Rooks
    board[A][7] = PIECE(Rook, Black);
    board[H][7] = PIECE(Rook, Black);
    board[A][0] = PIECE(Rook, White);
    board[H][0] = PIECE(Rook, White);

    // place Queens
    board[D][7] = PIECE(Queen, Black);
    board[D][0] = PIECE(Queen, White);

    // place King
    board[E][7] = PIECE(King, Black);
    board[E][0] = PIECE(King, White);
}

int
compare_pieces(piece_t left, piece_t right)
{
    return left.piece == right.piece && left.color == right.color;
}

int
file_idx(char _x)
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
king_moves(
        piece_t board[8][8], mov_t moves[64], uint8_t _x, uint8_t _y,
        int cursor_pos)
{
    int cursor = cursor_pos;
    for (int x = _x - 1; x < _x + 1; x++) {
        if (x < 8 && x >= 0) {
            if ((_y + 1) < 8) {
                moves[cursor].loc.x = x;
                moves[cursor].loc.y = _y + 1;
                moves[cursor].piece = board[_x][_y];
                cursor++;
            }
            
            if ((_y - 1) >= 0) {
                moves[cursor].loc.x = x;
                moves[cursor].loc.y = _y - 1;
                moves[cursor].piece = board[_x][_y];
                cursor++;
            }

            if (_y >= 0 && _y < 8 && x != _x) {
                moves[cursor].loc.x = x;
                moves[cursor].loc.y = _y;
                moves[cursor].piece = board[_x][_y];
                cursor++;
            }
        }
    }

    // check for castling
    if (_y == 7
        && _x == E
        && compare_pieces(board[_x][_y], PIECE(King, Black)))
    {
        // black
        if (compare_pieces(board[F][7], EmptySquare)
            && compare_pieces(board[G][7], EmptySquare))
        {
            moves[cursor].loc.x = CastleKingSide;
            moves[cursor].loc.y = CastleKingSide;
            moves[cursor].piece = board[_x][_y];
            cursor++;
        } else if (compare_pieces(board[C][7], EmptySquare)
            && compare_pieces(board[D][7], EmptySquare))
        {
            moves[cursor].loc.x = CastleQueenSide;
            moves[cursor].loc.y = CastleQueenSide;
            moves[cursor].piece = board[_x][_y];
            cursor++;
        }
    } else if (_y == 0
        && _x == E
        && compare_pieces(board[_x][_y], PIECE(King, White)))
    {
        // white
        if (compare_pieces(board[F][0], EmptySquare)
            && compare_pieces(board[G][0], EmptySquare))
        {
            moves[cursor].loc.x = CastleKingSide;
            moves[cursor].loc.y = CastleKingSide;
            moves[cursor].piece = board[_x][_y];
            cursor++;
        } else if (compare_pieces(board[C][0], EmptySquare)
            && compare_pieces(board[D][0], EmptySquare))
        {
            moves[cursor].loc.x = CastleQueenSide;
            moves[cursor].loc.y = CastleQueenSide;
            moves[cursor].piece = board[_x][_y];
            cursor++;
        }
    }

    return cursor - cursor_pos;
}

int
knight_move(piece_t board[8][8], mov_t moves[64], uint8_t _x, uint8_t _y)
{
    int cursor = 0;
    // up, left
    if ((_x - 1) >= 0 && (_y + 2) < 8) {
        moves[cursor].loc.x = _x - 1;
        moves[cursor].loc.y = _y + 1;
        moves[cursor].piece = board[_x][_y];
        cursor++;
    } else if ((_x - 2) >= 0 && (_y + 1) < 8) {
        moves[cursor].loc.x = _x - 1;
        moves[cursor].loc.y = _y + 1;
        moves[cursor].piece = board[_x][_y];
        cursor++;
    }

    // up, right
    if ((_x + 1) < 8 && (_y + 2) < 8) {
        moves[cursor].loc.x = _x + 1;
        moves[cursor].loc.y = _y + 1;
        moves[cursor].piece = board[_x][_y];
        cursor++;
    } else if ((_x + 2) < 8 && (_y + 1) < 8) {
        moves[cursor].loc.x = _x + 1;
        moves[cursor].loc.y = _y + 1;
        moves[cursor].piece = board[_x][_y];
        cursor++;
    }

    // down, left
    if ((_x - 1) >= 0 && (_y - 2) >= 0) {
        moves[cursor].loc.x = _x + 1;
        moves[cursor].loc.y = _y + 1;
        moves[cursor].piece = board[_x][_y];
        cursor++;
    } else if ((_x - 2) >= 0 && (_y - 1) >= 0) {
        moves[cursor].loc.x = _x + 1;
        moves[cursor].loc.y = _y + 1;
        moves[cursor].piece = board[_x][_y];
        cursor++;
    }

    // down, right
    if ((_x + 1) < 8 && (_y - 2) >= 0) {
        moves[cursor].loc.x = _x + 1;
        moves[cursor].loc.y = _y + 1;
        moves[cursor].piece = board[_x][_y];
        cursor++;
    } else if ((_x + 2) < 8 && (_y - 1) >= 0) {
        moves[cursor].loc.x = _x + 1;
        moves[cursor].loc.y = _y + 1;
        moves[cursor].piece = board[_x][_y];
        cursor++;
    }

    return cursor;
}

int
pawn_moves(piece_t board[8][8], mov_t moves[64], uint8_t _x, uint8_t _y)
{
    uint8_t cursor = 0;
    // TODO: en passant
    if (compare_pieces(board[_x][_y], PIECE(Pawn, Black))) {
        // black
        if (compare_pieces(board[_x][_y - 1], EmptySquare)
            && (_y - 1) >= 0)
        {
            moves[cursor].loc.x = _x;
            moves[cursor].loc.y = _y - 1;
            moves[cursor].piece = board[_x][_y];
            cursor++;
        }
        // can move two spaces
        if (compare_pieces(board[_x][_y - 2], EmptySquare) && _y == 6) {
            moves[cursor].loc.x = _x;
            moves[cursor].loc.y = _y - 2;
            moves[cursor].piece = board[_x][_y];
            cursor++;
        }
        // can take
        if ((_x - 1) >= 0 && (_y - 1) >= 0
                && !compare_pieces(board[_x - 1][_y - 1], EmptySquare))
        {
            moves[cursor].loc.x = _x - 1;
            moves[cursor].loc.y = _y - 1;
            moves[cursor].piece = board[_x][_y];
            cursor++;
        }
        if ((_x + 1) < 8 && (_y - 1) >= 0
                && !compare_pieces(board[_x + 1][_y - 1], EmptySquare))
        {
            moves[cursor].loc.x = _x + 1;
            moves[cursor].loc.y = _y - 1;
            moves[cursor].piece = board[_x][_y];
            cursor++;
        }
    } else if (compare_pieces(board[_x][_y], PIECE(Pawn, White))) {
        // white
        if (compare_pieces(board[_x][_y + 1], EmptySquare) && (_y + 1) < 8) {
            moves[cursor].loc.x = _x;
            moves[cursor].loc.y = _y + 1;
            moves[cursor].piece = board[_x][_y];
            cursor++;
        }
        // can move two spaces
        if (compare_pieces(board[_x][_y + 2], EmptySquare) && _y == 1) {
            moves[cursor].loc.x = _x;
            moves[cursor].loc.y = _y + 2;
            moves[cursor].piece = board[_x][_y];
            cursor++;
        }
        // can take
        if ((_x - 1) >= 0 && (_y + 1) < 8
                && !compare_pieces(board[_x - 1][_y + 1], EmptySquare))
        {
            moves[cursor].loc.x = _x;
            moves[cursor].loc.y = _y;
            moves[cursor].piece = board[_x][_y];
            cursor++;
        }
        if ((_x + 1) < 8 && (_y + 1) < 8
                && !compare_pieces(board[_x + 1][_y + 1], EmptySquare))
        {
            moves[cursor].loc.x = _x;
            moves[cursor].loc.y = _y;
            moves[cursor].piece = board[_x][_y];
            cursor++;
        }
    }

    return cursor;
}

piece_t
piece(piece_t board[8][8], loc_t loc)
{
    return board[loc.x][loc.y];
}

void
pos_to_str(char position[3], uint8_t _x, uint8_t _y) {
    position[0] = _x + 'a';
    position[1] = _y + '1';
    position[2] = '\0';
}

int
queen_moves(piece_t board[8][8], mov_t moves[64], uint8_t _x, uint8_t _y)
{
    int cursor = bishop_moves(board, moves, _x, _y, 0);
    cursor += rook_moves(board, moves, _x, _y, cursor);
    return cursor;
}

int
rook_moves(
        piece_t board[8][8], mov_t moves[64], uint8_t _x, uint8_t _y,
        int cursor_pos)
{
    // rank
    int cursor = cursor_pos;
    for (int x = 0; x < 8; x++) {
        if (x != _x) {
            moves[cursor].loc.x = x;
            moves[cursor].loc.y = _y;
            moves[cursor].piece = board[_x][_y];
            cursor++;
        }
    }

    // file
    for (int y = 0; y < 8; y++) {
        if (y != _y) {
            moves[cursor].loc.x = _x;
            moves[cursor].loc.y = y;
            moves[cursor].piece = board[_x][_y];
            cursor++;
        }
    }

    return cursor - cursor_pos;
}
