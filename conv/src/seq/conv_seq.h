#if !defined(CONV_SEQ_H)
#define CONV_SEQ_H

// NOTE: it is assumed that out_img memory is already allocated
void Seq_ApplyStencil(ConvWrapper* wrapper);

internal
void HandleAllBoundries(ConvWrapper* wrapper);

internal
void ApplyStencilInnerStep(ConvWrapper* wrapper, uint32 row, uint32 col);

internal
void ApplyStencilBoundaryStep(ConvWrapper* wrapper, uint32 row, uint32 col);

#endif
