#include <gpu/conv_gpu_opt.h>

int GPU_Opt_ApplyStencil(ConvWrapper* wrapper, cl_kernel kernels[9])
{    
    TestCaseStarted(&loop_timer);
    
    uint32 half_w = wrapper->msk_width / 2;
    uint32 half_h = wrapper->msk_height / 2;
    uint32 img_size = wrapper->img_width * wrapper->img_height;
    uint32 msk_size = wrapper->msk_width * wrapper->msk_height;

    cl_int status;
    cl_mem in_img_buf = clCreateBuffer (context, CL_MEM_READ_ONLY,
                                        img_size*sizeof(real32),
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

    kernel_config configs[9] = {kernel_config{{  32,    4}, {32, 4}},
                                kernel_config{{4032,    4}, {32, 4}},
                                kernel_config{{  32,    4}, {32, 4}},
                                
                                kernel_config{{  32, 4088}, {32, 4}},
                                kernel_config{{4032, 4088}, {32, 4}},
                                kernel_config{{  32, 4088}, {32, 4}},

                                kernel_config{{  32,    4}, {32, 4}},
                                kernel_config{{4032,    4}, {32, 4}},
                                kernel_config{{  32,    4}, {32, 4}}};
    
    for(int k_idx=0 ; k_idx<9 ; ++k_idx)
    {
        cl_kernel kernel = kernels[k_idx];
        int arg_idx = 0;
        status = clSetKernelArg(kernel, arg_idx++, sizeof(cl_mem),
                                &out_img_buf);
        CHECK_OPENCL_ERROR(status, "clSetKernelArg");

        status = clSetKernelArg(kernel, arg_idx++, sizeof(cl_mem),
                                &in_img_buf);
        CHECK_OPENCL_ERROR(status, "clSetKernelArg");

        status = clEnqueueNDRangeKernel(queue, kernel, 2, NULL,
                                        configs[k_idx].global,
                                        configs[k_idx].local, 0, NULL, NULL);
        CHECK_OPENCL_ERROR(status, "clEnqueueNDRangeKernel");
    }
    
    status = clEnqueueReadBuffer(queue, out_img_buf, CL_TRUE, 0,
                                 img_size*sizeof(real32), wrapper->out_img,
                                 0, NULL, NULL);
    CHECK_OPENCL_ERROR(status, "clEnqueueReadBuffer");                               
 
    TestCaseFinished(&loop_timer);

    status = clReleaseMemObject(in_img_buf);
    CHECK_OPENCL_ERROR(status, "clReleaseMemObject");
    
    status = clReleaseMemObject(out_img_buf);
    CHECK_OPENCL_ERROR(status, "clReleaseMemObject");
    
    // Print2DArray("Output Image: ", wrapper->out_img,
    //              wrapper->img_width,
    //              wrapper->img_height);

    return SUCCESS;
}
