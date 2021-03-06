#include <utils.h>
#include <assert.h>
#include <time.h>
#include <stdlib.h>

#define KiloBytes(bytes) (bytes) / 1024
#define MegaBytes(bytes) KiloBytes(bytes) / 1024
#define GigaBytes(bytes) MegaBytes(bytes) / 1024

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

void GenerateRandomImage(real32* img, uint32 img_width,
                     uint32 img_height)
{
    uint32 c, r;
    srand ((unsigned int)time(NULL));
    
    for(c=0 ; c<img_width ; c++)
    {
        for(r=0 ; r<img_height ; r++)
        {
            img[(r*img_width) + c] = (real32)(rand() % 255);
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
    msk[0] = 0.005008f;
    msk[1] = 0.017300f;
    msk[2] = 0.026151f;
    msk[3] = 0.017300f;
    msk[4] = 0.005008f;

    msk[5] = 0.017300f;
    msk[6] = 0.059761f;
    msk[7] = 0.090339f;
    msk[8] = 0.059761f;
    msk[9] = 0.017300f;
    
    msk[10] = 0.026151f;
    msk[11] = 0.090339f;
    msk[12] = 0.136565f;
    msk[13] = 0.090339f;
    msk[14] = 0.026151f;
    
    msk[15] = 0.017300f;
    msk[16] = 0.059761f;
    msk[17] = 0.090339f;
    msk[18] = 0.059761f;
    msk[19] = 0.017300f;

    msk[20] = 0.005008f;
    msk[21] = 0.017300f;
    msk[22] = 0.026151f;
    msk[23] = 0.017300f;
    msk[24] = 0.005008f;
}

bool CompareImages(real32* img1, real32* img2, uint32 width,
                   uint32 height)
{
    uint32 c, r;
     
    for(r=0 ; r<height ; r++)
    {
        for(c=0 ; c<width ; c++)
        {
            if((img1[(r*width)+c] - img2[(r*width)+c]) > 0.0001f)
            {
                return false;
            }
        }
    }

    return true;
}

void GenerateTestArray(uint32* array, uint32 len)
{        
    for(uint32 i=0 ; i<len ; i++)
    {
        array[i] = rand() % 1000;
    }
}

bool CompareArrays(uint32* a1, uint32* a2, uint32 len)
{     
    for(uint32 i=0 ; i<len ; i++)
    {
        if(a1[i] != a2[i])
        {
            return false;
        }
    }

    return true;
}

bool TestIfArrayIsSorted(uint32* array, uint32 len)
{
    for(uint32 i=1 ; i<len ; i++)
    {
        if(array[i] < array[i-1])
        {
            return false;
        }
    }

    return true;
}

struct SetupOptions
{
    char* required_platform_subname;
};

int SetupOpenCL(SetupOptions* setup_options=NULL)
{
    cl_int status;
    cl_uint num_platforms = 0;

    status = clGetPlatformIDs(0, 0, &num_platforms);
    CHECK_OPENCL_ERROR(status, "clGetPlatformIDs");

    cl_platform_id* platforms = (cl_platform_id*)malloc(num_platforms*sizeof(cl_platform_id));
    CHECK_ALLOCATION(platforms, "devices");
    
    status = clGetPlatformIDs(num_platforms, platforms, NULL);
    CHECK_OPENCL_ERROR(status, "clGetPlatformIDs");

    if(setup_options == NULL)
    {
        platform = platforms[0];
    }
    else
    {
        for(cl_uint i = 0; i < num_platforms; ++i)
        {
            size_t platform_name_length = 0;
            status = clGetPlatformInfo(
                platforms[i],
                CL_PLATFORM_NAME,
                0,
                0,
                &platform_name_length);
            CHECK_OPENCL_ERROR(status, "clGetPlatformInfo");

            char* platform_name = new char[platform_name_length];
            status = clGetPlatformInfo(
                platforms[i],
                CL_PLATFORM_NAME,
                platform_name_length,
                platform_name,
                0);
            CHECK_OPENCL_ERROR(status, "clGetPlatformInfo");            

            if(strstr(platform_name, setup_options->required_platform_subname))
            {
                platform = platforms[i];
            }

            delete [] platform_name;
        }
    }

    free(platforms);
    
    cl_context_properties cps[3] =
        {
            CL_CONTEXT_PLATFORM,
            (cl_context_properties)platform,
            0
        };

    context = clCreateContextFromType(cps, CL_DEVICE_TYPE_GPU | CL_DEVICE_TYPE_CPU, NULL,
                                      NULL, &status);
    CHECK_OPENCL_ERROR(status, "clCreateContextFromType");
    
    size_t devicesSize = 0;
    status = clGetContextInfo(context, CL_CONTEXT_DEVICES, 0, NULL,
                              &devicesSize);
    CHECK_OPENCL_ERROR(status, "clGetContextInfo");

    size_t deviceCount = (devicesSize / sizeof(cl_device_id));

    devices = (cl_device_id*)malloc(devicesSize);
    CHECK_ALLOCATION(devices, "devices");

    status = clGetContextInfo(context, CL_CONTEXT_DEVICES,
                              devicesSize, devices, NULL);
    CHECK_OPENCL_ERROR(status, "clGetContextInfo");

    for(size_t i=0 ; i<deviceCount ; i++)
    {
        char device_name[50];
        status = clGetDeviceInfo(devices[i], CL_DEVICE_NAME, sizeof(device_name),
                                 device_name, 0);
        CHECK_OPENCL_ERROR(status, "clGetDeviceInfo");
        std::cout << device_name << std::endl;

        cl_device_type device_type;
        status = clGetDeviceInfo(devices[i], CL_DEVICE_TYPE, sizeof(device_type),
                                 &device_type, 0);
        CHECK_OPENCL_ERROR(status, "clGetDeviceInfo");

        if(device_type == CL_DEVICE_TYPE_CPU)
        {
            std::cout << "CPU Device";
            cpu_device = devices[i];
            cl_queue_properties prop[] = {0};
            cpu_queue = clCreateCommandQueueWithProperties(context, devices[i], prop,
                                                       &status);
            CHECK_OPENCL_ERROR(status, "clCreateCommandQueueWithProperties");
        }
        else if(device_type == CL_DEVICE_TYPE_GPU)
        {
            std::cout << "GPU Device";
            gpu_device = devices[i];
            cl_queue_properties prop[] = {0};
            gpu_queue = clCreateCommandQueueWithProperties(context, devices[i], prop,
                                                       &status);
            CHECK_OPENCL_ERROR(status, "clCreateCommandQueueWithProperties");
        }
        else
        {
            std::cout << "\x1b[31;1mUnexpected device: " << device_type
                      << ", why is this here?!\x1b[0m";
        }

        std::cout << std::endl;
        
        DisplayDeviceSVMCaps(devices[i]);
        DisplayDeviceMemoryCaps(devices[i]);
        DisplayDeviceWorkRangeInfo(devices[i]);

        std::cout << "==============================" << std::endl << std::endl;
    }
    
    return SUCCESS;
}

int SetupProgram(std::string program_file_name, cl_program* program_ptr)
{
    return SetupProgram(true, program_file_name, program_ptr);
}
    
int SetupProgram(bool gpu, std::string program_file_name,
                 cl_program* program_ptr)
{
    cl_device_id device = gpu ? gpu_device : cpu_device;
    cl_int status;
    std::ifstream source_file(std::string("..\\kernels\\") + program_file_name.c_str());

    if (!source_file)
    {
        return 1;
    }

    std::string source_code(std::istreambuf_iterator<char>(
                                source_file),
                            (std::istreambuf_iterator<char>()));

    const char* source = source_code.c_str();
    size_t source_size[] = {strlen(source)};
    
    *program_ptr = clCreateProgramWithSource(context, 1, &source,
                                        source_size, &status);
    CHECK_OPENCL_ERROR(status, "clCreateProgramWithSource");

    std::string flags_str = "-I ./ -cl-std=CL2.0";

    status = clBuildProgram(*program_ptr, 1, &device, flags_str.c_str(),
                            NULL, NULL);
    CHECK_OPENCL_ERROR(status, "clBuildProgram");

    return SUCCESS;
}

int SetupKernel(std::string kernel_file_name, std::string kernel_name,
                cl_kernel* kernel_ptr)
{
    return SetupKernel(true, kernel_file_name, kernel_name, kernel_ptr);
}

int SetupKernel(bool gpu, std::string kernel_file_name, std::string kernel_name,
                cl_kernel* kernel_ptr)
{
    cl_device_id device = gpu ? gpu_device : cpu_device;
    cl_int status;
    std::ifstream source_file(std::string("..\\kernels\\") + kernel_file_name.c_str());

    if (!source_file)
    {
        return 1;
    }

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

int SetupKernel(cl_program program, std::string kernel_name, cl_kernel* kernel_ptr)
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

    std::cout << "SVM capabilities:" << std::endl;

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
              << std::endl;

    return SUCCESS;
}

int DisplayDeviceMemoryCaps(cl_device_id device)
{
    cl_int status;

    std::cout << "Memory properties:" << std::endl;

    cl_ulong global_mem_size;
    status = clGetDeviceInfo(device, CL_DEVICE_GLOBAL_MEM_SIZE, sizeof(cl_ulong),
                             &global_mem_size, 0);
    CHECK_OPENCL_ERROR(status, "clGetDeviceInfo(CL_DEVICE_GLOBAL_MEM_SIZE)");
    std::cout << "\tCL_DEVICE_GLOBAL_MEM_SIZE: " << MegaBytes(global_mem_size)
              << " MBytes" << std::endl;
    
    cl_ulong global_cache_size;
    status = clGetDeviceInfo(device, CL_DEVICE_GLOBAL_MEM_CACHE_SIZE, sizeof(cl_ulong),
                             &global_cache_size, 0);
    CHECK_OPENCL_ERROR(status, "clGetDeviceInfo(CL_DEVICE_GLOBAL_MEM_CACHE_SIZE)");
    std::cout << "\tCL_DEVICE_GLOBAL_MEM_CACHE_SIZE: " << KiloBytes(global_cache_size)
              << " KBytes" << std::endl;

    cl_uint global_cacheline_size;
    status = clGetDeviceInfo(device, CL_DEVICE_GLOBAL_MEM_CACHELINE_SIZE, sizeof(cl_uint),
                             &global_cacheline_size, 0);
    CHECK_OPENCL_ERROR(status, "clGetDeviceInfo(CL_DEVICE_GLOBAL_MEM_CACHELINE_SIZE)");
    std::cout << "\tCL_DEVICE_GLOBAL_MEM_CACHELINE_SIZE: " << global_cacheline_size
              << std::endl;

    cl_device_mem_cache_type mem_cache_type;
    status = clGetDeviceInfo(device, CL_DEVICE_GLOBAL_MEM_CACHE_TYPE,
                             sizeof(cl_device_mem_cache_type),
                             &mem_cache_type, 0);
    CHECK_OPENCL_ERROR(status, "clGetDeviceInfo(CL_DEVICE_GLOBAL_MEM_CACHE_TYPE)");
    std::cout << "\tCL_DEVICE_GLOBAL_MEM_CACHE_TYPE: ";
    if(mem_cache_type && CL_NONE)
    {
        std::cout << "CL_NONE | ";
    }
    else if(mem_cache_type && CL_READ_ONLY_CACHE)
    {
        std::cout << "CL_READ_ONLY_CACHE | ";
    }
    if(mem_cache_type && CL_READ_WRITE_CACHE)
    {
        std::cout << "CL_READ_WRITE_CACHE" << std::endl;
    }
    
    return SUCCESS;
}

int DisplayDeviceWorkRangeInfo(cl_device_id device)
{
    cl_int status;

    std::cout << "Work dim properties:" << std::endl;

    cl_uint num_compute_units;
    status = clGetDeviceInfo(device, CL_DEVICE_MAX_COMPUTE_UNITS, sizeof(cl_uint),
                             &num_compute_units, 0);
    CHECK_OPENCL_ERROR(status, "clGetDeviceInfo(CL_DEVICE_MAX_COMPUTE_UNITS)");
    std::cout << "\tCL_DEVICE_MAX_COMPUTE_UNITS: " << num_compute_units
              << std::endl;    
    
    size_t max_workgroup_size;
    status = clGetDeviceInfo(device, CL_DEVICE_MAX_WORK_GROUP_SIZE, sizeof(size_t),
                             &max_workgroup_size, 0);
    CHECK_OPENCL_ERROR(status, "clGetDeviceInfo(CL_DEVICE_MAX_WORK_GROUP_SIZE)");
    std::cout << "\tCL_DEVICE_MAX_WORK_GROUP_SIZE: " << max_workgroup_size
              << std::endl;

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

    return SUCCESS;
}

int PrintBufferContents_Uint32(cl_mem buf, uint32 size, std::string name,
                               uint32 line_size)
{
    cl_int status;
    
    uint32* temp = (uint32*) malloc(size * sizeof(uint32));

    status = clEnqueueReadBuffer(gpu_queue, buf, CL_TRUE, 0,
                                 size * sizeof(uint32), temp,
                                 0, NULL, NULL);
    CHECK_OPENCL_ERROR(status, "clEnqueueReadBuffer");

    std::cout << "BUFFER: " << name << std::endl;
    
    for(uint32 i=0 ; i<size ; i++)
    {
        std::cout << temp[i];

        if(((i + 1) % line_size) == 0)
        {
            std::cout << std::endl;
        }
        else
        {
            std::cout << ",";
        }
    }

    std::cout << std::endl;

    free(temp);


    return SUCCESS;
}

void ResetLoopTimer(TestLoopTimer* loop_timer)
{
    loop_timer->num_successes = 0;
    loop_timer->total_time = 0;
    loop_timer->times.clear();
}

void TestCaseStarted(TestLoopTimer* loop_timer)
{
    assert(!loop_timer->timer.working);

    loop_timer->timer.working = true;
    loop_timer->timer.start = clock();
}

real64 TestCaseFinished(TestLoopTimer* loop_timer)
{
    assert(loop_timer->timer.working);

    loop_timer->timer.working = false;
    clock_t diff = clock() - loop_timer->timer.start;
    real64 time = ((real64)diff / CLOCKS_PER_SEC) * 1000.0;
    
    loop_timer->total_time += time;
    loop_timer->times.push_back(time);
    //std::cout << "time elapsed = " << diff << std::endl;
    return diff;
}

void DrawProgressBar(uint32 cur, uint32 target)
{
    std::string bar;
    bar = "[";
    uint32 progress = ((cur * 100) / target) / 10;

    uint32 i;

    for(i=0 ; i<progress ; ++i)
    {
        bar += "+++";
    }

    for(i=progress+1 ; i<=10 ; ++i)
    {
        bar += "   ";
    }

    bar += "]";
    std::cout << "\33[2K\r" << bar;
}

real64 GetMedian(TestLoopTimer* loop_timer)
{
    std::sort(loop_timer->times.begin(), loop_timer->times.end());

    return loop_timer->times[loop_timer->num_iterations / 2];
}
