#include <coarse/conv_coarse.h>

void Coarse_ApplyStencil(real32* in_img, uint32 img_width,
                         uint32 img_height, real32* msk,
                         uint32 msk_width, uint32 msk_height,
                         real32* out_img)
{
    /*
    std::cout << "Coarse (non-SVM) Convolution START!" << std::endl;
    //Print2DArray("Input Image: ", in_img, img_width, img_height);
    _in_img = in_img;
    _img_width = img_width;
    _img_height = img_height;
    _msk = msk;
    _msk_width = msk_width;
    _msk_height = msk_height;
    _out_img = out_img;
    _half_w = msk_width / 2;
    _half_h = msk_height / 2;

    uint32 img_size = _img_width * _img_height;
    uint32 inner_width = (_img_width - (_half_w*2));
    uint32 inner_height = (_img_height - (_half_h*2));
    uint32 inner_size = inner_width * inner_height;
    uint32 msk_size = _msk_width * _msk_height;

    try
    {
        kernel_file_name = "conv_kernel.cl";
        kernel_name = "conv_kernel";
        SetupOpenCL();

        cl_int status;
        
        cl::Buffer in_img_buf = cl::Buffer(context, CL_MEM_READ_ONLY,
                                           img_size*sizeof(real32));
        cl::Buffer msk_buf = cl::Buffer(context, CL_MEM_READ_ONLY,
                                        msk_size*sizeof(real32));
        cl::Buffer out_img_buf = cl::Buffer(context,
                                            CL_MEM_WRITE_ONLY,
                                            img_size*sizeof(real32));

        queue.enqueueWriteBuffer(in_img_buf, CL_TRUE, 0,
                                 img_size*sizeof(real32), in_img);
        queue.enqueueWriteBuffer(msk_buf, CL_TRUE, 0,
                                 msk_size*sizeof(real32), msk);

        cl::Kernel kernel(program, kernel_name.c_str());
        kernel.setArg(0, in_img_buf);
        kernel.setArg(1, img_width);
        kernel.setArg(2, img_height);
        kernel.setArg(3, msk_buf);
        kernel.setArg(4, msk_width);
        kernel.setArg(5, msk_height);
        kernel.setArg(6, out_img_buf);

        // TODO play with local range to understand its effect
        
        // TODO use offset fields instead of calculating that in the
        // kernel
        cl::NDRange global(inner_width, inner_height);

        cl::Event event;
        queue.enqueueNDRangeKernel(kernel, cl::NullRange,
                                   global, cl::NullRange,
                                   NULL, &event);
        
        queue.enqueueReadBuffer(out_img_buf, CL_TRUE, 0,
                                img_size*sizeof(real32), out_img);
                               
    }
    catch(cl::Error error)
    {
        std::cout << error.what() << "(" << error.err() << ")"
                  << std::endl;
    }

    // TODO: try to use clEnqueueNativeKernel here
    HandleAllBoundries();

    //Print2DArray("Output Image: ", out_img, img_width, img_height);
    std::cout << "Coarse (non-SVM) Convolution FINISH!" << std::endl;
    std::cout << "======================" << std::endl;
    */
}
