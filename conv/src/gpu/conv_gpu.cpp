#include <gpu/conv_gpu.h>

int GPU_ApplyStencil(ConvWrapper* wrapper, cl_kernel kernel)
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
        
    cl_mem msk_buf = clCreateBuffer (context, CL_MEM_READ_ONLY,
                                     msk_size*sizeof(real32),
                                     NULL, &status);
    CHECK_OPENCL_ERROR(status, "clCreateBuffer");

    cl_mem out_img_buf = clCreateBuffer(context, CL_MEM_READ_ONLY,
                                        img_size*sizeof(real32),
                                        NULL, &status);
    CHECK_OPENCL_ERROR(status, "clCreateBuffer");
        
    status = clEnqueueWriteBuffer(gpu_queue, in_img_buf, CL_TRUE, 0,
                                  img_size*sizeof(real32),
                                  wrapper->in_img, 0, NULL, NULL);
    CHECK_OPENCL_ERROR(status, "clEnqueueWriteBuffer");

    status = clEnqueueWriteBuffer(gpu_queue, msk_buf, CL_TRUE, 0,
                                  msk_size*sizeof(real32),
                                  wrapper->msk, 0, NULL, NULL);
    CHECK_OPENCL_ERROR(status, "clEnqueueWriteBuffer");
    
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

    status = clSetKernelArg(kernel, arg_idx++, sizeof(uint32),
                            &wrapper->msk_width);
    CHECK_OPENCL_ERROR(status, "clSetKernelArg");
    
    status = clSetKernelArg(kernel, arg_idx++, sizeof(cl_mem),
                            &out_img_buf);
    CHECK_OPENCL_ERROR(status, "clSetKernelArg");
    
    size_t local_dim = 16;
    
    size_t global[2];
    global[0] = (((wrapper->img_width - 1) / local_dim) + 1) * local_dim;
    global[1] = (((wrapper->img_height - 1) / local_dim) + 1) * local_dim;

    size_t local[2];
    local[0] = local_dim;
    local[1] = local_dim;

    cl_event evt;
    status = clEnqueueNDRangeKernel(gpu_queue, kernel, 2, NULL,
                                    global,
                                    local, 0, NULL, &evt);
    CHECK_OPENCL_ERROR(status, "clEnqueueNDRangeKernel");

    status = clEnqueueReadBuffer(gpu_queue, out_img_buf, CL_TRUE, 0,
                                 img_size*sizeof(real32), wrapper->out_img,
                                 0, NULL, NULL);
    CHECK_OPENCL_ERROR(status, "clEnqueueReadBuffer");                               
 
    clWaitForEvents(1, &evt);

    TestCaseFinished(&loop_timer);

    status = clReleaseMemObject(in_img_buf);
    CHECK_OPENCL_ERROR(status, "clReleaseMemObject");

    status = clReleaseMemObject(msk_buf);
    CHECK_OPENCL_ERROR(status, "clReleaseMemObject");
    
    status = clReleaseMemObject(out_img_buf);
    CHECK_OPENCL_ERROR(status, "clReleaseMemObject");
    
    // Print2DArray("Output Image: ", wrapper->out_img,
    //              wrapper->img_width,
    //              wrapper->img_height);

    return SUCCESS;
}
