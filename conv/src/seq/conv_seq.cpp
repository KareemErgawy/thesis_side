#include <seq/conv_seq.h>
#include <cassert>

void Seq_ApplyStencil(real32* in_img, uint32 img_width,
                  uint32 img_height, real32* msk, uint32 msk_width,
                  uint32 msk_height, real32* out_img)
{
    std::cout << "Sequential Convolution START!" << std::endl;
    //Print2DArray("Input Image: ", in_img, img_width, img_height);
    _in_img = in_img;
    _img_width = img_width;
    _img_height = img_height;
    _msk = msk;
    _msk_width = msk_width;
    _msk_height = msk_height;
    _out_img = out_img;
    _half_w = msk_width / 2;
    _half_h = msk_height / 2;

    HandleAllBoundries();
    
    // inner regions
    for(uint32 c = _half_w ; c < img_width-_half_w ; c++)
    {
        for(uint32 r = _half_h ; r < img_height-_half_h ; r++)
        {
            ApplyStencilInnerStep(r, c);
        }
    }

    //Print2DArray("Output Image: ", out_img, img_width, img_height);
    std::cout << "Sequential Convolution FINISH!" << std::endl;
    std::cout << "======================" << std::endl;
}

internal
void HandleAllBoundries()
{
    
    uint32 c, r;
    
    // top boundary
    for(c = 0 ; c < _img_width ; c++)
    {
        for(r = 0 ; r < _half_h ; r++)
        {
            ApplyStencilBoundaryStep(r, c);
        }
    }

    // left boundary
    for(c = 0 ; c < _half_w ; c++)
    {
        for(r = _half_h ; r < _img_height-_half_h ; r++)
        {
            ApplyStencilBoundaryStep(r, c);
        }
    }
    
    // bottom boundary
    for(c = 0 ; c < _img_width ; c++)
    {
        for(r = _img_height-1 ; r >= _img_height-_half_h ; r--)
        {
            ApplyStencilBoundaryStep(r, c);
        }
    }

    // right boundary
    for(c = _img_width-1 ; c >= _img_width-_half_w ; c--)
    {
        for(r = _half_h ; r < _img_height-_half_h ; r++)
        {
            ApplyStencilBoundaryStep(r, c);
        }
    }    
}

internal
void ApplyStencilInnerStep(uint32 row, uint32 col)
{
    for(int32 c = -_half_w ; c <= (int32)_half_w ; c++)
    {
        for(int32 r = -_half_h ; r <= (int32)_half_h ; r++)
        {
            _out_img[(row*_img_width)+col]
                += (_in_img[((row+r)*_img_width)+col+c]
                   *_msk[((_half_h+r)*_msk_width)+_half_w+c]);
        }
    }
}

internal
void ApplyStencilBoundaryStep(uint32 row, uint32 col)
{

    _out_img[(row*_img_width)+col] = 0;
    
    for(int32 c = -_half_w ; c <= (int32)_half_w ; c++)
    {
        for(int32 r = -_half_h ; r <= (int32)_half_h ; r++)
        {
            int32 r1 = r + row;
            int32 c1 = c + col;

//            std::cout << col << " " << c1 << " " << c << " ";
            
            // Mirror if < 0
            r1 = (r1 < 0) ? (-r-1) : r1;
            c1 = (c1 < 0) ? (-c-1) : c1;
            // Mirror if > dim
            r1 = (r1 >= (int32)_img_height) ? _img_height-r : r1;
            c1 = (c1 >= (int32)_img_width) ? _img_width-c : c1;

//            std::cout << c1 << std::endl;
            assert(r1 >= 0);
            assert(c1 >= 0);
            assert(r1 < (int32)_img_height);
            assert(c1 < (int32)_img_width);

            _out_img[(row*_img_width)+col]
                += (_in_img[(r1*_img_width)+c1]
                   *_msk[((_half_h+r)*_msk_width)+_half_w+c]);
        }
    }
}
