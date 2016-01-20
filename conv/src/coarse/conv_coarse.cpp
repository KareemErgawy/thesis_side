#include <coarse/conv_coarse.h>

int Coarse_ApplyStencil(real32* in_img, uint32 img_width,
                        uint32 img_height, real32* msk,
                        uint32 msk_width, uint32 msk_height,
                        real32* out_img, bool use_urolled)
{
    std::cout << "Coarse (non-SVM) Convolution START!" << std::endl;

    if(use_urolled)
    {
        std::cout << "Urolled kernel used";
    }
    else
    {
        std::cout << "Urolled kernel used NOT used";        
    }
    std::cout << std::endl;

    //Print2DArray("Input Image: ", in_img, img_width, img_height);
    _in_img = in_img;
    _img_width = img_width;
    _img_height = img_height;
    _msk = msk;
    _msk_width = msk_width;
    _msk_height = msk_height;
    _out_img = out_img;
    _half_w = msk_width / 2;
    _half_h = msk_height / 2;

    uint32 img_size = _img_width * _img_height;
    uint32 inner_width = (_img_width - (_half_w*2));
    uint32 inner_height = (_img_height - (_half_h*2));
    uint32 inner_size = inner_width * inner_height;
    uint32 msk_size = _msk_width * _msk_height;

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
                                  in_img, 0, NULL, NULL);
    CHECK_OPENCL_ERROR(status, "clEnqueueWriteBuffer");

    status = clEnqueueWriteBuffer(queue, msk_buf, CL_TRUE, 0,
                                  msk_size*sizeof(real32),
                                  msk, 0, NULL, NULL);
    CHECK_OPENCL_ERROR(status, "clEnqueueWriteBuffer");

    cl_kernel kernel;
    
    if(use_urolled)
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
                            &img_width);
    CHECK_OPENCL_ERROR(status, "clSetKernelArg");
        
    status = clSetKernelArg(kernel, arg_idx++, sizeof(cl_mem),
                            &msk_buf);
    CHECK_OPENCL_ERROR(status, "clSetKernelArg");

    if(!use_urolled)
    {
        status = clSetKernelArg(kernel, arg_idx++, sizeof(uint32),
                                &msk_width);
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
    
    status = clEnqueueNDRangeKernel(queue, kernel, 2, NULL,
                                    global,
                                    local, 0, NULL, NULL);
    CHECK_OPENCL_ERROR(status, "clEnqueueNDRangeKernel");

    status = clEnqueueReadBuffer(queue, out_img_buf, CL_TRUE, 0,
                                 img_size*sizeof(real32), out_img,
                                 0, NULL, NULL);
    CHECK_OPENCL_ERROR(status, "clEnqueueReadBuffer");                               
 
    // TODO: try to use clEnqueueNativeKernel here
    HandleAllBoundries();

    //Print2DArray("Output Image: ", out_img, img_width, img_height);
    std::cout << "Coarse (non-SVM) Convolution FINISH!" << std::endl;
    std::cout << "======================" << std::endl;

    return SUCCESS;
}
