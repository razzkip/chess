#include "test.h"

int
t_assert(int expression, const char* comment, ...)
{
    va_list args;

    va_start(args, comment);
    if (!expression) {
        fprintf(stderr, "assert error: %s:%d: ", __FILE__, __LINE__);
        vfprintf(stderr, comment, args);
    }
    return expression;
}

int
t_assert_true(int expression, const char* comment, ...)
{
    va_list args;
    va_start(args, comment);
    if (!expression) {
        fprintf(stderr, "assert error: %s:%d: ", __FILE__, __LINE__);
        vfprintf(stderr, comment, args);
    }
    return expression;
}

int
t_assert_false(int expression, const char* comment, ...)
{
    va_list args;
    va_start(args, comment);
    if (expression) {
        fprintf(stderr, "assert error: %s:%d: %s\n", __FILE__, __LINE__);
        vfprintf(stderr, comment, args);
    }
    return expression;
}

int
t_assert_null(void* pointer, const char* comment, ...)
{
    va_list args;
    va_start(args, comment);
    if (pointer) {
        fprintf(stderr, "assert error: %s:%d: %s\n", __FILE__, __LINE__);
        vfprintf(stderr, comment, args);
        return 0;
    } else {
        return 1;
    }
}

int
t_assert_not_null(void* pointer, const char* comment, ...)
{
    va_list args;
    va_start(args, comment);
    if (!pointer) {
        fprintf(stderr, "assert error: %s:%d: %s\n", __FILE__, __LINE__);
        vfprintf(stderr, comment, args);
        return 0;
    } else {
        return 1;
    }
}
