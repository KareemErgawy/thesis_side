#if !defined(CONV_COARSE_SVM_H)

// NOTE: it is assumed that out_img memory is already allocated
int CoarseSVM_ApplyStencil(ConvWrapper* wrapper, cl_kernel kernel);

int AllocateSVMObjects(real32** svm_in_img, real32** svm_msk, real32** svm_out_img,
                       uint32 img_size, uint32 msk_size);

int SVMHandleAllBoundries(ConvWrapper* wrapper, real32* svm_in_img,
                          real32* svm_msk, real32* svm_out_img,
                          uint32 img_size, uint32 msk_size);

int SVMHandleInnerRegions(ConvWrapper* wrapper, real32* svm_in_img, real32* svm_msk,
                          real32* svm_out_img, uint32 inner_width, uint32 inner_height,
                          cl_kernel kernel, cl_event* kernel_evt);

int CopyOutputFromSVM(real32* out_img, real32* svm_out_img, uint32 img_size);

#define CONV_COARSE_SVM_H
#endif
