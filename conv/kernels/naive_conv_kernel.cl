__kernel void naive_conv_kernel(__global float* in_img, int img_width,
                          int img_height,
                          __global float* msk, int msk_width,
			  __global float* out_img)
{
    int half_msk_dim = msk_width / 2;
    int col = get_global_id(0);
    int row = get_global_id(1);

    if((col >= img_width)
       || (row >= img_height))
    {
        return;
    }
    
    int out_index = (row*img_width)+col;

    out_img[out_index] = 0;

    // overlapped tiling! here we need cells from neighboring tiles.
    // check "High-Performance Code Generation for Stencil
    // Computations on GPU Architectures"
    for(int c = -half_msk_dim ; c <= half_msk_dim ; c++)
    {
        for(int r = -half_msk_dim ; r <= half_msk_dim ; r++)
        {
            int r1 = r + row;
            int c1 = c + col;

            // Mirror if < 0
            r1 = (r1 < 0) ? (-r-1) : r1;
            c1 = (c1 < 0) ? (-c-1) : c1;
            // Mirror if > dim
            r1 = (r1 >= img_height) ? img_height-r : r1;
            c1 = (c1 >= img_width) ? img_width-c : c1;

            out_img[out_index]
                += (in_img[(r1*img_width)+c1]
                   *msk[((half_msk_dim+r)*msk_width)
		        +half_msk_dim+c]);
        }	
    }
}
