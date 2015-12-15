#if !defined(CONV_COARSE_H)
#define CONV_COARSE_H

// NOTE: it is assumed that out_img memory is already allocated
int Coarse_ApplyStencil(real32* in_img, uint32 img_width,
                        uint32 img_height, real32* msk,
                        uint32 msk_width, uint32 msk_height,
                        real32* out_img, bool use_urolled=true);

#endif
