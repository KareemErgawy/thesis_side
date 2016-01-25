#include <seq/conv_seq.h>
#include <cassert>

void Seq_ApplyStencil(ConvWrapper* wrapper)
{
//    std::cout << "Sequential Convolution START!" << std::endl;
    //Print2DArray("Input Image: ", in_img, img_width, img_height);

    TestCaseStarted(&loop_timer);

    /*
    _in_img = wrapper->in_img;
    _img_width = wrapper->img_width;
    _img_height = wrapper->img_height;
    _msk = wrapper->msk;
    _msk_width = wrapper->msk_width;
    _msk_height = wrapper->msk_height;
    _out_img = wrapper->out_img;
    _half_w = wrapper->msk_width / 2;
    _half_h = wrapper->msk_height / 2;
    */

    uint32 half_w = wrapper->msk_width / 2;
    uint32 half_h = wrapper->msk_height / 2;
    
    HandleAllBoundries(wrapper);
    
    // inner regions
    for(uint32 c = half_w ; c < wrapper->img_width-half_w ; c++)
    {
        for(uint32 r = half_h ; r < wrapper->img_height-half_h ; r++)
        {
            ApplyStencilInnerStep(wrapper, r, c);
        }
    }

    TestCaseFinished(&loop_timer);
    //Print2DArray("Output Image: ", out_img, img_width, img_height);
    //std::cout << "Sequential Convolution FINISH!" << std::endl;
    //std::cout << "======================" << std::endl;
}

internal
void HandleAllBoundries(ConvWrapper* wrapper)
{    
    uint32 c, r;
    
    uint32 half_w = wrapper->msk_width / 2;
    uint32 half_h = wrapper->msk_height / 2;
    
    // top boundary
    for(c = 0 ; c < wrapper->img_width ; c++)
    {
        for(r = 0 ; r < half_h ; r++)
        {
            ApplyStencilBoundaryStep(wrapper, r, c);
        }
    }

    // left boundary
    for(c = 0 ; c < half_w ; c++)
    {
        for(r = half_h ; r < wrapper->img_height-half_h ; r++)
        {
            ApplyStencilBoundaryStep(wrapper, r, c);
        }
    }
    
    // bottom boundary
    for(c = 0 ; c < wrapper->img_width ; c++)
    {
        for(r = wrapper->img_height-1 ; r >= wrapper->img_height-half_h ; r--)
        {
            ApplyStencilBoundaryStep(wrapper, r, c);
        }
    }

    // right boundary
    for(c = wrapper->img_width-1 ; c >= wrapper->img_width-half_w ; c--)
    {
        for(r = half_h ; r < wrapper->img_height-half_h ; r++)
        {
            ApplyStencilBoundaryStep(wrapper, r, c);
        }
    }    
}

internal
void ApplyStencilInnerStep(ConvWrapper* wrapper, uint32 row, uint32 col)
{    
    int32 half_w = wrapper->msk_width / 2;
    int32 half_h = wrapper->msk_height / 2;

    wrapper->out_img[(row*wrapper->img_width) + col] = 0;
        
    for(int32 c = -half_w ; c <= half_w ; c++)
    {
        for(int32 r = -half_h ; r <= half_h ; r++)
        {
            wrapper->out_img[(row*wrapper->img_width)+col]
                += (wrapper->in_img[((row+r)*wrapper->img_width)+col+c]
                    *wrapper->msk[((half_h+r)*wrapper->msk_width)+half_w+c]);
        }
    }
}

internal
void ApplyStencilBoundaryStep(ConvWrapper* wrapper, uint32 row, uint32 col)
{
    int32 half_w = wrapper->msk_width / 2;
    int32 half_h = wrapper->msk_height / 2;

    wrapper->out_img[(row*wrapper->img_width)+col] = 0;
    
    for(int32 c = -half_w ; c <= half_w ; c++)
    {
        for(int32 r = -half_h ; r <= half_h ; r++)
        {
            int32 r1 = r + row;
            int32 c1 = c + col;

//            std::cout << col << " " << c1 << " " << c << " ";

            /*
            // Mirror if < 0
            r1 = (r1 < 0) ? (-r-1) : r1;
            c1 = (c1 < 0) ? (-c-1) : c1;
            // Mirror if > dim
            r1 = (r1 >= (int32)wrapper->img_height) ? wrapper->img_height-r : r1;
            c1 = (c1 >= (int32)wrapper->img_width) ? wrapper->img_width-c : c1;
            */
            
            // Mirror if < 0
            r1 = (r1 < 0) ? 0 : r1;
            c1 = (c1 < 0) ? 0 : c1;
            // Mirror if > dim
            r1 = (r1 >= (int32)wrapper->img_height) ? wrapper->img_height-1 : r1;
            c1 = (c1 >= (int32)wrapper->img_width) ? wrapper->img_width-1 : c1;

            
//            std::cout << c1 << std::endl;
            assert(r1 >= 0);
            assert(c1 >= 0);
            assert(r1 < (int32)wrapper->img_height);
            assert(c1 < (int32)wrapper->img_width);

            wrapper->out_img[(row*wrapper->img_width)+col]
                += (wrapper->in_img[(r1*wrapper->img_width)+c1]
                    *wrapper->msk[((half_h+r)*wrapper->msk_width)+half_w+c]);
        }
    }
}
