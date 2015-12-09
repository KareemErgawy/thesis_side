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
