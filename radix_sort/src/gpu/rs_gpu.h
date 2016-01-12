#if !defined(RS_GPU_H)
#define RS_GPU_H

// OpenCL buffers
global_variable cl_mem keys_buf;
global_variable cl_mem temp_keys_buf;
global_variable cl_mem tile_offsets_buf;
global_variable cl_mem counters_buf;
global_variable cl_mem counters_sum_buf;
global_variable cl_mem aux_sum_buf;

global_variable uint32 tile_size;

void RadixSort_GPU(uint32* in, uint32 len, uint32 num_digits);

int CreateBuffers(uint32* keys, uint32 len);

int LocalSort(uint32 start_bit, uint32* keys, uint32 len);

int Histogram(uint32 start_bit, uint32* keys, uint32 len);

int Rank(uint32 len);

int Scatter();

#endif
