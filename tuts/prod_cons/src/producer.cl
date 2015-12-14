__constant sampler_t sampler =
    CLK_NORMALIZED_COORDS_FALSE |
    CLK_FILTER_NEAREST          |
    CLK_ADDRESS_CLAMP_TO_EDGE;

__kernel
void producerKernel(image2d_t __read_only inputImage,
                    pipe __write_only float* outoutPipe,
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

    write_pipe(outoutPipe, &sum);
}