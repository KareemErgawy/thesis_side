__kernel void LocalSort_Kernel(__global uint* temp_keys,
                               __global uint* keys, uint start_bit,
			       uint digits)
{
    __local local_keys[256];

    int local_id = get_local_id(0);
    int global_id = get_global_id(0);

    local_keys[local_id] = keys[global_id];
    work_group_barrier(CLK_LOCAL_MEM_FENCE);
}
