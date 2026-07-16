/* Minimal debug.h stub for compiling urlget.c */
#ifndef DEBUG_H
#define DEBUG_H

#ifdef NDEBUG
#  define DEBUG_ENTER(...)  ((void)0)
#  define DEBUG_TRACE(...)  ((void)0)
#  define DEBUG_ERROR(...)  ((void)0)
#else
#  include <stdio.h>
#  define DEBUG_ENTER(...)  do { fprintf(stderr, "ENTER %s ", __func__); \
        fprintf(stderr, __VA_ARGS__); fprintf(stderr, "\n"); } while (0)
#  define DEBUG_TRACE(...)  do { fprintf(stderr, "TRACE: "); \
        fprintf(stderr, __VA_ARGS__); fprintf(stderr, "\n"); } while (0)
#  define DEBUG_ERROR(...)  do { fprintf(stderr, "ERROR: "); \
        fprintf(stderr, __VA_ARGS__); fprintf(stderr, "\n"); } while (0)
#endif

#endif
