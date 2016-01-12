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

    size_t local_id = get_local_id(0);
    size_t global_id = get_global_id(0);

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

uint CalcDigitValue(uint x, uint cur_digit, digits)
{
    return ((x >> (cur_digit*digits)) & 0x7);
}

__kernel void Histogram_Kernel(__global uint* tile_offsets,
                               __global uint* counters,
			       __global uint* temp_keys,
			       uint start_bit, uint digits, uint radix,
			       uint tile_size, uint num_tiles)
{
    __local uint local_digit_vals[256];
    __local uint local_tile_offsets[256];
    __local uint local_counters[256];
    __local uint local_next[256];

    size_t local_id = get_local_id(0);
    size_t global_id = get_global_id(0);
    size_t group_id = get_group_id(0);

    local_digit_vals[local_id] = CalcDigitValue(temp_keys[global_id],
                                               start_bit, digits);
    work_group_barrier(CLK_LOCAL_MEM_FENCE);
    local_next[local_id] = 0;
    local_tile_offsets[local_id] = 0;
    	
    if(local_id > 0)
    {
        if(local_digit_vals[local_id] != local_digit_vals[local_id-1])
	{
	    local_next[local_digit_vals[local_id-1]]
	        = local_digit_vals[local_id];
	    local_tile_offsets[local_digit_vals[local_id]]
	        = local_id;
	}
    }

    work_group_barrier(CLK_LOCAL_MEM_FENCE);

    if(local_id < (radix - 1))
    {
        local_counters[local_id]
	    = local_tile_offsets[local_next[local_id]]
	      - local_tile_offsets[local_id];
    }
    else if(local_id == (radix - 1))
    {
        local_counters[local_id] = get_local_size(0)
	                           - local_tile_offsets[local_id];
    }

    work_group_barrier(CLK_LOCAL_MEM_FENCE);

    if(local_id < radix)
    {
        tile_offsets[(radix * group_id) + local_id]
	    = local_tile_offsets[local_id];
	counters[(num_tiles * local_id) + group_id]
	    = local_counters[local_id];
    }
}

__kernel void InitAuxSum_Kernel(__global uint* counters_sum,
                           __global uint* counters,
		           __global uint* aux_sum)
{
    __local local_counters[256];
    size_t local_id = get_local_id(0);
    size_t global_id = get_global_id(0);
    size_t group_id = get_group_id(0);
    size_t linear_id = (local_id * get_num_groups(0)) + group_id;

    local_counters[local_id] = counters[linear_id];

    work_group_barrier(CLK_LOCAL_MEM_FENCE);
    
    counters_sum[linear_id] =  work_group_scan_exclusive_add
                                   (local_counters[local_id]);

    work_group_barrier(CLK_LOCAL_MEM_FENCE);

    // TODO instead of that if, we can do that on the host
    if(local_id == (get_local_size(0) - 1))
    {
        aux_sum[group_id] = counters_sum[linear_id]
	                    + local_counters[local_id];
    }
}

__kernel void AddAuxSum_Kernel(__global uint* counters_sum,
                               __global uint* aux_sum)
{
    size_t group_id = get_group_id(0);

    if(group_id > 0)
    {
        size_t local_id = get_local_id(0);
	size_t group_id = get_group_id(0);
        size_t linear_id = (local_id * get_num_groups(0)) + group_id;
        counters_sum[linear_id] = counters_sum[linear_id]
	                          + aux_sum[group_id - 1];
    }
}