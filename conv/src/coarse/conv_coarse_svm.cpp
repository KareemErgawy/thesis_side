#include <coarse/conv_coarse_svm.h>

// NOTE: A mixture of C and C++ CL API calls is used here because SVM
// functionality is not added to the wrapper yet

// TODO: Unify the API usage to C or C++
// TODO: Proper error handling and reporting
global_variable void* svmInput;

void CoarseSVM_ApplyStencil(real32* in_img, uint32 img_width,
                         uint32 img_height, real32* msk,
                         uint32 msk_width, uint32 msk_height,
                         real32* out_img)
{
    /*
    kernel_file_name = "test_svm_kernel.cl";
    kernel_name = "test_svm_kernel";
    SetupOpenCL();

    cl_device_svm_capabilities caps;
    cl_int err = clGetDeviceInfo(devices[0](),
                                 CL_DEVICE_SVM_CAPABILITIES,
                                 sizeof(cl_device_svm_capabilities),
                                 &caps, 0);

    if(err == CL_SUCCESS)
    {
        std::cout << "SVM capabilities found:" << std::endl;
        std::cout << "CL_DEVICE_SVM_COARSE_GRAIN_BUFFER: "
                  << ((caps & CL_DEVICE_SVM_COARSE_GRAIN_BUFFER) != 0)
                  << std::endl;

        std::cout << "CL_DEVICE_SVM_FINE_GRAIN_BUFFER: "
                  << ((caps & CL_DEVICE_SVM_FINE_GRAIN_BUFFER) != 0)
                  << std::endl;

        std::cout << "CL_DEVICE_SVM_FINE_GRAIN_SYSTEM: "
                  << ((caps & CL_DEVICE_SVM_FINE_GRAIN_SYSTEM) != 0)
                  << std::endl;
        
        std::cout << "CL_DEVICE_SVM_ATOMICS: "
                  << ((caps & CL_DEVICE_SVM_ATOMICS) != 0)
                  << std::endl;
    }
    else
    {
        std::cout << "SVM capabilities NOT found" << std::endl;
        return;
    }

    std::cout << "Context: " << context() << std::endl;
    
    svmInput = clSVMAlloc(context(), CL_MEM_READ_WRITE,
                                10*sizeof(int), 0);
    cl_int status;

    if(svmInput != NULL)
    {
        std::cout << "Allocated SVM memory" << std::endl;
    }
    else
    {
        std::cout << "Couldn't allocate SVM memory" << std::endl;
        return;
    }
    
    status = clEnqueueSVMMap(queue(), CL_TRUE,
                             CL_MAP_WRITE_INVALIDATE_REGION,
                             svmInput, 10*sizeof(int), 0,
                             NULL, NULL);

    if(status == CL_SUCCESS)
    {
        std::cout << "clEnqueueSVMMap SUCCESS" << std::endl;
    }
    else
    {
        std::cout << "clEnqueueSVMMap FAILED" << std::endl;
        return;
    }

    for(int i=0 ; i<10 ; i++)
    {
        ((int*)(svmInput))[i] = i;
    }
    
    status = clEnqueueSVMUnmap(queue(), svmInput, 0, NULL, NULL);

    if(status == CL_SUCCESS)
    {
        std::cout << "clEnqueueSVMUnmap SUCCESS" << std::endl;
    }
    else
    {
        std::cout << "clEnqueueSVMUnmap FAILED" << std::endl;
        return;
    }
    
    cl::Kernel kernel(program, kernel_name.c_str());
    status = clSetKernelArgSVMPointer(kernel(), 0, (void*)(svmInput));

    cl_context kc;
    kernel.getInfo(CL_KERNEL_CONTEXT, &kc);    
    std::cout << "Kernel context: " << kc << std::endl;
    
    cl_context qc;
    queue.getInfo(CL_QUEUE_CONTEXT, &qc);
    std::cout << "Queue context: " << qc << std::endl;
    
    if(status == CL_SUCCESS)
    {
        std::cout << "clSetKernelArgSVMPointer SUCCESS" << std::endl;
    }
    else
    {
        std::cout << "clSetKernelArgSVMPointer FAILED" << std::endl;
        return;
    }

    size_t globalThreads = 10;
    size_t localThreads = 1;
    cl_event ndrEvent;
    status = clEnqueueNDRangeKernel(queue(), kernel(), 1, NULL,
                                    &globalThreads, &localThreads,
                                    0, NULL, &ndrEvent);
    
    if(status == CL_SUCCESS)
    {
        std::cout << "clEnqueueNDRangeKernel SUCCESS" << std::endl;
    }
    else
    {
        std::cout << "clEnqueueNDRangeKernel FAILED" << std::endl;
        return;
    }

    for(int i=0 ; i<10 ; i++)
    {
        std::cout << "Test " << i << std::endl;
    }
/*
    status = clFlush(queue());

    if(status == CL_SUCCESS)
    {
        std::cout << "clFlush SUCCESS" << std::endl;
    }
    else
    {
        std::cout << "clFlush FAILED" << std::endl;
        return;
    }

    status = waitForEventAndRelease(&ndrEvent);

    if(status == CL_SUCCESS)
    {
        std::cout << "waitForEventAndRelease SUCCESS" << std::endl;
    }
    else
    {
        std::cout << "waitForEventAndRelease FAILED" << std::endl;
        return;
    }
*/  
    /*
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
        kernel_file_name = "conv_kernel.cl";
        kernel_name = "conv_kernel";
        SetupOpenCL();

        cl_int status;
                
        status = AllocateSVMObjects();
        //status = SVMHandleAllBoundries(in_img, msk, out_img);
        status = SVMHandleInnerRegions();
        //status = CopyOutputFromSVM(out_img);

        clSVMFree(context(), _in_img);
        clSVMFree(context(), _msk);
        clSVMFree(context(), _out_img);
        
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
    */
}

cl_int AllocateSVMObjects()
{
    /*
    _in_img = (real32*)clSVMAlloc(
        context(), CL_MEM_READ_WRITE, _img_size*sizeof(real32), 0);
    
    if(_in_img == NULL)
    {
        std::cerr << "Cannot allocate SVM memory for svm_in_img"
                  << std::endl;
        return 1;
    }
    else
    {
        std::cerr << "Allocated SVM memory for svm_in_img"
                  << std::endl;
    }
        
    _msk = (real32*)clSVMAlloc(
        context(), CL_MEM_READ_WRITE, _msk_size*sizeof(real32), 0);

    if(_msk == NULL)
    {
        std::cerr << "Cannot allocate SVM memory for svm_msk"
                  << std::endl;
        return 1;
    }
    else
    {
        std::cerr << "Allocated SVM memory for svm_msk"
                  << std::endl;
    }

    _out_img = (real32*)clSVMAlloc(
        context(), CL_MEM_READ_WRITE, _img_size*sizeof(real32), 0);

    if(_out_img == NULL)
    {
        std::cerr << "Cannot allocate SVM memory for svm_out_img"
                  << std::endl;
        return 1;
    }
    else
    {
        std::cerr << "Allocated SVM memory for svm_out_img"
                  << std::endl;
    }
    */
    return 0;
}

cl_int SVMHandleAllBoundries(real32* in_img, real32* msk,
                             real32* out_img)
{
    /*
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
    */
    return 0;
}

cl_int SVMHandleInnerRegions()
{
    /*
    cl_int status;
    
    cl::Kernel kernel(program, kernel_name.c_str());
    status = clSetKernelArgSVMPointer(kernel(), 0, (void*)_in_img);
    CHECK_OPENCL_ERROR(status, "clSetKernelArgSVMPointer");

    status = kernel.setArg(1, _img_width);
    CHECK_OPENCL_ERROR(status, "kernel.setArg");

    status = kernel.setArg(2, _img_height);
    CHECK_OPENCL_ERROR(status, "kernel.setArg");
        
    status = clSetKernelArgSVMPointer(kernel(), 3, (void*)_msk);
    CHECK_OPENCL_ERROR(status, "clSetKernelArgSVMPointer");

    status = kernel.setArg(4, _msk_width);
    CHECK_OPENCL_ERROR(status, "kernel.setArg");
    
    status = kernel.setArg(5, _msk_height);
    CHECK_OPENCL_ERROR(status, "kernel.setArg");
    
    status = clSetKernelArgSVMPointer(kernel(), 6, (void*)_out_img);
    CHECK_OPENCL_ERROR(status, "clSetKernelArgSVMPointer");
        
    // TODO play with local range to understand its effect
    cl::NDRange global(_inner_width, _inner_height);

    cl::Event event;
    status = queue.enqueueNDRangeKernel(kernel, cl::NullRange,
                                        global, cl::NullRange,
                                        NULL, &event);

    std::cout << "Kernel result: " << status << std::endl;

    cl_int exec_state =
        event.getInfo<CL_EVENT_COMMAND_EXECUTION_STATUS>();
    std::cout << "Exec state: " << exec_state << std::endl;
    status = clWaitForEvents(1, &event());
    std::cout << status << std::endl;
    exec_state =
        event.getInfo<CL_EVENT_COMMAND_EXECUTION_STATUS>();
    std::cout << "Exec state2: " << exec_state << std::endl;

    status = clReleaseEvent(event());    
    status = clFlush(queue());
    */
}

cl_int CopyOutputFromSVM(real32* out_img)
{
    /*
    cl_int status;
    status = clEnqueueSVMMap(queue(), CL_TRUE, CL_MAP_WRITE,
                             _out_img, _img_size*sizeof(real32),
                             0, NULL, NULL);
    std::memcpy(_out_img, out_img, _img_size*sizeof(real32));
    status = clEnqueueSVMUnmap(queue(), _out_img, 0, NULL, NULL);

    return status;
    */
    return 0;
}
