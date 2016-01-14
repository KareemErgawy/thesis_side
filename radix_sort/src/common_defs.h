#if !defined(COMMON_DEFS_H)
#define COMMON_DEFS_H

// IMPORTANT: it is assumed that, input arrays are unsinged integers
global_variable uint32  bits_per_digit = 4;
global_variable uint32  radix = 16;

uint32 FindNumDigits(uint32* array, uint32 len);

#endif
