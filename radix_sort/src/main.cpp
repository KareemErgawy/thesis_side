#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstring>
#include <string>
#include <iomanip>
#include <cmath>

#include <CL/cl.h>

#include <Utils/bmp-utils.c>
#include <utils.cpp>

#include <seq/rs_seq.cpp>

int main()
{
    uint32 len = 10;
    uint32* test = (uint32*) malloc(sizeof(uint32) * len);

    std::cout << std::hex;
    
    for(uint32 i=0 ; i<len ; i++)
    {
        test[i] = rand() % 100;
        std::cout << test[i] << std::endl;
    }

    std::cout << std::endl << "***************************"
              << std::endl << std::endl;
    
    RadixSort(test, len, 2);

    for(uint32 i=0 ; i<len ; i++)
    {
        std::cout << test[i] << std::endl;
    }

    free(test);
    
    return 0;
}
