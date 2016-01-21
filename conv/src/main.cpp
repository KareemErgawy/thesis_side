#include <utils.cpp>

#include <seq/conv_seq.cpp>
#include <coarse/conv_coarse.cpp>
#include <coarse/conv_coarse_svm.cpp>

#define ReportResult(img_name, test_name)               \
    if(CompareImages(out_img_seq, img_name, img_width,  \
                     img_height))                       \
    {                                                   \
        std::cout << "~~~~~~~~~~~~~~" << std::endl      \
                  << "TEST PASSED [" #test_name "]!"    \
                  << std::endl                          \
                  << "~~~~~~~~~~~~~~" << std::endl;     \
    }                                                   \
    else                                                \
    {                                                   \
        std::cout << "~~~~~~~~~~~~~~" << std::endl      \
                  << "TEST FAILED [" #test_name "]!"    \
                  << std::endl                          \
                  << "~~~~~~~~~~~~~~" << std::endl;     \
    }                                                   \
    std::cout << std::endl << std::endl;

#define SIMPLE 0
#define CAT    1
#define RAND   2

#define CASE   RAND

static const char* inputImagePath = "../Images/cat.bmp";

// TODO Generate random large image to compare timings
int main()
{
    int status;
    SetupOptions setup_options = {};
    setup_options.required_platform_subname = "Intel";
    status = SetupOpenCL(&setup_options);
    CHECK_ERROR(status, "SetupOpenCL");

#if (CASE == CAT)
    //
    // Cat input case
    //
    int32 img_width;
    int32 img_height;
    real32* in_img = readBmpFloat(inputImagePath, &img_height,
                                  &img_width);
#elif (CASE == RAND)
    //
    // Random matrix case
    //
    // TODO test the effects of the relationship between this image
    // size and this machine's computing power (generate an image that
    // fits perfectly and exactly in the avaiable compute units)
    int32 img_width = 4096;
    int32 img_height = 4096;
    real32* in_img = (real32*)malloc(sizeof(real32)*img_width
                                     *img_height);
    GenerateRandomImage(in_img, img_width, img_height);    
#else
    //
    // Test matrix case
    //
    int32 img_width = 7;
    int32 img_height = 7;
    real32* in_img = (real32*)malloc(sizeof(real32)*img_width
                                     *img_height);
    GenerateTestImage(in_img, img_width, img_height);
#endif
    
    uint32 msk_width = 5;
    uint32 msk_height = 5;
    real32* msk = (real32*)malloc(
        sizeof(real32)*msk_width*msk_height);

#if ((CASE == CAT) || (CASE == RAND))
    GenerateGaussianBlurFilter_5X5(msk);
#else
    GenerateTestMask(msk, msk_width, msk_height);
#endif
    
    //
    // Sequential implementation test
    //
    real32* out_img_seq = (real32*)malloc(sizeof(real32)*img_width
                                          *img_height);
    Seq_ApplyStencil(in_img, img_width, img_height, msk, msk_width,
                     msk_height, out_img_seq);
    
#if (CASE == CAT)
    writeBmpFloat(out_img_seq, "cat_seq.bmp", img_height,
                  img_width, inputImagePath);
#endif
    std::cout  << std::endl;
   
    //
    // Coarse non-SVM test
    //
    real32* out_img_coarse = (real32*)malloc(sizeof(real32)*img_width
                                             *img_height);
    Coarse_ApplyStencil(in_img, img_width, img_height, msk,
                        msk_width, msk_height, out_img_coarse,
                        false);
#if (CASE == CAT)
    writeBmpFloat(out_img_coarse, "cat_coarse.bmp", img_height,
                  img_width, inputImagePath);
#endif
    ReportResult(out_img_coarse, Coarse non-SVM);

    //
    // Coarse SVM test
    //
    real32* out_img_coarse_svm = (real32*)malloc(
        sizeof(real32)*img_width*img_height);
    CoarseSVM_ApplyStencil(in_img, img_width, img_height, msk,
                           msk_width, msk_height, out_img_coarse_svm,
                           false);
#if (CASE == CAT)
    writeBmpFloat(out_img_coarse_svm, "cat_coarse_svm.bmp", img_height,
                 img_width, inputImagePath);
#endif
    ReportResult(out_img_coarse_svm, Coarse SVM);
       
    //
    // Coarse non-SVM test (unrolled)
    //
    free(out_img_coarse);    
    out_img_coarse = (real32*)malloc(sizeof(real32)*img_width
                                             *img_height);
    Coarse_ApplyStencil(in_img, img_width, img_height, msk,
                        msk_width, msk_height, out_img_coarse);
#if (CASE == CAT)
    writeBmpFloat(out_img_coarse, "cat_coarse_unrolled.bmp",
                  img_height,
                  img_width, inputImagePath);
#endif
    ReportResult(out_img_coarse, Coarse (non-SVM));
    
    //
    // Coarse SVM test (unrolled)
    //
    free(out_img_coarse_svm);
    out_img_coarse_svm = (real32*)malloc(
        sizeof(real32)*img_width*img_height);
    CoarseSVM_ApplyStencil(in_img, img_width, img_height, msk,
                           msk_width, msk_height, out_img_coarse_svm);
#if (CASE == CAT)
    writeBmpFloat(out_img_coarse_svm, "cat_coarse_svm_unrolled.bmp",
                  img_height,
                  img_width, inputImagePath);
#endif
    ReportResult(out_img_coarse_svm, Coarse (SVM));
    
    free(in_img);
    free(msk);
    free(out_img_seq);
    free(out_img_coarse);
    free(out_img_coarse_svm);
    
    return 0;
}
