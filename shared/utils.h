#if !defined(UTILS_H)
#define UTILS_H
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstring>
#include <string>
#include <iomanip>
#include <cmath>
#include <stdint.h>
#include <time.h>
#include <CL/cl.h>
#include <queue>

#include <Utils/bmp-utils.c>

#define global_variable static
#define internal static

typedef uint32_t uint32;
typedef int32_t int32;
typedef float real32;
typedef double real64;

#define ArrayCount(Array) (sizeof(Array) / sizeof((Array)[0]))

#define SUCCESS            0
#define GENERAL_FAILURE    1
#define CL_CALL_FAILURE    2
#define ALLOCATION_FAILURE 3

#define CHECK_ERROR(status, funcName)                               \
    if(status != SUCCESS)                                           \
    {                                                               \
        std::cout << "Error " << status << " calling " << funcName  \
                  << std::endl;                                     \
        std::cout << "Location : " << __FILE__ << ":" << __LINE__   \
                  << std::endl;                                     \
        return CL_CALL_FAILURE;                                     \
    }                                                               \
    else                                                            \
    {                                                               \
        /*std::cout << msg << " Fine" << std::endl;*/               \
    }

#define CHECK_OPENCL_ERROR(status, funcName)                        \
    if(status != CL_SUCCESS)                                        \
    {                                                               \
        std::cout << "Error " << status << " calling " << funcName  \
                  << std::endl;                                     \
        std::cout << "Location : " << __FILE__ << ":" << __LINE__   \
                  << std::endl;                                     \
        return CL_CALL_FAILURE;                                     \
    }                                                               \
    else                                                            \
    {                                                               \
        /*std::cout << msg << " Fine" << std::endl;*/               \
    }

#define CHECK_OPENCL_BUILD_ERROR(status, funcName, device)          \
    if(status != CL_SUCCESS)                                        \
    {                                                               \
        std::cout << "Error " << status << " calling " << funcName  \
                  << std::endl;                                     \
        std::cout << "Location : " << __FILE__ << ":" << __LINE__   \
                  << std::endl;                                     \
        PrintCompilerError(program, device);                        \
        return CL_CALL_FAILURE;                                     \
    }                                                               \
    else                                                            \
    {                                                               \
        /*std::cout << msg << " Fine" << std::endl;*/               \
    }

#define CHECK_ALLOCATION(ptr, ptrName)                              \
    if(ptr == NULL)                                                 \
    {                                                               \
        std::cout << "Failed to allocate memory for " << ptrName    \
                  << std::endl;                                     \
        std::cout << "Location : " << __FILE__ << ":" << __LINE__   \
                  << std::endl;                                     \
        return ALLOCATION_FAILURE;                                  \
    }

global_variable cl_platform_id   platform;
global_variable cl_device_id*    devices;
global_variable cl_context       context;

global_variable cl_device_id     gpu_device;
global_variable cl_device_id     cpu_device;
global_variable cl_command_queue gpu_queue;
global_variable cl_command_queue cpu_queue;

global_variable cl_program       program;

//
// Image related util functions
//
struct ConvWrapper
{
    real32* in_img;
    uint32 img_width;
    uint32 img_height;

    real32* msk;
    uint32 msk_width;
    uint32 msk_height;

    real32* out_img;
};

struct kernel_config
{
    size_t global[2];
    size_t local[2];
};

void Print2DArray(std::string message, real32* array, uint32 width,
                  uint32 height);

void GenerateTestImage(real32* img, uint32 img_width,
                     uint32 img_height);

void GenerateTestMask(real32* msk, uint32 msk_width,
                      uint32 msk_height);

void GenerateRandomImage(real32* img, uint32 img_width,
                         uint32 img_height);

void GenerateGaussianBlurFilter_5X5(real32* msk);

bool CompareImages(real32* img1, real32* img2, uint32 img_width,
                   uint32 img_height);

void Clear2DArray(real32* array, uint32 width, uint32 height,
                  real32 value);

//
// Integer 1D arrays related functions (used in radix sort only so far)
//
void GenerateTestArray(uint32* array, uint32 len);

bool CompareArrays(uint32* a1, uint32* a2, uint32 len);

//
// OpenCL util functions
//
int SetupOpenCL();

int SetupProgram(std::string prgoram_file_name, cl_program* program_ptr);

int SetupProgram(bool gpu, std::string program_file_name,
                 cl_program* program_ptr);

int SetupKernel(std::string kernel_file_name,
                std::string kernel_name, cl_kernel* kernel_ptr);

int SetupKernel(bool gpu, std::string kernel_file_name,
                std::string kernel_name, cl_kernel* kernel_ptr);

int SetupKernel(cl_program program, std::string kernel_name, cl_kernel* kernel_ptr);

int DisplayDeviceSVMCaps(cl_device_id device);

int DisplayDeviceMemoryCaps(cl_device_id device);

int DisplayDeviceWorkRangeInfo(cl_device_id device);

int PrintCompilerError(cl_program program, cl_device_id device);

int PrintBufferContents_Uint32(cl_mem buf, uint32 size,
                               std::string name, uint32 line_size);

//
// Test case timing utils
//

struct TestCaseTimer
{
    clock_t start;
    bool working;
};

struct TestLoopTimer
{
    TestCaseTimer timer;
    
    uint32 num_iterations;
    uint32 num_successes;
    std::vector<real64> times;

    real64 total_time;
};

void ResetLoopTimer(TestLoopTimer* loop_timer);

void TestCaseStarted(TestLoopTimer* loop_timer);

real64 TestCaseFinished(TestLoopTimer* loop_timer);

#endif
