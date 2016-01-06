#if !defined(RS_GPU_H)
#define RS_GPU_H

// OpenCL buffers
global_variable cl_mem keys_buf;
global_variable cl_mem temp_keys_buf;

void RadixSort_GPU(uint32* in, uint32 len, uint32 num_digits);

void CreateBuffers();

#endif
