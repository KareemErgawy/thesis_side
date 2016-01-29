@echo off

clang++ -I "C:/Program Files (x86)/Intel/OpenCL SDK/5.3/include/" main.cpp -o clang_cl_test.exe -L"C:/Program Files (x86)/Intel/OpenCL SDK/5.3/lib/x86/" -lOpenCL
