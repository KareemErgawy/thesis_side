#include "gpu/rs_gpu.h"

void RadixSort_GPU(uint32* keys, uint32 len, uint32 num_digits)
{
    tile_size = 256;
    CreateBuffers(keys, len);
    
    // TODO for now, every kernel is called separately with its
    // inputs/outputs passed from/to the host. try to avoid that

    // NOTE: reads and writes needed by evey kernel are done at the
    // kernel invokation function below (see LocalSort for example)

    for(uint32 cur_digit=0 ; cur_digit<1/*num_digits*/ ; cur_digit++)
    {
        uint32 start_bit = cur_digit * digits;
        std::cout << start_bit << std::endl;
        LocalSort(start_bit, keys, len);
        Histogram(start_bit, keys, len);
    }
    
    // for(uint32 i=0 ; i<len ; i++)
    // {
    //     std::cout << keys[i] << ", ";
    // }

    // std::cout << std::endl;
}

int CreateBuffers(uint32* keys, uint32 len)
{
    cl_int status;
    uint32 m = radix * (((len - 1) / tile_size) + 1);
    
    keys_buf = clCreateBuffer(context, CL_MEM_READ_ONLY,
                            len*sizeof(uint32),
                            NULL, &status);
    CHECK_OPENCL_ERROR(status, "clCreateBuffer");

    temp_keys_buf = clCreateBuffer(context, CL_MEM_READ_WRITE,
                                   len*sizeof(uint32),
                                   NULL, &status);
    CHECK_OPENCL_ERROR(status, "clCreateBuffer");

    tile_offsets_buf = clCreateBuffer(context, CL_MEM_READ_WRITE,
                                   m*sizeof(uint32),
                                   NULL, &status);
    CHECK_OPENCL_ERROR(status, "clCreateBuffer");
    
    counters_buf = clCreateBuffer(context, CL_MEM_READ_WRITE,
                                   m*sizeof(uint32),
                                   NULL, &status);
    CHECK_OPENCL_ERROR(status, "clCreateBuffer");

    counters_sum_buf = clCreateBuffer(context, CL_MEM_READ_WRITE,
                                   m*sizeof(uint32),
                                   NULL, &status);
    CHECK_OPENCL_ERROR(status, "clCreateBuffer");
}

int LocalSort(uint32 start_bit, uint32* keys, uint32 len)
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
    size_t local = tile_size;

    status = clEnqueueNDRangeKernel(queue, kernel, 1, NULL, &global,
                                    &local, 0, NULL, NULL);
    CHECK_OPENCL_ERROR(status, "clEnqueueNDRangeKernel");

    // status = clEnqueueReadBuffer(queue, temp_keys_buf, CL_TRUE, 0,
    //                              len*sizeof(uint32), keys,
    //                              0, NULL, NULL);
    // CHECK_OPENCL_ERROR(status, "clEnqueueReadBuffer");
}

int Histogram(uint32 start_bit, uint32* keys, uint32 len)
{
    cl_int status;

    cl_kernel kernel;
    status = SetupKernel("Histogram_Kernel",
                         &kernel);
    CHECK_ERROR(status, "SetupKernel");

    int arg_idx = 0;
    status = clSetKernelArg(kernel, arg_idx++, sizeof(cl_mem),
                            &tile_offsets_buf);
    CHECK_OPENCL_ERROR(status, "clSetKernelArg");

    status = clSetKernelArg(kernel, arg_idx++, sizeof(cl_mem),
                            &counters_buf);
    CHECK_OPENCL_ERROR(status, "clSetKernelArg");    

    status = clSetKernelArg(kernel, arg_idx++, sizeof(cl_mem),
                            &temp_keys_buf);
    CHECK_OPENCL_ERROR(status, "clSetKernelArg");    

    status = clSetKernelArg(kernel, arg_idx++, sizeof(uint32),
                            &start_bit);
    CHECK_OPENCL_ERROR(status, "clSetKernelArg");

    status = clSetKernelArg(kernel, arg_idx++, sizeof(uint32),
                            &digits);
    CHECK_OPENCL_ERROR(status, "clSetKernelArg");

    status = clSetKernelArg(kernel, arg_idx++, sizeof(uint32),
                            &radix);
    CHECK_OPENCL_ERROR(status, "clSetKernelArg");    

    status = clSetKernelArg(kernel, arg_idx++, sizeof(uint32),
                            &tile_size);
    CHECK_OPENCL_ERROR(status, "clSetKernelArg");

    uint32 num_tiles = (((len - 1) / tile_size) + 1);
    status = clSetKernelArg(kernel, arg_idx++, sizeof(uint32),
                            &num_tiles);
    CHECK_OPENCL_ERROR(status, "clSetKernelArg");

    size_t global = len;
    size_t local = tile_size;

    status = clEnqueueNDRangeKernel(queue, kernel, 1, NULL, &global,
                                    &local, 0, NULL, NULL);
    CHECK_OPENCL_ERROR(status, "clEnqueueNDRangeKernel");

    // status = clEnqueueReadBuffer(queue, temp_keys_buf, CL_TRUE, 0,
    //                              len*sizeof(uint32), keys,
    //                              0, NULL, NULL);
    // CHECK_OPENCL_ERROR(status, "clEnqueueReadBuffer");

    uint32 m = radix * (((len - 1) / tile_size) + 1);

    // uint32* temp = (uint32*) malloc(sizeof(uint32) * m);

    // status = clEnqueueReadBuffer(queue, tile_offsets_buf, CL_TRUE, 0,
    //                              m*sizeof(uint32), temp,
    //                              0, NULL, NULL);
    // CHECK_OPENCL_ERROR(status, "clEnqueueReadBuffer");

    // for(uint32 i=0 ; i<m ; i++)
    // {
    //     std::cout << temp[i] << ", ";
    // }

    // std::cout << std::endl;

    // free(temp);
}
