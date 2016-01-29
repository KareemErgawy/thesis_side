#include <utils.cpp>

global_variable TestLoopTimer loop_timer;

#include <seq/conv_seq.cpp>
#include <coarse/conv_coarse.cpp>
#include <coarse/conv_coarse_svm.cpp>
#include <fine/conv_fine_svm.cpp>
#include <gpu/conv_gpu.cpp>
#include <gpu/conv_gpu_opt.cpp>

#define ReportTotalResult()                                         \
    std::cout << "\x1b[33;1mTotal elapsed time:\t\t"                \
    << loop_timer.total_time << "(ms)"  << std::endl                \
    << "Average:\t\t\t" << ((real32)loop_timer.total_time           \
                            /(real32)loop_timer.num_iterations)     \
    << "(ms)" << std::endl                                          \
    << "Median:\t\t\t\t"                                            \
    << GetMedian(&loop_timer)                                       \
    << "(ms)" << std::endl                                          \
    << ((loop_timer.num_successes < loop_timer.num_iterations) ?    \
        "\x1b[31;1m" : "\x1b[32;1m")                                \
    << "Success rate:\t\t\t"                                        \
    << loop_timer.num_successes << "/" << loop_timer.num_iterations \
    << " (" << ((real32)loop_timer.num_successes                    \
                / (real32)loop_timer.num_iterations * 100.0f)       \
    << "%)\x1b[0m" << std::endl;

#define ReportResult(img_name, test_name)               \
    if(CompareImages(out_img_seq, img_name, img_width,  \
                     img_height))                       \
    {                                                   \
        ++(loop_timer.num_successes);                   \
    }                                                   \
    else                                                \
    {                                                   \
    }

#define TestLoop(out_img_ptr, conv_call, out_file_name, test_name)  \
    std::cout << "\x1b[37;1m" << test_name                          \
    << " test loop started ..." << std::endl;                       \
    ResetLoopTimer(&loop_timer);                                    \
    real32* out_img_ptr = (real32*)malloc(sizeof(real32)*img_width  \
                                          *img_height);             \
    /*std::cout << std::endl;*/                                     \
    DrawProgressBar(0, loop_timer.num_iterations);                  \
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
        ReportResult(out_img_ptr, test_name);                       \
        DrawProgressBar(test+1, loop_timer.num_iterations);         \
    }                                                               \
    std::cout << std::endl;                                         \
    ReportTotalResult();                                            \
    std::cout << test_name << " test loop finished!"                \
    << std::endl << std::endl << std::endl;       

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

    cl_kernel kernel;
    status = SetupKernel("conv_kernel.cl", "conv_kernel", &kernel);
    CHECK_ERROR(status, "SetupKernel");

    cl_kernel naive_kernel;
    status = SetupKernel("naive_conv_kernel.cl", "naive_conv_kernel", &naive_kernel);
    CHECK_ERROR(status, "SetupKernel");

    cl_program gaussian_opt_prog;
    status = SetupProgram("gaussian.cl", &gaussian_opt_prog);
    CHECK_ERROR(status, "SetupProgram");
    
    cl_kernel gaussian_opt_kernels[9];
    std::string kernel_names[9] = {std::string("gaussian_tl"),
                                   std::string("gaussian_t"),
                                   std::string("gaussian_tr"),
                                   std::string("gaussian_ml"),
                                   std::string("gaussian_m"),
                                   std::string("gaussian_mr"),
                                   std::string("gaussian_bl"),
                                   std::string("gaussian_b"),
                                   std::string("gaussian_br")};
    
    for(int k_idx=0 ; k_idx<9 ; ++k_idx)
    {
        status = SetupKernel(gaussian_opt_prog, kernel_names[k_idx],
                    &gaussian_opt_kernels[k_idx]);
        CHECK_ERROR(status, "SetupKernel");
    }
    
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

    loop_timer.num_iterations = 7;
    ConvWrapper wrapper;
    
    //
    // Sequential implementation test
    //
    TestLoop(out_img_seq, Seq_ApplyStencil(&wrapper),
             "cat_seq.bmp", "Sequential");

    loop_timer.num_iterations = 7;
    
    //
    // Pure GPU test
    //
    TestLoop(out_img_gpu, GPU_ApplyStencil(&wrapper, naive_kernel),
             "cat_fine_gpu.bmp", "Pure GPU");

    //
    // Optimized GPU test
    //
    TestLoop(out_img_gpu_opt, GPU_Opt_ApplyStencil(&wrapper, gaussian_opt_kernels),
             "cat_fine_gpu_opt.bmp", "Optimized GPU");

    
    //
    // Coarse non-SVM test
    //
    TestLoop(out_img_coarse, Coarse_ApplyStencil(&wrapper, kernel),
             "cat_coarse.bmp", "Coarse non-SVM");
    
    //
    // Coarse SVM test
    //
    TestLoop(out_img_coarse_svm, CoarseSVM_ApplyStencil(&wrapper, kernel),
             "cat_coarse_svm.bmp", "Coarse SVM");

    //
    // Fine SVM test
    //
    TestLoop(out_img_fine_svm, FineSVM_ApplyStencil(&wrapper, kernel, true),
             "cat_fine_svm.bmp", "Fine SVM");

    free(in_img);
    free(msk);
    free(out_img_seq);
    free(out_img_coarse_svm);
    free(out_img_gpu);
    free(out_img_gpu_opt);
    
    return 0;
}
