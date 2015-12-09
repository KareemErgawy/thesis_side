#define __CL_ENABLE_EXCEPTIONS

#include <CL/cl.hpp>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

int main()
{
    const int elements = 2048;
    size_t datasize = sizeof(int)*elements;

    int* A = new int[elements];
    int* B = new int[elements];
    int* C = new int[elements];
    int* expC = new int[elements];

    for(int i=0 ; i<elements ; i++)
    {
        A[i] = i;
        B[i] = i;
        expC[i] = A[i] + B[i];
    }

    try
    {
        std::vector<cl::Platform> platforms;
        cl::Platform::get(&platforms);

        std::vector<cl::Device> devices;
        platforms[0].getDevices(CL_DEVICE_TYPE_ALL, &devices);

        cl::Context context(devices);

        cl::CommandQueue queue = cl::CommandQueue(context,
                                                  devices[0]);
        cl::Buffer bufferA = cl::Buffer(context, CL_MEM_READ_ONLY,
                                        datasize);
        cl::Buffer bufferB = cl::Buffer(context, CL_MEM_READ_ONLY,
                                        datasize);
        cl::Buffer bufferC = cl::Buffer(context, CL_MEM_WRITE_ONLY,
                                        datasize);

        queue.enqueueWriteBuffer(bufferA, CL_TRUE, 0, datasize, A);
        queue.enqueueWriteBuffer(bufferB, CL_TRUE, 0, datasize, B);

        std::ifstream sourceFile("vector_add_kernel.cl");
        std::string sourceCode(std::istreambuf_iterator<char> (
                                   sourceFile),
                               (std::istreambuf_iterator<char>()));

        cl::Program::Sources source(1, std::make_pair(
                                        sourceCode.c_str(),
                                        sourceCode.length() + 1));
        cl::Program program = cl::Program(context, source);
        program.build(devices);

        cl::Kernel vecadd_kernel(program, "vecadd");

        vecadd_kernel.setArg(0, bufferA);
        vecadd_kernel.setArg(1, bufferB);
        vecadd_kernel.setArg(2, bufferC);

        cl::NDRange global(elements);
        cl::NDRange local(256);
        queue.enqueueNDRangeKernel(vecadd_kernel, cl::NullRange,
                                   global, local);

        queue.enqueueReadBuffer(bufferC, CL_TRUE, 0, datasize, C);

        
        bool testPassed = true;

        for(int i=0 ; i<elements ; i++)
        {
            if(C[i] != expC[i])
            {
                testPassed = false;
            }
        }

        std::cout << (testPassed ? "SUCCESS\n" : "FAILURE\n");
    }
    catch(cl::Error error)
    {
        std::cout << error.what() << "(" << error.err() << ")" <<
            std::endl;
    }

    return 0;
}
