#if !defined(CONV_COARSE_H)
#define CONV_COARSE_H

// NOTE: it is assumed that out_img memory is already allocated
int Coarse_ApplyStencil(ConvWrapper* wrapper, cl_kernel kernel);

#endif
