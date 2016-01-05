// TODO come back to this later because it didn't work quite well.
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <string.h>

#include <CL/cl.h>

#include "Utils/bmp-utils.h"

void check(cl_int status);
void printCompilerError(cl_program program, cl_device_id device);
char* readFile(const char *filename);

static float gaussianBlurFilter[25] =
{
    1.0f/273.0f,  4.0f/273.0f,  7.0f/273.0f,  4.0f/273.0f, 1.0f/273.0f,
    4.0f/273.0f, 16.0f/273.0f, 26.0f/273.0f, 16.0f/273.0f, 4.0f/273.0f,
    7.0f/273.0f, 26.0f/273.0f, 41.0f/273.0f, 26.0f/273.0f, 7.0f/273.0f,
    4.0f/273.0f, 16.0f/273.0f, 26.0f/273.0f, 16.0f/273.0f, 4.0f/273.0f,
    1.0f/273.0f,  4.0f/273.0f,  7.0f/273.0f,  4.0f/273.0f, 1.0f/273.0f
};

static const int filterWidth = 5;
static const int filterSize = 25*sizeof(float);

static const int HIST_BINS = 256;

int main(int argc, char** argv)
{
    float* hInputImage = NULL;
    int* hOutputHistogram = NULL;
    int imageRows;
    int imageCols;
    hInputImage = readBmpFloat("../Images/cat.bmp", & imageRows,
                               &imageCols);

    const int imageElements = imageRows * imageCols;
    const size_t imageSize = imageElements * sizeof(float);

    const int histogramSize = HIST_BINS * sizeof(int);
    hOutputHistogram = (int*)malloc(histogramSize);
    if(!hOutputHistogram)
    {
        exit(-1);
    }

    cl_int status;

    cl_platform_id platform;
    status = clGetPlatformIDs(1, &platform, NULL);
    check(status);

    cl_device_id devices[2];
    cl_device_id gpuDevice;
    cl_device_id cpuDevice;
    status = clGetDeviceIDs(platform, CL_DEVICE_TYPE_GPU, 1,
                            &gpuDevice, NULL);
    check(status);
    status = clGetDeviceIDs(platform, CL_DEVICE_TYPE_CPU, 1,
                            &cpuDevice, NULL);
    check(status);
    devices[0] = gpuDevice;
    devices[1] = cpuDevice;

    cl_context context;
    context = clCreateContext(NULL, 2, devices, NULL, NULL, &status);
    check(status);

    cl_command_queue gpuQueue;
    cl_command_queue cpuQueue;
    gpuQueue = clCreateCommandQueue(context, gpuDevice, 0, &status);
    check(status);
    cpuQueue = clCreateCommandQueue(context, cpuDevice, 0, &status);
    check(status);

    cl_image_desc desc;
    desc.image_type = CL_MEM_OBJECT_IMAGE2D;
    desc.image_width = imageCols;
    desc.image_height = imageRows;
    desc.image_depth = 0;
    desc.image_array_size = 0;
    desc.image_row_pitch = 0;
    desc.image_slice_pitch = 0;
    desc.num_mip_levels = 0;
    desc.num_samples = 0;
    desc.buffer = NULL;

    cl_image_format format;
    format.image_channel_order = CL_R;
    format.image_channel_data_type = CL_FLOAT;

    cl_mem inputImage;
    inputImage = clCreateImage(context, CL_MEM_READ_ONLY, &format,
                               &desc, NULL, NULL);
    check(status);

    cl_mem outputHistogram;
    outputHistogram = clCreateBuffer(context, CL_MEM_WRITE_ONLY,
                                     histogramSize, NULL, &status);
    check(status);

    cl_mem filter;
    filter = clCreateBuffer(context, CL_MEM_READ_ONLY, filterSize,
                            NULL, &status);
    check(status);

    cl_mem pipe;
    pipe = clCreatePipe(context, 0, sizeof(float),
                        imageRows*imageCols, NULL, &status);

    size_t origin[3] = {0, 0, 0};
    size_t region[3] = {imageCols, imageRows, 1};
    status = clEnqueueWriteImage(gpuQueue, inputImage, CL_TRUE,
                                 origin, region, 0, 0, hInputImage,
                                 0, NULL, NULL);
    check(status);

    status = clEnqueueWriteBuffer(gpuQueue, filter, CL_TRUE, 0,
                                  filterSize, gaussianBlurFilter,
                                  0, NULL, NULL);
    check(status);

    int zero = 0;
    status = clEnqueueFillBuffer(cpuQueue, outputHistogram, &zero,
                                 sizeof(int), 0, histogramSize, 0,
                                 NULL, NULL);
    check(status);

    char* programSource = readFile("producer-consumer.cl");
    size_t programSourceLen = strlen(programSource);
    cl_program program = clCreateProgramWithSource(
        context, 1, (const char**)&programSource, &programSourceLen,
        &status);
    check(status);

    std::string flags_str = "-I ./ -cl-std=CL2.0";
    
    status = clBuildProgram(program, 2, devices, flags_str.c_str(),
                            NULL, NULL);

    if(status != CL_SUCCESS)
    {
        printCompilerError(program, gpuDevice);
        exit(-1);
    }

    cl_kernel producerKernel;
    cl_kernel consumerKernel;

    producerKernel = clCreateKernel(program, "producerKernel",
                                    &status);
    check(status);

    consumerKernel = clCreateKernel(program, "consumerKernel",
                                    &status);
    check(status);

    status = clSetKernelArg(producerKernel, 0, sizeof(cl_mem),
                            &inputImage);
    status |= clSetKernelArg(producerKernel, 1, sizeof(cl_mem),
                             &pipe);
    status |= clSetKernelArg(producerKernel, 2, sizeof(cl_mem),
                             &filter);
    status |= clSetKernelArg(producerKernel, 3, sizeof(int),
                             &filterWidth);
    check(status);

    status = clSetKernelArg(consumerKernel, 0, sizeof(cl_mem),
                            &pipe);
    status = clSetKernelArg(consumerKernel, 1, sizeof(int),
                            &imageElements);
    status = clSetKernelArg(consumerKernel, 2, sizeof(cl_mem),
                            &outputHistogram);
    check(status);

    size_t producerGlobalSize[2];
    producerGlobalSize[0] = imageCols;
    producerGlobalSize[1] = imageRows;

    size_t producerLocalSize[2];
    producerLocalSize[0] = 8;
    producerLocalSize[1] = 8;

    size_t consumerGlobalSize[1];
    consumerGlobalSize[0] = 1;

    size_t consumerLocalSize[1];
    consumerLocalSize[0] = 1;

    status = clEnqueueNDRangeKernel(gpuQueue, producerKernel, 2, NULL,
                                    producerGlobalSize,
                                    producerLocalSize,
                                    0, NULL, NULL);
    check(status);

    status = clEnqueueNDRangeKernel(cpuQueue, consumerKernel, 1, NULL,
                                    consumerGlobalSize,
                                    consumerLocalSize,
                                    0, NULL, NULL);

    status = clEnqueueReadBuffer(cpuQueue, outputHistogram, CL_TRUE,
                                 0, histogramSize, hOutputHistogram,
                                 0, NULL, NULL);
    check(status);


    for(int i=0 ; i<HIST_BINS ; i++)
    {
        std::cout << i << ">" << hOutputHistogram[i] << " | ";

        if((i % 10) == 0)
        {
            std::cout << std::endl;
        }
    }
    
    clReleaseKernel(producerKernel);
    clReleaseKernel(consumerKernel);
    clReleaseProgram(program);
    clReleaseCommandQueue(gpuQueue);
    clReleaseCommandQueue(cpuQueue);
    clReleaseMemObject(inputImage);
    clReleaseMemObject(outputHistogram);
    clReleaseMemObject(filter);
    clReleaseMemObject(pipe);
    clReleaseContext(context);

    free(hInputImage);
    free(hOutputHistogram);
    free(programSource);

    return 0;
}


void check(cl_int status) {

   if (status != CL_SUCCESS) {
      printf("OpenCL error (%d)\n", status);
      exit(-1);
   }
}

void printCompilerError(cl_program program, cl_device_id device) {
   cl_int status;

   size_t logSize;
   char *log;

   /* Get the log size */
   status = clGetProgramBuildInfo(program, device, CL_PROGRAM_BUILD_LOG,
               0, NULL, &logSize);
   check(status);

   /* Allocate space for the log */
   log = (char*)malloc(logSize);
   if (!log) {
      exit(-1);
   }

   /* Read the log */
   status = clGetProgramBuildInfo(program, device, CL_PROGRAM_BUILD_LOG,
               logSize, log, NULL);
   check(status);

   /* Print the log */
   printf("%s\n", log);
}

char* readFile(const char *filename) {

   FILE *fp;
   char *fileData;
   long fileSize;
   
   /* Open the file */
   fp = fopen(filename, "r");
   if (!fp) {
      printf("Could not open file: %s\n", filename);
      exit(-1);
   }

   /* Determine the file size */
   if (fseek(fp, 0, SEEK_END)) {
      printf("Error reading the file\n");
      exit(-1);
   }
   fileSize = ftell(fp);
   if (fileSize < 0) {
      printf("Error reading the file\n");
      exit(-1);
   }
   if (fseek(fp, 0, SEEK_SET)) {
      printf("Error reading the file\n");
      exit(-1);
   }

   /* Read the contents */
   fileData = (char*)malloc(fileSize + 1);
   if (!fileData) { 
      exit(-1); 
   }
   if (fread(fileData, fileSize, 1, fp) != 1) {
      printf("Error reading the file\n");
      exit(-1);
   }

   /* Terminate the string */
   fileData[fileSize] = '\0';

   /* Close the file */
   if (fclose(fp)) {
      printf("Error closing the file\n");
      exit(-1);
   }

   return fileData;
}
