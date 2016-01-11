#include <utils.h>

void Print2DArray(std::string message, real32* array, uint32 width,
                  uint32 height)
{
    uint32 c, r;
    std::cout << "********************************" << std::endl
              << message << std::endl;
    
    for(r=0 ; r<height ; r++)
    {
        for(c=0 ; c<width ; c++)
        {
            std::cout << std::setprecision(4)  << std::setw(4)
                      << array[(r*width) + c] << " ";
        }

        std::cout << std::endl;
    }    

    std::cout << "********************************" << std::endl;

}

void Clear2DArray(real32* array, uint32 width, uint32 height,
                  real32 value)
{
    uint32 c, r;
    
    for(r=0 ; r<height ; r++)
    {
        for(c=0 ; c<width ; c++)
        {
            array[(r*width) + c] = value;
        }
    }    
}

void GenerateTestImage(real32* img, uint32 img_width,
                     uint32 img_height)
{
    uint32 c, r;
    
    for(c=0 ; c<img_width ; c++)
    {
        for(r=0 ; r<img_height ; r++)
        {
            if((r == (img_height / 2)) && (c == (img_width / 2)))
            {
                img[(r*img_width) + c] = 10.f;
            }
            else
            {
                img[(r*img_width) + c] = 1.f;
            }
        }
    }
}

void GenerateTestMask(real32* msk, uint32 msk_width,
                      uint32 msk_height)
{
    uint32 c, r;
    real32 total = 0;
    
    for(c=0 ; c<msk_width ; c++)
    {
        for(r=0 ; r<msk_height ; r++)
        {
            msk[(r*msk_width) + c] = 1.f/(msk_width*msk_height);
            total += msk[(r*msk_width) + c];
        }
    }
}

void GenerateGaussianBlurFilter_5X5(real32* msk)
{
    msk[0] =  1.0f/273.0f;
    msk[1] =  4.0f/273.0f;
    msk[2] =  7.0f/273.0f;
    msk[3] =  4.0f/273.0f;
    msk[4] =  1.0f/273.0f;

    msk[5] =  4.0f/273.0f;
    msk[6] = 16.0f/273.0f;
    msk[7] = 26.0f/273.0f;
    msk[8] = 16.0f/273.0f;
    msk[9] =  4.0f/273.0f;

    msk[10] =  7.0f/273.0f;
    msk[11] = 26.0f/273.0f;
    msk[12] = 41.0f/273.0f;
    msk[13] = 26.0f/273.0f;
    msk[14] =  7.0f/273.0f;

    msk[15] =  4.0f/273.0f;
    msk[16] = 16.0f/273.0f;
    msk[17] = 26.0f/273.0f;
    msk[18] = 16.0f/273.0f;
    msk[19] =  4.0f/273.0f;

    msk[20] =  1.0f/273.0f;
    msk[21] =  4.0f/273.0f;
    msk[22] =  7.0f/273.0f;
    msk[23] =  4.0f/273.0f;
    msk[24] =  1.0f/273.0;
}

bool CompareImages(real32* img1, real32* img2, uint32 width,
                   uint32 height)
{
    uint32 c, r;
     
    for(r=0 ; r<height ; r++)
    {
        for(c=0 ; c<width ; c++)
        {
            if(img1[(r*width)+c] != img2[(r*width)+c])
            {
                return false;
            }
        }
    }

    return true;
}

// TODO: get the program init out of here and setup so that you have
// the most capable device
int SetupOpenCL()
{
    cl_int status;
    status = clGetPlatformIDs(1, &platform, NULL);
    CHECK_OPENCL_ERROR(status, "clGetPlatformIDs");

    cl_context_properties cps[3] =
        {
            CL_CONTEXT_PLATFORM,
            (cl_context_properties)platform,
            0
        };

    context = clCreateContextFromType(cps, CL_DEVICE_TYPE_GPU, NULL,
                                      NULL, &status);
    CHECK_OPENCL_ERROR(status, "clCreateContextFromType");
    
    size_t devicesSize = 0;
    status = clGetContextInfo(context, CL_CONTEXT_DEVICES, 0, NULL,
                              &devicesSize);
    CHECK_OPENCL_ERROR(status, "clGetContextInfo");

    int deviceCount = (int)(devicesSize / sizeof(cl_device_id));

    devices = (cl_device_id*)malloc(devicesSize);
    CHECK_ALLOCATION(devices, "devices");

    status = clGetContextInfo(context, CL_CONTEXT_DEVICES,
                              devicesSize, devices, NULL);
    CHECK_OPENCL_ERROR(status, "clGetContextInfo");

    device = devices[0];

    DisplayDeviceSVMCaps(device);

    cl_queue_properties prop[] = {0};
    queue = clCreateCommandQueueWithProperties(context, device, prop,
                                               &status);
    CHECK_OPENCL_ERROR(status, "clCreateCommandQueueWithProperties");
    
    return SUCCESS;
}

int SetupKernel(std::string kernel_file_name, std::string kernel_name,
                cl_kernel* kernel_ptr)
{
    cl_int status;
    std::ifstream source_file(kernel_file_name.c_str());
    std::string source_code(std::istreambuf_iterator<char>(
                               source_file),
                           (std::istreambuf_iterator<char>()));

    const char* source = source_code.c_str();
    size_t source_size[] = {strlen(source)};
    
    program = clCreateProgramWithSource(context, 1, &source,
                                        source_size, &status);
    CHECK_OPENCL_ERROR(status, "clCreateProgramWithSource");

    std::string flags_str = "-I ./ -cl-std=CL2.0";

    status = clBuildProgram(program, 1, &device, flags_str.c_str(),
                            NULL, NULL);
    CHECK_OPENCL_ERROR(status, "clBuildProgram");

    *kernel_ptr = clCreateKernel(program, kernel_name.c_str(), &status);
    CHECK_OPENCL_ERROR(status, "clCreateKernel");
    
    return SUCCESS;
}

int SetupKernel(std::string kernel_name, cl_kernel* kernel_ptr)
{
    cl_int status;
    *kernel_ptr = clCreateKernel(program, kernel_name.c_str(), &status);
    CHECK_OPENCL_ERROR(status, "clCreateKernel");
    
    return SUCCESS;
}

int DisplayDeviceSVMCaps(cl_device_id device)
{
    cl_int status;
    cl_device_svm_capabilities caps;
    status = clGetDeviceInfo(device, CL_DEVICE_SVM_CAPABILITIES,
                             sizeof(cl_device_svm_capabilities),
                             &caps, 0);

    if(status != CL_SUCCESS)
    {
        std::cout << std::endl << "Device doesn't support SVM" << std::endl;
        return GENERAL_FAILURE;
    }

    std::cout << std::endl << "SVM capabilities:" << std::endl;

    std::cout << "\tCL_DEVICE_SVM_COARSE_GRAIN_BUFFER: "
              << ((caps & CL_DEVICE_SVM_COARSE_GRAIN_BUFFER) != 0)
              << std::endl;

    std::cout << "\tCL_DEVICE_SVM_FINE_GRAIN_BUFFER:   "
              << ((caps & CL_DEVICE_SVM_FINE_GRAIN_BUFFER) != 0)
              << std::endl;

    std::cout << "\tCL_DEVICE_SVM_FINE_GRAIN_SYSTEM:   "
              << ((caps & CL_DEVICE_SVM_FINE_GRAIN_SYSTEM) != 0)
              << std::endl;
        
    std::cout << "\tCL_DEVICE_SVM_ATOMICS:             "
              << ((caps & CL_DEVICE_SVM_ATOMICS) != 0)
              << std::endl << std::endl;

    return SUCCESS;
}

int PrintCompilerError(cl_program program, cl_device_id device)
{
    cl_int status;
    size_t log_size;
    char* log;

    status = clGetProgramBuildInfo(program, device,
                                   CL_PROGRAM_BUILD_LOG, 0, NULL,
                                   &log_size);
    CHECK_OPENCL_ERROR(status, "clGetProgramBuildInfo");

    log = (char*)malloc(log_size);
    CHECK_ALLOCATION(log, "log");

    status = clGetProgramBuildInfo(program, device,
                                   CL_PROGRAM_BUILD_LOG,
                                   log_size, log, NULL);
    CHECK_OPENCL_ERROR(status, "clGetProgramBuildInfo");

    std::cout << log << std::endl;
}
