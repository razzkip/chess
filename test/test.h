#ifndef TEST_TEST_H
#define TEST_TEST_H

#include <assert.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>

#include "chess.h"

int t_assert(int expression, const char* comment, ...);
int t_assert_true(int expression, const char* comment, ...);
int t_assert_false(int expression, const char* comment, ...);
int t_assert_null(void* pointer, const char* comment, ...);
int t_assert_not_null(void* pointer, const char* comment, ...);

#endif /* TEST_TEST_H */
