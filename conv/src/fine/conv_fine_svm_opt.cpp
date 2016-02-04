#include <fine/conv_fine_svm_opt.h>

int FineSVM_Opt_ApplyStencil(ConvWrapper* wrapper, cl_kernel kernels[8],
                             cl_kernel inner_kernel)
{
    TestCaseStarted(&loop_timer);

    cl_int status;
    uint32 img_size = wrapper->img_width * wrapper->img_height;

    real32* svm_in_img = (real32*)clSVMAlloc(context,
                                        CL_MEM_READ_WRITE
                                        | CL_MEM_SVM_FINE_GRAIN_BUFFER
                                        | CL_MEM_SVM_ATOMICS,
                                        img_size*sizeof(real32), 0);
    CHECK_ALLOCATION(svm_in_img, "in_img");
    
    real32* svm_out_img = (real32*)clSVMAlloc(context,
                                         CL_MEM_READ_WRITE
                                         | CL_MEM_SVM_FINE_GRAIN_BUFFER
                                         | CL_MEM_SVM_ATOMICS,
                                         img_size*sizeof(real32), 0);
    CHECK_ALLOCATION(svm_out_img, "out_img");

    std::memcpy(svm_in_img, wrapper->in_img, img_size*sizeof(real32));
    
    kernel_config configs[8] = {kernel_config{{  32,    4}, {32, 4}},
                                kernel_config{{4032,    4}, {32, 4}},
                                kernel_config{{  32,    4}, {32, 4}},
                                
                                kernel_config{{  32, 4088}, {32, 4}},
                                kernel_config{{  32, 4088}, {32, 4}},

                                kernel_config{{  32,    4}, {32, 4}},
                                kernel_config{{4032,    4}, {32, 4}},
                                kernel_config{{  32,    4}, {32, 4}}};

    kernel_config inner_config = kernel_config{{4032, 4088}, {32, 4}};

    cl_event kernel_evts[9];
    
    for(int k_idx=0 ; k_idx<8 ; ++k_idx)
    {
        cl_kernel kernel = kernels[k_idx];
        int arg_idx = 0;
        status = clSetKernelArgSVMPointer(kernel, arg_idx++, svm_out_img);
        CHECK_OPENCL_ERROR(status, "clSetKernelArgSVMPointer");

        status = clSetKernelArgSVMPointer(kernel, arg_idx++, svm_in_img);
        CHECK_OPENCL_ERROR(status, "clSetKernelArgSVMPointer");

        status = clEnqueueNDRangeKernel(cpu_queue, kernel, 2, NULL,
                                        configs[k_idx].global,
                                        configs[k_idx].local, 0,
                                        NULL, &kernel_evts[k_idx]);
        CHECK_OPENCL_ERROR(status, "clEnqueueNDRangeKernel");
    }

    int arg_idx = 0;
    status = clSetKernelArgSVMPointer(inner_kernel, arg_idx++, svm_out_img);
    CHECK_OPENCL_ERROR(status, "clSetKernelArgSVMPointer");

    status = clSetKernelArgSVMPointer(inner_kernel, arg_idx++, svm_in_img);
    CHECK_OPENCL_ERROR(status, "clSetKernelArgSVMPointer");

    status = clEnqueueNDRangeKernel(gpu_queue, inner_kernel, 2, NULL,
                                    inner_config.global,
                                    inner_config.local, 0,
                                    NULL, &kernel_evts[8]);
    CHECK_OPENCL_ERROR(status, "clEnqueueNDRangeKernel");

    clWaitForEvents(9, kernel_evts);

    std::memcpy(wrapper->out_img, svm_out_img, img_size*sizeof(real32));
    
    TestCaseFinished(&loop_timer);

    clSVMFree(context, svm_in_img);
    clSVMFree(context, svm_out_img);

    return SUCCESS;
}
