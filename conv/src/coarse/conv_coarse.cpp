#include <coarse/conv_coarse.h>

int Coarse_ApplyStencil(ConvWrapper* wrapper, bool use_unrolled)
{
    /*std::cout << "Coarse (non-SVM) Convolution START!" << std::endl;

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
    
    //Print2DArray("Input Image: ", in_img, img_width, img_height);
    /*
    _in_img = wrapper->in_img;
    _img_width = wrapper->img_width;
    _img_height = wrapper->img_height;
    _msk = wrapper->msk;
    _msk_width = wrapper->msk_width;
    _msk_height = wrapper->msk_height;
    _out_img = wrapper->out_img;
    _half_w = _msk_width / 2;
    _half_h = _msk_height / 2;
    */

    uint32 half_w = wrapper->msk_width / 2;
    uint32 half_h = wrapper->msk_height / 2;
    uint32 img_size = wrapper->img_width * wrapper->img_height;
    uint32 inner_width = (wrapper->img_width - (half_w*2));
    uint32 inner_height = (wrapper->img_height - (half_h*2));
    uint32 inner_size = inner_width * inner_height;
    uint32 msk_size = wrapper->msk_width * wrapper->msk_height;

    cl_int status;
    cl_mem in_img_buf = clCreateBuffer (context, CL_MEM_READ_ONLY,
                                        img_size*sizeof(real32),
                                        NULL, &status);
    CHECK_OPENCL_ERROR(status, "clCreateBuffer");
        
    cl_mem msk_buf = clCreateBuffer (context, CL_MEM_READ_ONLY,
                                     msk_size*sizeof(real32),
                                     NULL, &status);
    CHECK_OPENCL_ERROR(status, "clCreateBuffer");

    cl_mem out_img_buf = clCreateBuffer(context, CL_MEM_READ_ONLY,
                                        img_size*sizeof(real32),
                                        NULL, &status);
    CHECK_OPENCL_ERROR(status, "clCreateBuffer");
        
    status = clEnqueueWriteBuffer(queue, in_img_buf, CL_TRUE, 0,
                                  img_size*sizeof(real32),
                                  wrapper->in_img, 0, NULL, NULL);
    CHECK_OPENCL_ERROR(status, "clEnqueueWriteBuffer");

    status = clEnqueueWriteBuffer(queue, msk_buf, CL_TRUE, 0,
                                  msk_size*sizeof(real32),
                                  wrapper->msk, 0, NULL, NULL);
    CHECK_OPENCL_ERROR(status, "clEnqueueWriteBuffer");

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
    status = clSetKernelArg(kernel, arg_idx++, sizeof(cl_mem),
                            &in_img_buf);
    CHECK_OPENCL_ERROR(status, "clSetKernelArg");
        
    status = clSetKernelArg(kernel, arg_idx++, sizeof(uint32),
                            &wrapper->img_width);
    CHECK_OPENCL_ERROR(status, "clSetKernelArg");

    status = clSetKernelArg(kernel, arg_idx++, sizeof(uint32),
                            &wrapper->img_height);
    CHECK_OPENCL_ERROR(status, "clSetKernelArg");
        
    status = clSetKernelArg(kernel, arg_idx++, sizeof(cl_mem),
                            &msk_buf);
    CHECK_OPENCL_ERROR(status, "clSetKernelArg");

    if(!use_unrolled)
    {
        status = clSetKernelArg(kernel, arg_idx++, sizeof(uint32),
                                &wrapper->msk_width);
        CHECK_OPENCL_ERROR(status, "clSetKernelArg");
    }
    
    status = clSetKernelArg(kernel, arg_idx++, sizeof(cl_mem),
                            &out_img_buf);
    CHECK_OPENCL_ERROR(status, "clSetKernelArg");
    
    size_t local_dim = 16;
    
    size_t global[2];
    global[0] = (((inner_width - 1) / local_dim) + 1) * local_dim;
    global[1] = (((inner_height - 1) / local_dim) + 1) * local_dim;

    size_t local[2];
    local[0] = local_dim;
    local[1] = local_dim;

    cl_event evt;
    status = clEnqueueNDRangeKernel(queue, kernel, 2, NULL,
                                    global,
                                    local, 0, NULL, &evt);
    CHECK_OPENCL_ERROR(status, "clEnqueueNDRangeKernel");

    status = clEnqueueReadBuffer(queue, out_img_buf, CL_TRUE, 0,
                                 img_size*sizeof(real32), wrapper->out_img,
                                 0, NULL, NULL);
    CHECK_OPENCL_ERROR(status, "clEnqueueReadBuffer");                               
 
    // TODO: try to use clEnqueueNativeKernel here
    HandleAllBoundries(wrapper);

    clWaitForEvents(1, &evt);

    TestCaseFinished(&loop_timer);

    status = clReleaseMemObject(in_img_buf);
    CHECK_OPENCL_ERROR(status, "clReleaseMemObject");

    status = clReleaseMemObject(msk_buf);
    CHECK_OPENCL_ERROR(status, "clReleaseMemObject");
    
    status = clReleaseMemObject(out_img_buf);
    CHECK_OPENCL_ERROR(status, "clReleaseMemObject");
    
    //Print2DArray("Output Image: ", out_img, img_width, img_height);
    //std::cout << "Coarse (non-SVM) Convolution FINISH!" << std::endl;
    //std::cout << "======================" << std::endl;

    return SUCCESS;
}
