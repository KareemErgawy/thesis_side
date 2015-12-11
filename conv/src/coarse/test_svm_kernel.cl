__kernel void test_svm_kernel(__global void* input)
{
    __global int* intInput = (__global int*)(input);

    int idx = get_global_id(0);
    printf("input[%d] = %d\n", intInput[idx], idx);
}