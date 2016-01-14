#include <utils.cpp>

#include <common_defs.cpp>
#include <seq/rs_seq.cpp>
#include <gpu/rs_gpu.cpp>

#define ReportResult(arr_name, test_name)               \
    if(TestIfArrayIsSorted(arr_name, len))              \
    {                                                   \
        std::cout << "~~~~~~~~~~~~~~" << std::endl      \
                  << "TEST PASSED [" #test_name"]!"     \
                  << std::endl                          \
                  << "~~~~~~~~~~~~~~" << std::endl;     \
    }                                                   \
    else                                                \
    {                                                   \
        std::cout << "~~~~~~~~~~~~~~" << std::endl      \
                  << "TEST FAILED [" #test_name "]!"    \
                  << std::endl                          \
                  << "~~~~~~~~~~~~~~" << std::endl;     \
    }

int main()
{
    int status;
    status = SetupOpenCL();
    CHECK_ERROR(status, "SetupOpenCL");
    
    uint32 len = 4096;
    uint32* input = (uint32*) malloc(sizeof(uint32) * len);
    GenerateTestArray(input, len);

    uint32 num_digits = FindNumDigits(input, len);

    // NOTE the input is copied to different other arrays to test the
    // same input on differnt implmentations

    //
    // Sequential implementation test
    //
    uint32* seq_output = (uint32*) malloc(sizeof(uint32) * len);
    memcpy(seq_output, input, sizeof(uint32) * len);
    Seq_RadixSort(seq_output, len, num_digits);
    ReportResult(seq_output, Sequential CPU);
    
    //
    // GPU implementation test
    //
    uint32* gpu_output = (uint32*) malloc(sizeof(uint32) * len);
    memcpy(gpu_output, input, sizeof(uint32) * len);
    GPU_RadixSort(gpu_output, len, num_digits);
    ReportResult(gpu_output, GPU);

    free(input);
    free(seq_output);
    free(gpu_output);
    
    return 0;
}
