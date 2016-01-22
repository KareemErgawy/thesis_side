#include <utils.cpp>

global_variable TestLoopTimer loop_timer;

#include <seq/conv_seq.cpp>
#include <coarse/conv_coarse.cpp>
#include <coarse/conv_coarse_svm.cpp>
#include <fine/conv_fine_svm.cpp>

#define ReportTotalResult()                                         \
    std::cout << "\x1b[33;1mTotal elapsed time:\t\t"                \
    << loop_timer.total_time << "(ms)"  << std::endl                \
    << "Average:\t\t\t" << ((real32)loop_timer.total_time           \
                            /(real32)loop_timer.num_iterations)     \
    << "(ms)" << std::endl <<"\x1b[32;1mSuccess rate:\t\t\t"        \
    << loop_timer.num_successes << "/" << loop_timer.num_iterations \
    << " (" << ((real32)loop_timer.num_successes                    \
                / (real32)loop_timer.num_iterations * 100.0f)       \
    << "%)\x1b[0m" << std::endl << std::endl << std::endl;                         

#define ReportResult(img_name, test_name)                               \
    if(CompareImages(out_img_seq, img_name, img_width,                  \
                     img_height))                                       \
    {                                                                   \
        ++(loop_timer.num_successes);                                   \
    }                                                                   \
    else                                                                \
    {                                                                   \
    }

#define TestLoop(out_img_ptr, conv_call, out_file_name, test_name)  \
    std::cout << test_name << " loop started ..." << std::endl;     \
    ResetLoopTimer(&loop_timer);                                    \
    real32* out_img_ptr = (real32*)malloc(sizeof(real32)*img_width  \
                                          *img_height);             \
    for(uint32 test=0 ; test<loop_timer.num_iterations ; ++test)    \
    {                                                               \
        memset(out_img_ptr, 0, sizeof(real32)*img_width             \
               *img_height);                                        \
        wrapper = {                                                 \
            in_img, (uint32)img_width, (uint32)img_height,          \
            msk, msk_width, msk_height,                             \
            out_img_ptr                                             \
        };                                                          \
        conv_call;                                                  \
        /*#if (CASE == CAT)*/                                       \
        /*writeBmpFloat(out_img_ptr, out_file_name, img_height,*/   \
        /*img_width, inputImagePath);*/                             \
        /*#endif*/                                                  \
        ReportResult(out_img_ptr, test_name);                       \
    }                                                               \
    std::cout << test_name << " loop finished!" << std::endl;       \
    ReportTotalResult();

#define SIMPLE 0
#define CAT    1
#define RAND   2

#define CASE   RAND

global_variable const char* inputImagePath = "../Images/cat.bmp";

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
    ConvWrapper wrapper = {
        in_img, (uint32)img_width, (uint32)img_height,
        msk, msk_width, msk_height,
        out_img_seq
    };
    Seq_ApplyStencil(&wrapper);
    
#if (CASE == CAT)
    writeBmpFloat(out_img_seq, "cat_seq.bmp", img_height,
                  img_width, inputImagePath);
#endif
    std::cout  << std::endl;

    loop_timer.num_iterations = 10;

    //
    // Coarse non-SVM test
    //
    TestLoop(out_img_coarse, Coarse_ApplyStencil(&wrapper, false),
             "cat_coarse.bmp", "Coarse non-SVM");
    
    //
    // Coarse SVM test
    //
    TestLoop(out_img_coarse_svm, CoarseSVM_ApplyStencil(&wrapper, false),
             "cat_coarse_svm.bmp", "Coarse SVM");

    //
    // Fine SVM test
    //
    TestLoop(out_img_fine_svm, FineSVM_ApplyStencil(&wrapper, false, true),
             "cat_fine_svm.bmp", "Fine SVM");

    //TestLoop(out_img_fine_svm2, FineSVM_ApplyStencil(&wrapper, false, false),
    //         "cat_fine_svm2.bmp", "Fine SVM2");

#if 0
    //
    // Coarse non-SVM test (unrolled)
    //
    free(out_img_coarse);    
    out_img_coarse = (real32*)malloc(sizeof(real32)*img_width
                                             *img_height);
    wrapper = {
        in_img, (uint32)img_width, (uint32)img_height,
        msk, msk_width, msk_height,
        out_img_coarse
    };
    Coarse_ApplyStencil(&wrapper);
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
    wrapper = {
        in_img, (uint32)img_width, (uint32)img_height,
        msk, msk_width, msk_height,
        out_img_coarse_svm
    };
    CoarseSVM_ApplyStencil(&wrapper);
#if (CASE == CAT)
    writeBmpFloat(out_img_coarse_svm, "cat_coarse_svm_unrolled.bmp",
                  img_height,
                  img_width, inputImagePath);
#endif
    ReportResult(out_img_coarse_svm, Coarse (SVM));

    //
    // Fine SVM test (unrolled)
    //
    free(out_img_fine_svm);
    out_img_fine_svm = (real32*)malloc(
        sizeof(real32)*img_width*img_height);
    wrapper = {
        in_img, (uint32)img_width, (uint32)img_height,
        msk, msk_width, msk_height,
        out_img_fine_svm
    };
    FineSVM_ApplyStencil(&wrapper);
#if (CASE == CAT)
    writeBmpFloat(out_img_fine_svm, "cat_fine_svm_unrolled.bmp",
                  img_height,
                  img_width, inputImagePath);
#endif
    ReportResult(out_img_fine_svm, Fine (SVM));
#endif
    free(in_img);
    free(msk);
    free(out_img_seq);
    free(out_img_coarse_svm);
    
    return 0;
}
