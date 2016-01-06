#include <seq/rs_seq.h>

void RadixSort_Seq(uint32* in, uint32 len, uint32 num_digits)
{
    counters = (uint32*) malloc(sizeof(uint32) * radix);
    counters_sum = (uint32*) malloc(sizeof(uint32) * radix);
    out = (uint32*) malloc(sizeof(uint32) * len);
    
    for(uint32 cur_digit=0 ; cur_digit<num_digits ; cur_digit++)
    {
        CountingSort(in, len, cur_digit);
    }

    memcpy(in, out, sizeof(uint32) * len);
    
    free(counters);
    free(counters_sum);
    free(out);
}

internal
void CountingSort(uint32* in, uint32 len, uint32 cur_digit)
{
    Histogram(in, len, cur_digit);
    Rank();
    Scatter(in, len, out, cur_digit);
}

internal
void Histogram(uint32* in, uint32 len, uint32 cur_digit)
{
    for(uint32 i=0 ; i<radix ; i++)
    {
        counters[i] = 0;
    }

    for(int i=0 ; i<len ; i++)
    {
        uint32 digit_val = CalcDigitValue(in[i], cur_digit);
        counters[digit_val]++;
    }
}

internal
void Rank()
{
    counters_sum[0] = counters[0];
    
    for(int i=1 ; i<radix ; i++)
    {
        counters_sum[i] = counters[i] + counters_sum[i-1];
    }
}

internal
void Scatter(uint32* in, uint32 len, uint32* out, uint32 cur_digit)
{
    for(int32 i=len-1 ; i>=0 ; i--)
    {
        uint32 digit_val = CalcDigitValue(in[i], cur_digit);
        uint32 out_loc = counters_sum[digit_val] - 1;
        out[out_loc] = in[i];
        --counters_sum[digit_val];
    }
}

internal
uint32 CalcDigitValue(uint32 x, uint32 cur_digit)
{
    return ((x >> (cur_digit*digits)) & 0xF);
}
