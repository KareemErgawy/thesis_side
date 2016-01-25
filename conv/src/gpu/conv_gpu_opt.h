#if !defined(CONV_GPU_OPT_H)
#define CONV_GPU_OPT_H

// kernel order:
// 0 - top left
// 1 - top
// 2 - top right
// 3 - middle left
// 4 - middle
// 5 - middle right
// 6 - bottom left
// 7 - bottom
// 8 - bottom right
int GPU_Opt_ApplyStencil(ConvWrapper* wrapper, cl_kernel kernels[9]);

struct kernel_config
{
    size_t global[2];
    size_t local[2];
};

#endif
