__kernel void test_svm_kernel(__global int* input)
{
    int idx = get_global_id(0);
    input[idx] = input[idx] + 1;
}