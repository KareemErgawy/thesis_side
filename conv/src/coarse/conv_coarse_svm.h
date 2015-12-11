#if !defined(CONV_COARSE_SVM_H)

global_variable real32 _img_size;
global_variable real32 _inner_width;
global_variable real32 _inner_height;
global_variable real32 _inner_size;
global_variable real32 _msk_size;

global_variable size_t kernel_wrkgrp_size;
global_variable cl_ulong kernel_local_mem_used;
global_variable size_t compile_wrkgrp_size[3];

// NOTE: it is assumed that out_img memory is already allocated
int CoarseSVM_ApplyStencil(real32* in_img, uint32 img_width,
                         uint32 img_height, real32* msk,
                         uint32 msk_width, uint32 msk_height,
                         real32* out_img);

int AllocateSVMObjects();
int SVMHandleAllBoundries(real32* in_img, real32* msk,
                             real32* out_img);
int SVMHandleInnerRegions();
int CopyOutputFromSVM(real32* out_img);

#define CONV_COARSE_SVM_H
#endif
