#if !defined(CONV_FINE_SVM_OPT_H)
#define CONV_FINE_SVM_OPT_H

int FineSVM_Opt_ApplyStencil(ConvWrapper* wrapper, cl_kernel kernels[8],
                             cl_kernel inner_kernel);

#endif
