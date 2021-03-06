#if !defined(RS_SEQ_H)
#define RS_SEQ_H

global_variable uint32* counters;
global_variable uint32* counters_sum;
global_variable uint32* out;

void Seq_RadixSort(uint32* in, uint32 len, uint32 num_digits);

internal
void CountingSort(uint32* in, uint32 len, uint32 cur_digit);

internal
void Histogram(uint32* in, uint32 len, uint32 cur_digit);

internal
void Rank();

internal
void Scatter(uint32* in, uint32 len, uint32* out, uint32 cur_digit);

internal
uint32 CalcDigitValue(uint32 x, uint32 cur_digit);

#endif
