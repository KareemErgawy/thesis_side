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
    GenerateTestImage(in_img, img_width, img_height);
    
    real32* out_img = (real32*)malloc(sizeof(real32)*img_width
                                      *img_height);
    real32* out_img2 = (real32*)malloc(sizeof(real32)*img_width
                                      *img_height);

    uint32 msk_width = 5;
    uint32 msk_height = 5;

    real32* msk = (real32*)malloc(sizeof(real32)*msk_width
                                   *msk_height);
    GenerateTestMask(msk, msk_width, msk_height);
    
    Seq_ApplyStencil(in_img, img_width, img_height, msk, msk_width,
                 msk_height, out_img);
    
    Coarse_ApplyStencil(in_img, img_width, img_height, msk,
                        msk_width, msk_height, out_img2);
    
    return 0;
}
