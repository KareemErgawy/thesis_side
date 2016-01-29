#include <stdio.h>
#include <CL/cl.h>

int main()
{
    
    cl_int status;
    cl_uint num_platforms = 0;
    
    status = clGetPlatformIDs(0, 0, &num_platforms);
//    CHECK_OPENCL_ERROR(status, "clGetPlatformIDs");

    cl_platform_id* platforms = (cl_platform_id*)malloc(num_platforms*sizeof(cl_platform_id));
//    CHECK_ALLOCATION(platforms, "devices");
    
    status = clGetPlatformIDs(num_platforms, platforms, NULL);
//    CHECK_OPENCL_ERROR(status, "clGetPlatformIDs");

    cl_platform_id platform = platforms[0];
    
    size_t platform_name_length = 0;
    status = clGetPlatformInfo(
        platform,
        CL_PLATFORM_NAME,
        0,
        0,
        &platform_name_length);

    char* platform_name = new char[platform_name_length];
    status = clGetPlatformInfo(
        platform,
        CL_PLATFORM_NAME,
        platform_name_length,
        platform_name,
        0);
    
    printf("Platform name: %s", platform_name);
    
    return 0;
}
