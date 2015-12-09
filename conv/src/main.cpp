#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <iomanip>

#include <Utils/bmp-utils.c>
#include <utils.cpp>
#include <seq/conv_seq.cpp>
#include <coarse/conv_coarse.cpp>

static const char* inputImagePath = "../Images/cat.bmp";

int main()
{
    int32 img_width;
    int32 img_height;
    real32* in_img = readBmpFloat(inputImagePath, &img_height,
                                  &img_width);
    
    uint32 msk_width = 5;
    uint32 msk_height = 5;
    real32* msk = (real32*)malloc(
        sizeof(real32)*msk_width*msk_height);
    GenerateGaussianBlurFilter_5X5(msk);

    //
    // Sequential implementation test
    //
    real32* out_img_seq = (real32*)malloc(sizeof(real32)*img_width
                                          *img_height);
    Seq_ApplyStencil(in_img, img_width, img_height, msk, msk_width,
                     msk_height, out_img_seq);
    writeBmpFloat(out_img_seq, "cat_seq.bmp", img_height,
                  img_width, inputImagePath);

    //
    // Coarse non-SVM test
    //
    real32* out_img_coarse = (real32*)malloc(sizeof(real32)*img_width
                                             *img_height);
    Coarse_ApplyStencil(in_img, img_width, img_height, msk,
                        msk_width, msk_height, out_img_coarse);
    writeBmpFloat(out_img_coarse, "cat_coarse.bmp", img_height,
                  img_width, inputImagePath);

    if(CompareImages(out_img_seq, out_img_coarse, img_width,
                      img_height))
    {
        std::cout << "TEST PASSED [Coarse (non-SVM)]!" << std::endl;
    }
    else
    {
        std::cout << "TEST FAILED [Coarse (non-SVM)]!" << std::endl;
    }
    
    free(in_img);
    free(msk);
    free(out_img_seq);
    free(out_img_coarse);

    return 0;
}
