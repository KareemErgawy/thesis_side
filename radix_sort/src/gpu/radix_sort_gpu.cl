// See http://http.developer.nvidia.com/GPUGems3/gpugems3_ch39.html
void Split(__local uint local_keys[256], uint cur_bit, int local_id)
{
    __local uint e[256];
    __local uint f[256];
    __local uint t[256];
    __local uint d[256];
    __local uint temp[256];
    
    e[local_id] = !(local_keys[local_id] & (1 << cur_bit));
    f[local_id] =  work_group_scan_exclusive_add(e[local_id]);
    
    // TODO do we really need the fence here, or is
    // work_group_scan_exclusive_add guaranteed to by synced?
    work_group_barrier(CLK_LOCAL_MEM_FENCE);

    size_t local_size = get_local_size(0);
    uint total_falses = e[local_size-1] + f[local_size-1];
    t[local_id] = local_id - f[local_id] + total_falses;
    d[local_id] = e[local_id] ? f[local_id] : t[local_id];

    temp[local_id] = local_keys[local_id];

    work_group_barrier(CLK_LOCAL_MEM_FENCE);
    local_keys[d[local_id]] = temp[local_id];
}

__kernel void LocalSort_Kernel(__global uint* temp_keys,
                               __global uint* keys, uint start_bit,
			       uint digits)
{
    __local uint local_keys[256];

    int local_id = get_local_id(0);
    int global_id = get_global_id(0);

    local_keys[local_id] = keys[global_id];
    work_group_barrier(CLK_LOCAL_MEM_FENCE);

//    temp_keys[global_id] =  work_group_scan_inclusive_add(
//                                local_keys[local_id]);

    for(uint cur_bit = start_bit ; cur_bit < start_bit+digits ;
        cur_bit++)
    {
        Split(local_keys, cur_bit, local_id);
	work_group_barrier(CLK_LOCAL_MEM_FENCE);
    }

    temp_keys[global_id] = local_keys[local_id];
    // TODO: is neccessary?
    work_group_barrier(CLK_LOCAL_MEM_FENCE);
}