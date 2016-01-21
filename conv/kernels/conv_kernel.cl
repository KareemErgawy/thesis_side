__kernel void conv_kernel(__global float* in_img, int img_width,
                          int img_height,
                          __global float* msk, int msk_width,
			  __global float* out_img)
{
    int half_msk_dim = msk_width / 2;
    int col = get_global_id(0) + half_msk_dim;
    int row = get_global_id(1) + half_msk_dim;

    if((col >= (img_width - half_msk_dim))
       || (row >= (img_height - half_msk_dim)))
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
            out_img[out_index]
                += (in_img[((row+r)*img_width)+col+c]
                   *msk[((half_msk_dim+r)*msk_width)
		        +half_msk_dim+c]);
        }	
    }
}
