#ifndef TEAPACKET_GRAPHICS_IMAGEDATA_H
#define TEAPACKET_GRAPHICS_IMAGEDATA_H
#ifdef __cplusplus
extern "C"
{
#endif

#include "TeaPacket/Graphics/Common/ImageFormat.h"
#include "TeaPacket/Types/Numeric.h"

typedef struct
{
    /**
     * A pointer to the raw image data. The format of that data depends on the format of this image.
    */
    void* data;
    /**
     * The pitch of the image. This defines how many bytes one row of pixels is.
     * @details If 0, then the width of the image multiplied by the bytes per pixel of the format should be used as the pitch.
     */
    tp_u32 pitch;
    /**
     * The width of the image, in pixels.
     */
    tp_u16 width;
    /**
     * The height of the image, in pixels.
     */
    tp_u16 height;
    /**
     * The format of the image.
     */
    TP_Gfx_Image_Format format;
} TP_Gfx_ImageData;

#ifdef __cplusplus
}
#endif
#endif
