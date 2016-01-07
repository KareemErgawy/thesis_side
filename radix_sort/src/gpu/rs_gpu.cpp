#include "gpu/rs_gpu.h"

void RadixSort_GPU(uint32* keys, uint32 len, uint32 num_digits)
{
    CreateBuffers(keys, len);

    uint32* temp_keys = (uint32*) malloc(len*sizeof(uint32));
    
    // TODO for now, every kernel is called separately with its
    // inputs/outputs passed from/to the host. try to avoid that

    // NOTE: reads and writes needed by evey kernel are done at the
    // kernel invokation function below (see LocalSort for example)
    for(uint32 cur_digit=0 ; cur_digit<num_digits ; cur_digit++)
    {
        uint32 start_bit = cur_digit * digits;
        LocalSort(start_bit, keys, temp_keys, len);
    }

    for(uint32 i=0 ; i<len ; i++)
    {
        std::cout << temp_keys[i] << ",";
    }

    std::cout << std::endl;
}

int CreateBuffers(uint32* keys, uint32 len)
{
    cl_int status;
    
    keys_buf = clCreateBuffer(context, CL_MEM_READ_ONLY,
                            len*sizeof(uint32),
                            NULL, &status);
    CHECK_OPENCL_ERROR(status, "clCreateBuffer");

    temp_keys_buf = clCreateBuffer(context, CL_MEM_READ_WRITE,
                                   len*sizeof(uint32),
                                   NULL, &status);
    CHECK_OPENCL_ERROR(status, "clCreateBuffer");
}

int LocalSort(uint32 start_bit, uint32* keys, uint32* temp_keys, uint32 len)
{
    cl_int status;

    status = clEnqueueWriteBuffer(queue, keys_buf, CL_TRUE, 0,
                                  len*sizeof(uint32),
                                  keys, 0, NULL, NULL);
    CHECK_OPENCL_ERROR(status, "clEnqueueWriteBuffer");

    cl_kernel kernel;
    status = SetupKernel("radix_sort_gpu.cl", "LocalSort_Kernel",
                         &kernel);
    CHECK_ERROR(status, "SetupKernel");

    int arg_idx = 0;
    status = clSetKernelArg(kernel, arg_idx++, sizeof(cl_mem),
                            &temp_keys_buf);
    CHECK_OPENCL_ERROR(status, "clSetKernelArg");

    status = clSetKernelArg(kernel, arg_idx++, sizeof(cl_mem),
                            &keys_buf);
    CHECK_OPENCL_ERROR(status, "clSetKernelArg");

    status = clSetKernelArg(kernel, arg_idx++, sizeof(uint32),
                            &start_bit);
    CHECK_OPENCL_ERROR(status, "clSetKernelArg");

    status = clSetKernelArg(kernel, arg_idx++, sizeof(uint32),
                            &digits);
    CHECK_OPENCL_ERROR(status, "clSetKernelArg");

    size_t global = len;
    size_t local = 256;

    status = clEnqueueNDRangeKernel(queue, kernel, 1, NULL, &global,
                                    &local, 0, NULL, NULL);
    CHECK_OPENCL_ERROR(status, "clEnqueueNDRangeKernel");

    status = clEnqueueReadBuffer(queue, temp_keys_buf, CL_TRUE, 0,
                                 len*sizeof(uint32), temp_keys,
                                 0, NULL, NULL);
    CHECK_OPENCL_ERROR(status, "clEnqueueReadBuffer");
}
