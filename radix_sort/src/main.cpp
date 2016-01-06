#include <utils.cpp>

#include <common_defs.h>
#include <seq/rs_seq.cpp>
#include <gpu/rs_gpu.cpp>

int main()
{
    int status;
    status = SetupOpenCL();
    CHECK_ERROR(status, "SetupOpenCL");
    
    // TODO dynamically discover number of digits
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
    
    RadixSort_Seq(test, len, 2);

    for(uint32 i=0 ; i<len ; i++)
    {
        std::cout << test[i] << std::endl;
    }

    RadixSort_GPU(test, len, 2);
    
    free(test);
    
    return 0;
}
