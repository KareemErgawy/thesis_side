__kernel
void consumerKernel(pipe __read_only float* inputPipe,
                    int totalPixels,
		    __global int* histogram)
{
    int pixelCnt;
    float pixel;

    for(pixelCnt=0 ; pixelCnt<totalPixels ; pixelCnt++)
    {
        while(read_pipe(inputPipe, &pixel));
	histogram[(int)pixel]++;
    }
}