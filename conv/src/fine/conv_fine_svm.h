#if !defined(CONV_FINE_SVM_H)

int FineSVM_ApplyStencil(ConvWrapper* wrapper, cl_kernel kernel,
                         bool wait_kernel=false);

int FineSVM_AllocateSVMObjects(real32** svm_in_img, real32** svm_msk, real32** svm_out_img,
                       uint32 img_size, uint32 msk_size);

int FineSVM_HandleAllBoundries(ConvWrapper* wrapper, real32* svm_in_img,
                          real32* svm_msk, real32* svm_out_img,
                          uint32 img_size, uint32 msk_size);

#define CONV_FINE_SVM_H
#endif

