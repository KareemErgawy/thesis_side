#include <common_defs.h>

uint32 FindNumDigits(uint32* array, uint32 len)
{
    uint32 max_num = 0;
    for(uint32 i=0 ; i<len ; i++)
    {
        uint32 temp = array[i];
        uint32 num_digits = 0;

        while(temp > 0)
        {
            temp = temp >> bits_per_digit;
            num_digits++;
        }

        if(num_digits > max_num)
        {
            max_num = num_digits;
        }
    }

    return max_num;
}
