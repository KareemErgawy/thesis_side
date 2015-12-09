#if !defined(CONV_SEQ_H)
#define CONV_SEQ_H

global_variable real32* _in_img;
global_variable uint32 _img_width;
global_variable uint32 _img_height;
global_variable real32* _msk;
global_variable uint32 _msk_width;
global_variable uint32 _msk_height;
global_variable real32* _out_img;
global_variable uint32 _half_w;
global_variable uint32 _half_h;    

// NOTE: it is assumed that out_img memory is already allocated
void Seq_ApplyStencil(real32* in_img, uint32 img_width,
                  uint32 img_height, real32* msk, uint32 msk_width,
                  uint32 msk_height, real32* out_img);

internal
void HandleAllBoundries();

internal
void ApplyStencilInnerStep(uint32 row, uint32 col);

internal
void ApplyStencilBoundaryStep(uint32 row, uint32 col);

#endif
