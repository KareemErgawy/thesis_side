#include <fine/conv_fine_svm.h>

#include <CL/cl.h>

int FineSVM_ApplyStencil(ConvWrapper* wrapper, cl_kernel kernel, bool wait_kernel)
{
    /*
    std::cout << "Fine (SVM) Convolution START!" << std::endl;

    if(use_unrolled)
    {
        std::cout << "Urolled kernel used";
    }
    else
    {
        std::cout << "Urolled kernel used NOT used";        
    }
    std::cout << std::endl;
    */
    
    TestCaseStarted(&loop_timer);

    uint32 half_w = wrapper->msk_width / 2;
    uint32 half_h = wrapper->msk_height / 2;

    uint32 img_size = wrapper->img_width * wrapper->img_height;
    uint32 inner_width = (wrapper->img_width - (half_w*2));
    uint32 inner_height = (wrapper->img_height - (half_h*2));
    uint32 inner_size = inner_width * inner_height;
    uint32 msk_size = wrapper->msk_width * wrapper->msk_height;

    cl_int status;

    real32* svm_in_img = NULL;
    real32* svm_msk = NULL;
    real32* svm_out_img = NULL;
    
    status = FineSVM_AllocateSVMObjects(&svm_in_img, &svm_msk, &svm_out_img, img_size,
                                        msk_size);
    CHECK_ERROR(status, "AllocateSVMObjects");

    // NOTE: we would have to do this anyway. if not for copying the
    // input image, will be for initialization
    std::memcpy(svm_in_img, wrapper->in_img, img_size*sizeof(real32));
    std::memcpy(svm_msk, wrapper->msk, msk_size*sizeof(real32));

    cl_event kernel_evt;
    status = SVMHandleInnerRegions(wrapper, svm_in_img, svm_msk, svm_out_img,
                                   inner_width, inner_height,
                                   kernel, &kernel_evt);
    CHECK_ERROR(status, "SVMHandleInnerRegions");

    status = FineSVM_HandleAllBoundries(wrapper, svm_in_img, svm_msk, svm_out_img, img_size,
                                        msk_size);
    CHECK_ERROR(status, "SVMHandleAllBoundries");

    if(wait_kernel)
    {
        clWaitForEvents(1, &kernel_evt);
    }

    std::memcpy(wrapper->out_img, svm_out_img, img_size*sizeof(real32));
    
    TestCaseFinished(&loop_timer);
    
    clSVMFree(context, svm_in_img);
    clSVMFree(context, svm_msk);
    clSVMFree(context, svm_out_img);

    // Print2DArray("Output Image: ", wrapper->out_img, wrapper->img_width,
    //              wrapper->img_height);
    
    //std::cout << "Fine (SVM) Convolution FINISH!" << std::endl;
    //std::cout << "======================" << std::endl;

    return SUCCESS;
}

int FineSVM_AllocateSVMObjects(real32** svm_in_img, real32** svm_msk, real32** svm_out_img,
                               uint32 img_size, uint32 msk_size)
{
    (*svm_in_img) = (real32*)clSVMAlloc(context,
                                        CL_MEM_READ_WRITE
                                        | CL_MEM_SVM_FINE_GRAIN_BUFFER
                                        | CL_MEM_SVM_ATOMICS,
                                        img_size*sizeof(real32), 0);
    CHECK_ALLOCATION(*svm_in_img, "in_img");
        
    (*svm_msk) = (real32*)clSVMAlloc(context,
                                     CL_MEM_READ_WRITE
                                     | CL_MEM_SVM_FINE_GRAIN_BUFFER
                                     | CL_MEM_SVM_ATOMICS,
                                     msk_size*sizeof(real32), 0);
    CHECK_ALLOCATION(*svm_msk, "msk");

    (*svm_out_img) = (real32*)clSVMAlloc(
        context,
        CL_MEM_READ_WRITE
        | CL_MEM_SVM_FINE_GRAIN_BUFFER
        | CL_MEM_SVM_ATOMICS,
        img_size*sizeof(real32), 0);
    CHECK_ALLOCATION(*svm_out_img, "out_img");
    
    return SUCCESS;
}

int FineSVM_HandleAllBoundries(ConvWrapper* wrapper, real32* svm_in_img,
                               real32* svm_msk, real32* svm_out_img,
                               uint32 img_size, uint32 msk_size)
{
    cl_int status = 0;
    
    // Map SVM objects into the host address space to copy input
    // data and handle the boundaries
    
    ConvWrapper temp;
    temp.in_img = svm_in_img;
    temp.img_width = wrapper->img_width;
    temp.img_height = wrapper->img_height;
    // it doesn't really matter but anyway!
    temp.msk = svm_msk;
    temp.msk_width = wrapper->msk_width;
    temp.msk_height = wrapper->msk_height;
    temp.out_img = svm_out_img;
    HandleAllBoundries(&temp);
        
    return status;
}
