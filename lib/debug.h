#pragma once
#ifdef DEBUG
#include <stdio.h>
#define DebugPrint(...)               \
    do {                              \
        fprintf(stderr, __VA_ARGS__); \
    } while (false)
#else
#define DebugPrint(...) \
    do {                \
    } while (false)
#endif