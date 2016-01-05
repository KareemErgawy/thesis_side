#if !defined(UTILS_H)
#define UTILS_H

#include <stdint.h>

#define global_variable static
#define internal static

typedef uint32_t uint32;
typedef int32_t int32;

#define ArrayCount(Array) (sizeof(Array) / sizeof((Array)[0]))

#endif
