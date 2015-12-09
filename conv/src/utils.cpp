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
