#include "test.h"

int
t_assert(int* err, int expr, const char* note, ...)
{
    va_list args;

    va_start(args, note);
    if (!expr) {
        (*err)++;
        fprintf(stderr, "assert err: %s:%d: ", __FILE__, __LINE__);
        vfprintf(stderr, note, args);
    }
    return expr;
}

int
t_assert_true(int* err, int expr, const char* note, ...)
{
    va_list args;
    va_start(args, note);
    if (!expr) {
        (*err)++;
        fprintf(stderr, "assert err: %s:%d: ", __FILE__, __LINE__);
        vfprintf(stderr, note, args);
    }
    return expr;
}

int
t_assert_false(int* err, int expr, const char* note, ...)
{
    va_list args;
    va_start(args, note);
    if (expr) {
        (*err)++;
        fprintf(stderr, "assert err: %s:%d: %s\n", __FILE__, __LINE__);
        vfprintf(stderr, note, args);
    }
    return expr;
}

int
t_assert_null(int* err, void* pointer, const char* note, ...)
{
    va_list args;
    va_start(args, note);
    if (pointer) {
        (*err)++;
        fprintf(stderr, "assert err: %s:%d: %s\n", __FILE__, __LINE__);
        vfprintf(stderr, note, args);
        return 0;
    } else {
        return 1;
    }
}

int
t_assert_not_null(int* err, void* pointer, const char* note, ...)
{
    va_list args;
    va_start(args, note);
    if (!pointer) {
        (*err)++;
        fprintf(stderr, "assert err: %s:%d: %s\n", __FILE__, __LINE__);
        vfprintf(stderr, note, args);
        return 0;
    } else {
        return 1;
    }
}

int
t_assert_int(int* err, int v, int k, const char* note, ...)
{
    va_list args;
    va_start(args, note);
    if (v != k) {
        (*err)++;
        fprintf(stderr, "assert err: %s:%d: %s\n", __FILE__, __LINE__);
        vfprintf(stderr, note, args);
        return 0;
    } else {
        return 1;
    }
}

int
t_assert_uint(int* err, unsigned int v, unsigned int k, const char* note, ...)
{
    va_list args;
    va_start(args, note);
    if (v != k) {
        (*err)++;
        fprintf(stderr, "assert err: %s:%d: %s\n", __FILE__, __LINE__);
        vfprintf(stderr, note, args);
        return 0;
    } else {
        return 1;
    }
}

int
t_assert_float(int* err, float v, float k, const char* note, ...)
{
    va_list args;
    va_start(args, note);
    if (v != k) {
        (*err)++;
        fprintf(stderr, "assert err: %s:%d: %s\n", __FILE__, __LINE__);
        vfprintf(stderr, note, args);
        return 0;
    } else {
        return 1;
    }
}

int
t_assert_double(int* err, double v, double k, const char* note, ...)
{
    va_list args;
    va_start(args, note);
    if (v != k) {
        (*err)++;
        fprintf(stderr, "assert err: %s:%d: %s\n", __FILE__, __LINE__);
        vfprintf(stderr, note, args);
        return 0;
    } else {
        return 1;
    }
}

int
t_assert_string(
        int* err, const char* str, const char* k, const char* note, ...)
{
    va_list args;
    va_start(args, note);
    if (strcmp(str, k) != 0) {
        (*err)++;
        fprintf(stderr, "assert err: %s:%d: %s\n", __FILE__, __LINE__);
        vfprintf(stderr, note, args);
        return 0;
    } else {
        return 1;
    }
}

int
t_assert_string_strict(
        int* err, const char* str, const char* k, const char* note, ...)
{
    va_list args;
    va_start(args, note);
    if (strlen(str) != strlen(k) || strcmp(str, k) != 0) {
        (*err)++;
        fprintf(stderr, "assert err: %s:%d: %s\n", __FILE__, __LINE__);
        vfprintf(stderr, note, args);
        return 0;
    } else {
        return 1;
    }
}
