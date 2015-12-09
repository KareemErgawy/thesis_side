__kernel void conv_kernel(__global float* in_img, int img_width,
                          int img_height, __global float* msk,
			  int msk_width, int msk_height,
			  __global float* out_img)
{
    int half_w = msk_width / 2;
    int half_h = msk_height / 2;

    int col = get_global_id(0) + half_w;
    int row = get_global_id(1) + half_h;

    out_img[(row*img_width)+col] = 0;

    // TODO: unroll this loop
    for(int c = -half_w ; c <= half_w ; c++)
    {
        for(int r = -half_h ; r <= half_h ; r++)
        {
            out_img[(row*img_width)+col]
                += (in_img[((row+r)*img_width)+col+c]
                   *msk[((half_h+r)*msk_width)+half_w+c]);
        }
    }

//    printf("%d %f\n", ((row*img_width)+col),
//           out_img[(row*img_width)+col]);
}
