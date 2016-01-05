#if !defined(UTILS_H)
#define UTILS_H

#include <stdint.h>

#define global_variable static
#define internal static

typedef uint32_t uint32;
typedef int32_t int32;
typedef float real32;

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
        if(funcName == "clBuildProgram")                            \
        {                                                           \
            PrintCompilerError(program, device);                    \
        }                                                           \
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
        return ALLOCATION_FAILURE;                                                   \
    }

global_variable cl_platform_id   platform;
global_variable cl_device_id*    devices;
global_variable cl_device_id     device;
global_variable cl_context       context;
global_variable cl_command_queue queue;

global_variable cl_program       program;
global_variable cl_kernel        kernel;

void Print2DArray(std::string message, real32* array, uint32 width,
                  uint32 height);

void GenerateTestImage(real32* img, uint32 img_width,
                     uint32 img_height);

void GenerateTestMask(real32* msk, uint32 msk_width,
                      uint32 msk_height);

void GenerateGaussianBlurFilter_5X5(real32* msk);

bool CompareImages(real32* img1, real32* img2, uint32 img_width,
                   uint32 img_height);

void Clear2DArray(real32* array, uint32 width, uint32 height,
                  real32 value);

//
// OpenCL util functions
//
int SetupOpenCL();

int SetupKernel(std::string kernel_file_name,
                std::string kernel_name);

int DisplayDeviceSVMCaps(cl_device_id device);

int PrintCompilerError(cl_program program, cl_device_id device);

#endif
