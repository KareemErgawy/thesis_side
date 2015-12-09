#if !defined(UTILS_H)
#define UTILS_H

#include <stdint.h>

#define global_variable static
#define internal static

typedef uint32_t uint32;
typedef int32_t int32;
typedef float real32;

void Print2DArray(std::string message, real32* array, uint32 width,
                  uint32 height);
#endif
