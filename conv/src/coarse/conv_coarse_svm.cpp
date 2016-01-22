#include <coarse/conv_coarse_svm.h>

#include <CL/cl.h>

int CoarseSVM_ApplyStencil(ConvWrapper* wrapper, bool use_unrolled)
{
    /*
    std::cout << "Coarse (SVM) Convolution START!" << std::endl;

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

    /*
    _img_width = wrapper->img_width;
    _img_height = wrapper->img_height;
    _msk_width = wrapper->msk_width;
    _msk_height = wrapper->msk_height;
    */
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
    
    status = AllocateSVMObjects(&svm_in_img, &svm_msk, &svm_out_img, img_size, msk_size);
    CHECK_ERROR(status, "AllocateSVMObjects");
    status = SVMHandleAllBoundries(wrapper, svm_in_img, svm_msk, svm_out_img, img_size,
                                   msk_size);
    CHECK_ERROR(status, "SVMHandleAllBoundries");

    cl_event kernel_evt;
    status = SVMHandleInnerRegions(wrapper, svm_in_img, svm_msk, svm_out_img,
                                   inner_width, inner_height,
                                   use_unrolled, &kernel_evt);
    CHECK_ERROR(status, "SVMHandleInnerRegions");
    status = CopyOutputFromSVM(wrapper->out_img, svm_out_img, img_size);
    CHECK_ERROR(status, "CopyOutputFromSVM");

    TestCaseFinished(&loop_timer);
    
    clSVMFree(context, svm_in_img);
    clSVMFree(context, svm_msk);
    clSVMFree(context, svm_out_img);

    // Print2DArray("Output Image: ", wrapper->out_img, wrapper->img_width,
    //              wrapper->img_height);
    
    //std::cout << "Coarse (SVM) Convolution FINISH!" << std::endl;
    //std::cout << "======================" << std::endl;

    return SUCCESS;
}

int AllocateSVMObjects(real32** svm_in_img, real32** svm_msk, real32** svm_out_img,
                       uint32 img_size, uint32 msk_size)
{
    (*svm_in_img) = (real32*)clSVMAlloc(context, CL_MEM_READ_WRITE,
                                     img_size*sizeof(real32), 0);
    CHECK_ALLOCATION(*svm_in_img, "in_img");
        
    (*svm_msk) = (real32*)clSVMAlloc(context, CL_MEM_READ_WRITE,
                                  msk_size*sizeof(real32), 0);
    CHECK_ALLOCATION(*svm_msk, "msk");

    (*svm_out_img) = (real32*)clSVMAlloc(
        context, CL_MEM_READ_WRITE, img_size*sizeof(real32), 0);
    CHECK_ALLOCATION(*svm_out_img, "out_img");
    
    return SUCCESS;
}

int SVMHandleAllBoundries(ConvWrapper* wrapper, real32* svm_in_img,
                          real32* svm_msk, real32* svm_out_img,
                          uint32 img_size, uint32 msk_size)
{
    cl_int status;
    
    // Map SVM objects into the host address space to copy input
    // data and handle the boundaries
    status = clEnqueueSVMMap(queue, CL_TRUE,
                             CL_MAP_WRITE_INVALIDATE_REGION,
                             svm_in_img, img_size*sizeof(real32),
                             0, NULL, NULL);
    CHECK_OPENCL_ERROR(status, "clEnqueueSVMMap");

    // NOTE: we would have to do this anyway. if not for copying the
    // input image, will be for initialization
    std::memcpy(svm_in_img, wrapper->in_img, img_size*sizeof(real32));

    status = clEnqueueSVMMap(queue, CL_TRUE,
                             CL_MAP_WRITE_INVALIDATE_REGION,
                             svm_msk, msk_size*sizeof(real32),
                             0, NULL, NULL);
    CHECK_OPENCL_ERROR(status, "clEnqueueSVMMap");
    std::memcpy(svm_msk, wrapper->msk, msk_size*sizeof(real32));

    status = clEnqueueSVMMap(queue, CL_TRUE,
                             CL_MAP_WRITE_INVALIDATE_REGION,
                             svm_out_img, img_size*sizeof(real32),
                             0, NULL, NULL);
    CHECK_OPENCL_ERROR(status, "clEnqueueSVMMap");

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
        
    status = clEnqueueSVMUnmap(queue, svm_in_img, 0, NULL, NULL);
    CHECK_OPENCL_ERROR(status, "clEnqueueSVMUnmap");
    status = clEnqueueSVMUnmap(queue, svm_msk, 0, NULL, NULL);
    CHECK_OPENCL_ERROR(status, "clEnqueueSVMUnmap");
    status = clEnqueueSVMUnmap(queue, svm_out_img, 0, NULL, NULL);
    CHECK_OPENCL_ERROR(status, "clEnqueueSVMUnmap");
    
    return status;
}

int SVMHandleInnerRegions(ConvWrapper* wrapper, real32* svm_in_img, real32* svm_msk,
                          real32* svm_out_img, uint32 inner_width, uint32 inner_height,
                          bool use_unrolled, cl_event* kernel_evt)
{
    int status;
    cl_kernel kernel;
        
    if(use_unrolled)
    {
        status = SetupKernel("conv_kernel_unrolled.cl",
                             "conv_kernel", &kernel);
    }
    else
    {
        status = SetupKernel("conv_kernel.cl", "conv_kernel", &kernel);
    }
    CHECK_ERROR(status, "SetupKernel");

    int arg_idx = 0;
    status = clSetKernelArgSVMPointer(kernel, arg_idx++, svm_in_img);
    CHECK_OPENCL_ERROR(status, "clSetKernelArgSVMPointer");

    status = clSetKernelArg(kernel, arg_idx++, sizeof(uint32), &wrapper->img_width);
    CHECK_OPENCL_ERROR(status, "clSetKernelArg");

    status = clSetKernelArg(kernel, arg_idx++, sizeof(uint32), &wrapper->img_height);
    CHECK_OPENCL_ERROR(status, "clSetKernelArg");
    
    status = clSetKernelArgSVMPointer(kernel,  arg_idx++, svm_msk);
    CHECK_OPENCL_ERROR(status, "clSetKernelArgSVMPointer");

    if(!use_unrolled)
    {
        status = clSetKernelArg(kernel, arg_idx++, sizeof(uint32), &wrapper->msk_width);
        CHECK_OPENCL_ERROR(status, "clSetKernelArg");
    }   

    status = clSetKernelArgSVMPointer(kernel, arg_idx++, svm_out_img);
    CHECK_OPENCL_ERROR(status, "clSetKernelArgSVMPointer");

    // NOTE: despite having a max group size of 256 (16x16) on this
    // machine, the kernel fails to produce the correct results when
    // using svm. the max power of 2 that it accepts is 1!! the reason
    // is that the work group must be a multiple of the local
    // size. this can be overcome in coarse SVM because we will have
    // to map and unmpa any way but in fine grained access
    
    // as Arsene suggested I justed added an if condition to the
    // kernel code for now. only a few number of groups will diverge
    // making the overhead neglegible
    size_t local_dim = 16;
    
    size_t global[2];
    global[0] = (((inner_width - 1) / local_dim) + 1) * local_dim;
    global[1] = (((inner_height - 1) / local_dim) + 1) * local_dim;

    size_t local[2];
    local[0] = local_dim;
    local[1] = local_dim;

    status = clEnqueueNDRangeKernel(queue, kernel, 2, NULL, global,
                                    local, 0, NULL, kernel_evt);
    CHECK_OPENCL_ERROR(status, "clEnqueueNDRangeKernel");

    return SUCCESS;
}

cl_int CopyOutputFromSVM(real32* out_img, real32* svm_out_img, uint32 img_size)
{
    cl_int status;
    status = clEnqueueSVMMap(queue, CL_TRUE, CL_MAP_READ,
                             svm_out_img, img_size*sizeof(real32),
                             0, NULL, NULL);
    CHECK_OPENCL_ERROR(status, "clEnqueueSVMMap");
    
    std::memcpy(out_img, svm_out_img, img_size*sizeof(real32));

    status = clEnqueueSVMUnmap(queue, svm_out_img, 0, NULL, NULL);
    CHECK_OPENCL_ERROR(status, "clEnqueueSVMUnmap");
    
    return status;
}
