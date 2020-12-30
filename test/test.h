#ifndef TEST_TEST_H
#define TEST_TEST_H

#include <assert.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>

#include "chess.h"

int t_assert(int* err, int expr, const char* note, ...);
int t_assert_true(int* err, int expr, const char* note, ...);
int t_assert_false(int* err, int expression, const char* note, ...);

int t_assert_null(int* err, void* ptr, const char* note, ...);
int t_assert_not_null(int* err, void* ptr, const char* note, ...);

int t_assert_int(int* err, int v, int k, const char* note, ...);
int t_assert_uint(int* err, unsigned v, unsigned k, const char* note, ...);
int t_assert_float(int* err, float v, float k, const char* note, ...);
int t_assert_double(int* err, double v, double k, const char* note, ...);

int t_assert_string(int* err, const char* str, const char* k,
        const char* note, ...);
int t_assert_string_strict(int* err, const char* str, const char* k,
        const char* note, ...);

// tests
int test_clear_board();
int test_pawn_movement_clear_board();
int test_pawn_taking_moves();

// test playlist
static const int (*tests[])(void) = {
    test_clear_board, test_pawn_movement_clear_board, test_pawn_taking_moves, };

#endif /* TEST_TEST_H */
