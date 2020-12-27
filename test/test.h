#ifndef TEST_TEST_H
#define TEST_TEST_H

#include <assert.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>

#include "chess.h"

int t_assert(int* error, int expression, const char* comment, ...);
int t_assert_true(int* error, int expression, const char* comment, ...);
int t_assert_false(int* error, int expression, const char* comment, ...);
int t_assert_null(int* error, void* pointer, const char* comment, ...);
int t_assert_not_null(int* error, void* pointer, const char* comment, ...);

// tests
int test_clear_board();
int test_pawn_movement_clear_board();
int test_piece_color();

// test playlist
static const int (*tests[])(void) = {
    test_clear_board, test_piece_color, test_pawn_movement_clear_board };

#endif /* TEST_TEST_H */
