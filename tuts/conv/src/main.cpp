#define __CL_ENABLE_EXCEPTIONS

#include <CL/cl.hpp>
#include <fstream>
#include <iostream>
#include <vector>

#include "Utils/utils.h"
#include "Utils/bmp-utils.h"

static const char* inputImagePath = "../Images/cat.bmp";
static float gaussianBlurFilter[25] =
{
    1.0f/273.0f,  4.0f/273.0f,  7.0f/273.0f,  4.0f/273.0f,
    4.0f/273.0f, 16.0f/273.0f, 26.0f/273.0f, 16.0f/273.0f,
    7.0f/273.0f, 26.0f/273.0f, 41.0f/273.0f, 26.0f/273.0f,
    4.0f/273.0f, 16.0f/273.0f, 26.0f/273.0f, 16.0f/273.0f,
    1.0f/273.0f,  4.0f/273.0f,  7.0f/273.0f,  4.0f/273.0f,
};
static const int gaussianBlurFilterWidth = 5;

int main()
{
    float* hInputImage;
    float* hOutputImage;

    int imageRows;
    int imageCols;

    int filterWidth = gaussianBlurFilterWidth;
    float* filter = gaussianBlurFilter;

    hInputImage = readBmpFloat(inputImagePath, &imageRows,
                               &imageCols);
    hOutputImage = new float[imageRows*imageCols];

    try
    {
        std::vector<cl::Platform> platforms;
        cl::Platform::get(&platforms);

        std::vector<cl::Device> devices;
        platforms[0].getDevices(CL_DEVICE_TYPE_GPU, &devices);

        cl::Context context(devices);

        cl::CommandQueue queue = cl::CommandQueue(context,
                                                  devices[0]);
        
        cl::ImageFormat imageFormat = cl::ImageFormat(CL_R, CL_FLOAT);
        cl::Image2D inputImage = cl::Image2D(context,
                                             CL_MEM_READ_ONLY,
                                             imageFormat, imageCols,
                                             imageRows);
        cl::Image2D outputImage = cl::Image2D(context,
                                              CL_MEM_WRITE_ONLY,
                                              imageFormat, imageCols,
                                              imageRows);

        cl::Buffer filterBuffer = cl::Buffer(context,
                                             CL_MEM_READ_ONLY,
                                             filterWidth*filterWidth
                                             *sizeof(float));

        cl::size_t<3> origin;
        origin[0] = 0;
        origin[1] = 0;
        origin[2] = 0;
        cl::size_t<3> region;
        region[0] = imageCols;
        region[1] = imageRows;
        region[2] = 1;

        queue.enqueueWriteImage(inputImage, CL_TRUE, origin, region,
                                0, 0, hInputImage);

        queue.enqueueWriteBuffer(filterBuffer, CL_TRUE, 0,
                                 filterWidth*filterWidth
                                 *sizeof(float), filter);

        cl::Sampler sampler = cl::Sampler(context, CL_FALSE,
                                          CL_ADDRESS_CLAMP_TO_EDGE,
                                          CL_FILTER_NEAREST);

        std::ifstream sourceFile("image_convolution.cl");
        std::string sourceCode(std::istreambuf_iterator<char>(
                                   sourceFile),
                               (std::istreambuf_iterator<char>()));

        cl::Program::Sources source(1, std::make_pair(
                                        sourceCode.c_str(),
                                        sourceCode.length() + 1));

        cl::Program program = cl::Program(context, source);
        program.build(devices);
        
        cl::Kernel kernel(program, "convolution");
        kernel.setArg(0, inputImage);
        kernel.setArg(1, outputImage);
        kernel.setArg(2, filterBuffer);
        kernel.setArg(3, filterWidth);
        kernel.setArg(4, sampler);

        cl::NDRange global(imageCols, imageRows);
        cl::NDRange local(8, 8);

        queue.enqueueNDRangeKernel(kernel, cl::NullRange, global,
                                   local);

        queue.enqueueReadImage(outputImage, CL_TRUE, origin, region,
                               0, 0, hOutputImage);
        writeBmpFloat(hOutputImage, "cat_filtered.bmp", imageRows,
                      imageCols, inputImagePath);
    }
    catch(cl::Error error)
    {
        std::cout << error.what() << "(" << error.err() << ")"
                  << std::endl;
    }

    free(hInputImage);
    delete hOutputImage;
    return 0;
}
