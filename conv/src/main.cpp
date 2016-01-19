#include <utils.cpp>

#include <seq/conv_seq.cpp>
#include <coarse/conv_coarse.cpp>
#include <coarse/conv_coarse_svm.cpp>

#define ReportResult(img_name, test_name)               \
    if(CompareImages(out_img_seq, img_name, img_width,  \
                     img_height))                       \
    {                                                   \
        std::cout << "~~~~~~~~~~~~~~" << std::endl      \
                  << "TEST PASSED [" #test_name "]!"   \
                  << std::endl                          \
                  << "~~~~~~~~~~~~~~" << std::endl;     \
    }                                                   \
    else                                                \
    {                                                   \
        std::cout << "~~~~~~~~~~~~~~" << std::endl      \
                  << "TEST FAILED [" #test_name "]!"   \
                  << std::endl                          \
                  << "~~~~~~~~~~~~~~" << std::endl;     \
    }


static const char* inputImagePath = "../Images/cat.bmp";

// TODO Generate random large image to compare timings
int main()
{
    int status;
    SetupOptions setup_options = {};
    setup_options.required_platform_subname = "Intel";
    status = SetupOpenCL(&setup_options);
    CHECK_ERROR(status, "SetupOpenCL");
    //
    // Cat input case
    //
    int32 img_width;
    int32 img_height;
    real32* in_img = readBmpFloat(inputImagePath, &img_height,
                                  &img_width);

    //
    // Test matrix case
    //
    //int32 img_width = 7;
    //int32 img_height = 7;
    //real32* in_img = (real32*)malloc(sizeof(real32)*img_width
     //                                *img_height);
    //GenerateTestImage(in_img, img_width, img_height);

    uint32 msk_width = 5;
    uint32 msk_height = 5;
    real32* msk = (real32*)malloc(
        sizeof(real32)*msk_width*msk_height);
    GenerateGaussianBlurFilter_5X5(msk);
    //GenerateTestMask(msk, msk_width, msk_height);

    //
    // Sequential implementation test
    //
    real32* out_img_seq = (real32*)malloc(sizeof(real32)*img_width
                                          *img_height);
    Seq_ApplyStencil(in_img, img_width, img_height, msk, msk_width,
                     msk_height, out_img_seq);
    writeBmpFloat(out_img_seq, "cat_seq.bmp", img_height,
                  img_width, inputImagePath);

    std::cout  << std::endl;
   
    //
    // Coarse non-SVM test
    //
    real32* out_img_coarse = (real32*)malloc(sizeof(real32)*img_width
                                             *img_height);
    Coarse_ApplyStencil(in_img, img_width, img_height, msk,
                        msk_width, msk_height, out_img_coarse,
                        false);
    writeBmpFloat(out_img_coarse, "cat_coarse.bmp", img_height,
                  img_width, inputImagePath);

    if(CompareImages(out_img_seq, out_img_coarse, img_width,
                     img_height))
    {
        std::cout << "TEST PASSED [Coarse (non-SVM)]!"
                  << std::endl;
    }
    else
    {
        std::cout << "TEST FAILED [Coarse (non-SVM)]!"
                  << std::endl;
    }

    std::cout  << std::endl;
    
    //
    // Coarse SVM test
    //
    real32* out_img_coarse_svm = (real32*)malloc(
        sizeof(real32)*img_width*img_height);
    CoarseSVM_ApplyStencil(in_img, img_width, img_height, msk,
                           msk_width, msk_height, out_img_coarse_svm,
                           false);
    writeBmpFloat(out_img_coarse, "cat_coarse_svm.bmp", img_height,
                 img_width, inputImagePath);

    if(CompareImages(out_img_seq, out_img_coarse_svm, img_width,
                     img_height))
    {
        std::cout << "TEST PASSED [Coarse (SVM)]!"
                  << std::endl;
    }
    else
    {
        std::cout << "TEST FAILED [Coarse (SVM)]!"
                  << std::endl;
    }

    std::cout << std::endl;
       
    //
    // Coarse non-SVM test (unrolled)
    //
    free(out_img_coarse);    
    out_img_coarse = (real32*)malloc(sizeof(real32)*img_width
                                             *img_height);
    Coarse_ApplyStencil(in_img, img_width, img_height, msk,
                        msk_width, msk_height, out_img_coarse);
    writeBmpFloat(out_img_coarse, "cat_coarse_unrolled.bmp",
                  img_height,
                  img_width, inputImagePath);

    if(CompareImages(out_img_seq, out_img_coarse, img_width,
                     img_height))
    {
        std::cout << "TEST PASSED [Coarse (non-SVM)]!"
                  << std::endl;
    }
    else
    {
        std::cout << "TEST FAILED [Coarse (non-SVM)]!"
                  << std::endl;
    }

    std::cout  << std::endl;
    
    //
    // Coarse SVM test (unrolled)
    //
    free(out_img_coarse_svm);
    out_img_coarse_svm = (real32*)malloc(
        sizeof(real32)*img_width*img_height);
    CoarseSVM_ApplyStencil(in_img, img_width, img_height, msk,
                           msk_width, msk_height, out_img_coarse_svm);
    writeBmpFloat(out_img_coarse, "cat_coarse_svm_unrolled.bmp",
                  img_height,
                  img_width, inputImagePath);

    if(CompareImages(out_img_seq, out_img_coarse_svm, img_width,
                     img_height))
    {
        std::cout << "TEST PASSED [Coarse (SVM)]!"
                  << std::endl;
    }
    else
    {
        std::cout << "TEST FAILED [Coarse (SVM)]!"
                  << std::endl;
    }

    std::cout << std::endl;

    
    free(in_img);
    free(msk);
    free(out_img_seq);
    free(out_img_coarse);
    free(out_img_coarse_svm);
    
    return 0;
}
