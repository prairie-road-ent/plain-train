#include "PlainTrain.h"
#include "PngEncoding.h"
#include "PngPixels.h"
#include "general.h"

void updateGraphicImage(String renderGraphicPixelsFileAbsolutePath, PlainTrainConfig* projectConfig, String graphicOutputAbsolutePath)
{
  RenderGraphicPixelsCallback renderGraphicPixels =
    compileRenderGraphicPixels(
      renderGraphicPixelsFileAbsolutePath,
      projectConfig);
  U64 pixelsSize =
    sizeofRgb8bitPngPixels(
      projectConfig->graphicPixelsWidth,
      projectConfig->graphicPixelsHeight);
  U64 maxEncodingSize =
    maxsizeofRgb8bitPngEncoding(
      projectConfig->graphicPixelsWidth,
      projectConfig->graphicPixelsHeight);
  U64 poolSize =
    pixelsSize + maxEncodingSize;
  HeapAllocation pngPool =
    (HeapAllocation)malloc(poolSize);
  Rgb8bitPngPixels* pngPixels =
    (Rgb8bitPngPixels*)pngPool;
  HeapAllocation pngEncoding =
    pngPool + pixelsSize;
  initRgb8bitPngPixels(
    pngPixels,
    projectConfig->graphicPixelsWidth,
    projectConfig->graphicPixelsHeight);
  initRgb8bitPngEncoding(
    pngEncoding,
    pngPixels);
  renderGraphicPixels(
    pngPixels);
  encodeRgb8bitPngPixels(
    pngEncoding,
    pngPixels);
  writePngFile(
    graphicOutputAbsolutePath,
    pngEncoding);
  free(pngPool);
}
