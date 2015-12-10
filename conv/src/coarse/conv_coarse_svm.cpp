#include <coarse/conv_coarse_svm.h>

// NOTE: A mixture of C and C++ CL API calls is used here because SVM
// functionality is not added to the wrapper yet

// TODO: Unify the API usage to C or C++
// TODO: Proper error handling and reporting

void CoarseSVM_ApplyStencil(real32* in_img, uint32 img_width,
                         uint32 img_height, real32* msk,
                         uint32 msk_width, uint32 msk_height,
                         real32* out_img)
{
    std::cout << "Coarse (SVM) Convolution START!" << std::endl;

    _img_width = img_width;
    _img_height = img_height;
    _msk_width = msk_width;
    _msk_height = msk_height;
    _half_w = msk_width / 2;
    _half_h = msk_height / 2;

    _img_size = img_width * img_height;
    _inner_width = (img_width - (_half_w*2));
    _inner_height = (img_height - (_half_h*2));
    _inner_size = _inner_width * _inner_height;
    _msk_size = msk_width * msk_height;
    
    try
    {
        cl_int status;
        SetupOpenCL();

        status = AllocateSVMObjects();
        status = SVMHandleAllBoundries(in_img, msk, out_img);
        status = SVMHandleInnerRegions();
        //status = CopyOutputFromSVM(out_img);
        
        Print2DArray("Output Image: ", out_img, img_width,
                     img_height);
    }
    catch(cl::Error error)
    {
        std::cout << error.what() << "(" << error.err() << ")"
                  << std::endl;
    }
    
    std::cout << "Coarse (SVM) Convolution FINISH!" << std::endl;
    std::cout << "======================" << std::endl;
}

cl_int AllocateSVMObjects()
{
    _in_img = (real32*)clSVMAlloc(
        context(), CL_MEM_READ_WRITE, _img_size*sizeof(real32), 0);
    
    if(_in_img == NULL)
    {
        std::cerr << "Cannot allocate SVM memory for svm_in_img"
                  << std::endl;
        return 1;
    }
        
    _msk = (real32*)clSVMAlloc(
        context(), CL_MEM_READ_WRITE, _msk_size*sizeof(real32), 0);

    if(_msk == NULL)
    {
        std::cerr << "Cannot allocate SVM memory for svm_msk"
                  << std::endl;
        return 1;
    }

    _out_img = (real32*)clSVMAlloc(
        context(), CL_MEM_READ_WRITE, _img_size*sizeof(real32), 0);

    if(_out_img == NULL)
    {
        std::cerr << "Cannot allocate SVM memory for svm_out_img"
                  << std::endl;
        return 1;
    }

    return 0;
}

cl_int SVMHandleAllBoundries(real32* in_img, real32* msk,
                             real32* out_img)
{
    cl_int status;
    
    // Map SVM objects into the host address space to copy input
    // data and handle the boundaries
    status = clEnqueueSVMMap(queue(), CL_TRUE, CL_MAP_READ,
                             _in_img, _img_size*sizeof(real32),
                             0, NULL, NULL);
    // TODO: this will be replaced by initialization after making each
    // implementation responsilbe for its memory allocations
    std::memcpy(_in_img, in_img, _img_size*sizeof(real32));

    status = clEnqueueSVMMap(queue(), CL_TRUE, CL_MAP_READ,
                             _msk, _msk_size*sizeof(real32),
                             0, NULL, NULL);
    std::memcpy(_msk, msk, _msk_size*sizeof(real32));

    status = clEnqueueSVMMap(queue(), CL_TRUE,
                             CL_MAP_WRITE_INVALIDATE_REGION,
                             _out_img, _img_size*sizeof(real32),
                             0, NULL, NULL);

    HandleAllBoundries();
        
    status = clEnqueueSVMUnmap(queue(), _in_img, 0, NULL, NULL);
    status = clEnqueueSVMUnmap(queue(), _msk, 0, NULL, NULL);
    status = clEnqueueSVMUnmap(queue(), _out_img, 0, NULL, NULL);

    return status;
}

cl_int SVMHandleInnerRegions()
{
    cl_int status;
    kernel_file_name = "conv_kernel.cl";
    kernel_name = "conv_kernel";
    
    cl::Kernel kernel(program, kernel_name.c_str());
/*    status = clSetKernelArgSVMPointer(kernel(), 0, (void*)_in_img);
    kernel.setArg(1, _img_width);
    kernel.setArg(2, _img_height);
    status = clSetKernelArgSVMPointer(kernel(), 3, (void*)_msk);
    kernel.setArg(4, _msk_width);
    kernel.setArg(5, _msk_height);
    status = clSetKernelArgSVMPointer(kernel(), 6, (void*)_out_img);
*/    
    // TODO play with local range to understand its effect
    cl::NDRange global(_inner_width, _inner_height);

    cl::Event event;
    status = queue.enqueueNDRangeKernel(kernel, cl::NullRange,
                                        global, cl::NullRange,
                                        NULL, &event);
    status = clFlush(queue());
    status = clWaitForEvents(1, &event());
    status = clReleaseEvent(event());
}

cl_int CopyOutputFromSVM(real32* out_img)
{
    cl_int status;
    status = clEnqueueSVMMap(queue(), CL_TRUE, CL_MAP_WRITE,
                             _out_img, _img_size*sizeof(real32),
                             0, NULL, NULL);
    std::memcpy(_out_img, out_img, _img_size*sizeof(real32));
    status = clEnqueueSVMUnmap(queue(), _out_img, 0, NULL, NULL);

    return status;
}
