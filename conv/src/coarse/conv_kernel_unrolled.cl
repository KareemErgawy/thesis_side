#define pixel_contribution() out_img[outIdx] +=                 \
                             (in_img[((row+r)*img_width)+col+c] \
                              *msk[((half_msk_dim+r)*msk_width) \
                                    +half_msk_dim+c]);

// NOTE: it is assumed that the mask kernel is 5x5 in order to be
// able to unroll the loop
__kernel void conv_kernel(__global float* in_img, int img_width,
                          __global float* msk,
			  __global float* out_img)
{
    __constant int msk_width = 5;
    __constant int half_msk_dim = 2;
    
    int col = get_global_id(0) + half_msk_dim;
    int row = get_global_id(1) + half_msk_dim;

    // TODO: unroll this loop
    int outIdx = (row*img_width)+col;
    out_img[outIdx] = 0;
    
    int c, r;

    c = -half_msk_dim;
    r = -half_msk_dim;
    pixel_contribution();
    r++;
    pixel_contribution();
    r++;
    pixel_contribution();
    r++;
    pixel_contribution();
    r++;
    pixel_contribution();

    c++;
    r = -half_msk_dim;
    pixel_contribution();
    r++;
    pixel_contribution();
    r++;
    pixel_contribution();
    r++;
    pixel_contribution();
    r++;
    pixel_contribution();

    c++;
    r = -half_msk_dim;
    pixel_contribution();
    r++;
    pixel_contribution();
    r++;
    pixel_contribution();
    r++;
    pixel_contribution();
    r++;
    pixel_contribution();

    c++;
    r = -half_msk_dim;
    pixel_contribution();
    r++;
    pixel_contribution();
    r++;
    pixel_contribution();
    r++;
    pixel_contribution();
    r++;
    pixel_contribution();

    c++;
    r = -half_msk_dim;
    pixel_contribution();
    r++;
    pixel_contribution();
    r++;
    pixel_contribution();
    r++;
    pixel_contribution();
    r++;
    pixel_contribution();
}