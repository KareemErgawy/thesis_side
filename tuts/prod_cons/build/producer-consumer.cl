__constant sampler_t sampler =
    CLK_NORMALIZED_COORDS_FALSE |
    CLK_FILTER_NEAREST          |
    CLK_ADDRESS_CLAMP_TO_EDGE;

__kernel
void producerKernel(image2d_t __read_only inputImage,
                    __write_only pipe float outputPipe,
		    __constant float* filter,
		    int filterWidth)
{
    int column = get_global_id(0);
    int row = get_global_id(1);

    int halfWidth = (int)(filterWidth / 2);
    float sum = 0.0f;
    int filterIdx = 0;
    int2 coords;

    for(int i=-halfWidth ; i<=halfWidth ; i++)
    {
        coords.y = row + i;

        for(int j=-halfWidth ; j<=halfWidth ; j++)
	{
	    coords.x = column + j;
	    float4 pixel;
	    pixel = read_imagef(inputImage, sampler, coords);
	    sum += pixel.x * filter[filterIdx++];
	}
    }

    reserve_id_t res_id;
    res_id = reserve_write_pipe(outputPipe, 1);

    if(is_valid_reserve_id(res_id))
    {
        if(write_pipe(outputPipe, res_id, 0, &sum) == 0)
	{
	    commit_write_pipe(outputPipe, res_id);
	}
    }
}

__kernel
void consumerKernel(pipe __read_only float inputPipe,
                    int totalPixels,
		    __global int* histogram)
{
    int pixelCnt;
    float pixel;

    for(pixelCnt=0 ; pixelCnt<totalPixels ; pixelCnt++)
    {
        reserve_id_t res_id;
        while(1)
	{
            res_id = reserve_read_pipe(inputPipe, 1);

            if(is_valid_reserve_id(res_id))
     	    {
	        if(read_pipe(inputPipe, res_id, 0, &pixel) == 0)
	        {
	            commit_read_pipe(inputPipe, res_id);
		    break;
	        }
	    }
        }

	histogram[(int)pixel]++;
    }
}