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
