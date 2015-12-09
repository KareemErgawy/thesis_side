#if !defined(CONV_COARSE_H)
#define CONV_COARSE_H

#define __CL_ENABLE_EXCEPTIONS
#include <CL/cl.hpp>

global_variable std::vector<cl::Platform> platforms;
global_variable std::vector<cl::Device>   devices;
global_variable cl::Context               context;
global_variable cl::CommandQueue          queue;
global_variable cl::Program               program;
global_variable std::string               kernel_file_name;
global_variable std::string               kernel_name;
// TODO: consider taking that to a utils file
internal
void SetupOpenCL();

// NOTE: it is assumed that out_img memory is already allocated
void Coarse_ApplyStencil(real32* in_img, uint32 img_width,
                         uint32 img_height, real32* msk,
                         uint32 msk_width, uint32 msk_height,
                         real32* out_img);

#endif
