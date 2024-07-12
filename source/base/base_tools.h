#ifndef __BASE_TOOLS_H_
#define __BASE_TOOLS_H_

#include <stdio.h>
#include <stdlib.h>

#define ASSERT(c) if (!c) do { (*(volatile int *)0 = 0); } while(0)

#define LOG(...) fprintf(stdout, __VA_ARGS__)
#define LOG_ERROR(...) fprintf(stderr, __VA_ARGS__)
#define LOG_THROW(...) do { LOG(__VA_ARGS__); ASSERT(false); } while (0)
#define LOG_ASSERT(c, ...) if (!c) { LOG_THROW(__VA_ARGS__); }

#define STRADD(a, b) a ## b
#define DATA(p) STRADD("data/", p)

#endif