#include <plain-train.h>

void renderGraphic(Rgb8bitPngPixels* pngPixels)
{
  U8 backgroundColorRed = 255;
  U8 backgroundColorGreen = 128;
  U8 backgroundColorBlue = 0;
  Rgb8bitPixelChannels* currentPixelChannels_ptr;
  for (U32 pixelRowIndex = 0; pixelRowIndex < pngPixels->height; pixelRowIndex++)
  {
    for (U32 pixelColumnIndex = 0; pixelColumnIndex < pngPixels->width; pixelColumnIndex++)
    {
      currentPixelChannels_ptr =
        atPixelsDataPixelChannels(
          pngPixels,
          pixelColumnIndex,
          pixelRowIndex);
      currentPixelChannels_ptr->red =
        backgroundColorRed;
      currentPixelChannels_ptr->green =
        backgroundColorGreen;
      currentPixelChannels_ptr->blue =
        backgroundColorBlue;
    }
  }
}
