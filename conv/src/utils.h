#if !defined(UTILS_H)
#define UTILS_H

#include <stdint.h>

#define global_variable static
#define internal static

typedef uint32_t uint32;
typedef int32_t int32;
typedef float real32;

#define ArrayCount(Array) (sizeof(Array) / sizeof((Array)[0]))

global_variable std::vector<cl::Platform> platforms;
global_variable std::vector<cl::Device>   devices;
global_variable cl::Context               context;
global_variable cl::CommandQueue          queue;
global_variable cl::Program               program;
global_variable std::string               kernel_file_name;
global_variable std::string               kernel_name;

void Print2DArray(std::string message, real32* array, uint32 width,
                  uint32 height);

void GenerateTestImage(real32* img, uint32 img_width,
                     uint32 img_height);

void GenerateTestMask(real32* msk, uint32 msk_width,
                      uint32 msk_height);

void GenerateGaussianBlurFilter_5X5(real32* msk);

bool CompareImages(real32* img1, real32* img2, uint32 img_width,
                   uint32 img_height);

void SetupOpenCL();
#endif
