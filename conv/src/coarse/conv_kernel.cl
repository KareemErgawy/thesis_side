__kernel void conv_kernel(__global float* in_img, int img_width,
                          __global float* msk, int msk_width,
			  __global float* out_img)
{
    int half_msk_dim = msk_width / 2;
    int col = get_global_id(0) + half_msk_dim;
    int row = get_global_id(1) + half_msk_dim;

    out_img[(row*img_width)+col] = 0;
    
    for(int c = -half_msk_dim ; c <= half_msk_dim ; c++)
    {
        for(int r = -half_msk_dim ; r <= half_msk_dim ; r++)
        {
            out_img[(row*img_width)+col]
                += (in_img[((row+r)*img_width)+col+c]
                   *msk[((half_msk_dim+r)*msk_width)
		        +half_msk_dim+c]);
        }	
    }
}
