#include "test.h"

int
t_assert(int* error, int expression, const char* comment, ...)
{
    va_list args;

    va_start(args, comment);
    if (!expression) {
        (*error)++;
        fprintf(stderr, "assert error: %s:%d: ", __FILE__, __LINE__);
        vfprintf(stderr, comment, args);
    }
    return expression;
}

int
t_assert_true(int* error, int expression, const char* comment, ...)
{
    va_list args;
    va_start(args, comment);
    if (!expression) {
        (*error)++;
        fprintf(stderr, "assert error: %s:%d: ", __FILE__, __LINE__);
        vfprintf(stderr, comment, args);
    }
    return expression;
}

int
t_assert_false(int* error, int expression, const char* comment, ...)
{
    va_list args;
    va_start(args, comment);
    if (expression) {
        (*error)++;
        fprintf(stderr, "assert error: %s:%d: %s\n", __FILE__, __LINE__);
        vfprintf(stderr, comment, args);
    }
    return expression;
}

int
t_assert_null(int* error, void* pointer, const char* comment, ...)
{
    va_list args;
    va_start(args, comment);
    if (pointer) {
        (*error)++;
        fprintf(stderr, "assert error: %s:%d: %s\n", __FILE__, __LINE__);
        vfprintf(stderr, comment, args);
        return 0;
    } else {
        return 1;
    }
}

int
t_assert_not_null(int* error, void* pointer, const char* comment, ...)
{
    va_list args;
    va_start(args, comment);
    if (!pointer) {
        (*error)++;
        fprintf(stderr, "assert error: %s:%d: %s\n", __FILE__, __LINE__);
        vfprintf(stderr, comment, args);
        return 0;
    } else {
        return 1;
    }
}
