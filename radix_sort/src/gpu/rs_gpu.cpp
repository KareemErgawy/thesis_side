#include "gpu/rs_gpu.h"

int GPU_RadixSort(uint32* keys, uint32 len, uint32 num_digits)
{
//    std::cout << std::hex;
    tile_size = 256;
    CreateBuffers(keys, len);
    
    // TODO for now, every kernel is called separately with its
    // inputs/outputs passed from/to the host. try to avoid that

    cl_int status;
    status = clEnqueueWriteBuffer(queue, keys_buf, CL_TRUE, 0,
                                  len*sizeof(uint32),
                                  keys, 0, NULL, NULL);
    CHECK_OPENCL_ERROR(status, "clEnqueueWriteBuffer");

//    PrintBufferContents_Uint32(keys_buf, len, "keys", 16);
    
    for(uint32 cur_digit=0 ; cur_digit<num_digits ; cur_digit++)
    {
        uint32 start_bit = cur_digit * bits_per_digit;
        //std::cout << "start bit: " << start_bit << std::endl;
        LocalSort(start_bit, keys, len);
        Histogram(start_bit, keys, len);
        Rank(len);
        Scatter(start_bit, len);
    }

    status = clEnqueueReadBuffer(queue, keys_buf, CL_TRUE, 0,
                                 len*sizeof(uint32),
                                 keys, 0, NULL, NULL);
    CHECK_OPENCL_ERROR(status, "clEnqueueReadBuffer");
//    std::cout << std::dec;
}

int CreateBuffers(uint32* keys, uint32 len)
{
    cl_int status;
    uint32 num_tiles = (((len - 1) / tile_size) + 1);
    uint32 m = radix * num_tiles;
    
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

    aux_sum_buf = clCreateBuffer(context, CL_MEM_READ_WRITE,
                                 num_tiles*sizeof(uint32),
                                 NULL, &status);
    CHECK_OPENCL_ERROR(status, "clCreateBuffer");
}

int LocalSort(uint32 start_bit, uint32* keys, uint32 len)
{
    cl_int status;

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
                            &bits_per_digit);
    CHECK_OPENCL_ERROR(status, "clSetKernelArg");

    size_t global = len;
    size_t local = tile_size;
    
    status = clEnqueueNDRangeKernel(queue, kernel, 1, NULL, &global,
                                    &local, 0, NULL, NULL);
    CHECK_OPENCL_ERROR(status, "clEnqueueNDRangeKernel");

    //PrintBufferContents_Uint32(temp_keys_buf, len, "temp keys", 16);
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
                            &bits_per_digit);
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

    uint32 m = radix * (((len - 1) / tile_size) + 1);
    //PrintBufferContents_Uint32(counters_buf, m, "counters", (((len - 1) / tile_size) + 1));

    //PrintBufferContents_Uint32(tile_offsets_buf, m, "tile offsets", radix);
}

int Rank(uint32 len)
{
    cl_int status;

    cl_kernel kernel;
    status = SetupKernel("InitAuxSum_Kernel", &kernel);
    CHECK_ERROR(status, "SetupKernel");
    
    int arg_idx = 0;
    status = clSetKernelArg(kernel, arg_idx++, sizeof(cl_mem),
                            &counters_sum_buf);
    CHECK_OPENCL_ERROR(status, "clSetKernelArg");

    status = clSetKernelArg(kernel, arg_idx++, sizeof(cl_mem),
                            &counters_buf);
    CHECK_OPENCL_ERROR(status, "clSetKernelArg");    
    
    status = clSetKernelArg(kernel, arg_idx++, sizeof(cl_mem),
                            &aux_sum_buf);
    CHECK_OPENCL_ERROR(status, "clSetKernelArg");

    uint32 num_tiles = (((len - 1) / tile_size) + 1);
    size_t global = radix * num_tiles;

    size_t local = 256;

    uint32 m = radix * (((len - 1) / tile_size) + 1);
    
//    std::cout << "global: " << global << ", local: " << local
//              << std::endl;
    
    status = clEnqueueNDRangeKernel(queue, kernel, 1, NULL, &global,
                                    &local, 0, NULL, NULL);
    CHECK_OPENCL_ERROR(status, "clEnqueueNDRangeKernel");

    //PrintBufferContents_Uint32(aux_sum_buf, num_tiles, "aux sum",
//                               num_tiles);

    //PrintBufferContents_Uint32(counters_sum_buf, m, "counters_sum",
    //                             num_tiles);
    
    status = SetupKernel("AddAuxSum_Kernel", &kernel);
    CHECK_ERROR(status, "SetupKernel");

    arg_idx = 0;
    status = clSetKernelArg(kernel, arg_idx++, sizeof(cl_mem),
                            &counters_sum_buf);
    CHECK_OPENCL_ERROR(status, "clSetKernelArg");

    status = clSetKernelArg(kernel, arg_idx++, sizeof(cl_mem),
                            &aux_sum_buf);
    CHECK_OPENCL_ERROR(status, "clSetKernelArg");

    status = clEnqueueNDRangeKernel(queue, kernel, 1, NULL, &global,
                                    &local, 0, NULL, NULL);
    CHECK_OPENCL_ERROR(status, "clEnqueueNDRangeKernel");

    //PrintBufferContents_Uint32(counters_sum_buf, m, "counters_sum",
    //                           num_tiles);
}

int Scatter(uint32 start_bit, uint32 len)
{
    cl_int status;

    cl_kernel kernel;
    status = SetupKernel("Scatter_Kernel", &kernel);
    CHECK_ERROR(status, "SetupKernel");

    int arg_idx = 0;
    status = clSetKernelArg(kernel, arg_idx++, sizeof(cl_mem),
                            &keys_buf);
    CHECK_OPENCL_ERROR(status, "clSetKernelArg");

    status = clSetKernelArg(kernel, arg_idx++, sizeof(cl_mem),
                            &temp_keys_buf);
    CHECK_OPENCL_ERROR(status, "clSetKernelArg");

    status = clSetKernelArg(kernel, arg_idx++, sizeof(cl_mem),
                            &tile_offsets_buf);
    CHECK_OPENCL_ERROR(status, "clSetKernelArg");

    status = clSetKernelArg(kernel, arg_idx++, sizeof(cl_mem),
                            &counters_sum_buf);
    CHECK_OPENCL_ERROR(status, "clSetKernelArg");

    status = clSetKernelArg(kernel, arg_idx++, sizeof(uint32),
                            &start_bit);
    CHECK_OPENCL_ERROR(status, "clSetKernelArg");

    status = clSetKernelArg(kernel, arg_idx++, sizeof(uint32),
                            &bits_per_digit);
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

    // std::cout << "global: " << global << ", local: " << local
    //            << std::endl;
    
    status = clEnqueueNDRangeKernel(queue, kernel, 1, NULL, &global,
                                    &local, 0, NULL, NULL);
    CHECK_OPENCL_ERROR(status, "clEnqueueNDRangeKernel");

    //PrintBufferContents_Uint32(keys_buf, len, "keys", 16);
}
