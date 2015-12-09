#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <iomanip>

#include <utils.cpp>
#include <seq/conv_seq.cpp>
#include <coarse/conv_coarse.cpp>

int main()
{
    uint32 img_width = 7;
    uint32 img_height = 7;
    real32* in_img = new real32[img_width*img_height];

    uint32 c, r;
    
    for(c=0 ; c<img_width ; c++)
    {
        for(r=0 ; r<img_height ; r++)
        {
            if((r == (img_height / 2)) && (c == (img_width / 2)))
            {
                in_img[(r*img_width) + c] = 10.f;
            }
            else
            {
                in_img[(r*img_width) + c] = 1.f;
            }
        }
    }

    Print2DArray("Input Image", in_img, img_width, img_height);
    
    real32* out_img = (real32*)malloc(sizeof(real32)*img_width
                                      *img_height);
    real32* out_img2 = (real32*)malloc(sizeof(real32)*img_width
                                      *img_height);

    uint32 msk_width = 5;
    uint32 msk_height = 5;

    real32* msk = (real32*)malloc(sizeof(real32)*msk_width
                                   *msk_height);

    real32 total = 0;
    for(c=0 ; c<msk_width ; c++)
    {
        for(r=0 ; r<msk_height ; r++)
        {
            msk[(r*msk_width) + c] = 1.f/(msk_width*msk_height);
            total += msk[(r*msk_width) + c];
        }
    }
    
    Seq_ApplyStencil(in_img, img_width, img_height, msk, msk_width,
                 msk_height, out_img);
    Print2DArray("Output Image", out_img, img_width, img_height);
    
    Coarse_ApplyStencil(in_img, img_width, img_height, msk,
                        msk_width, msk_height, out_img2);
    Print2DArray("Output Image 2", out_img2, img_width, img_height);
    return 0;
}
