#include "PlainTrain.h"
#include "PngEncoding.h"
#include "PngPixels.h"
#include "general.h"

void updateGraphicImage(String renderGraphicPixelsFileAbsolutePath, PlainTrainConfig* projectConfig, Rgb8bitPngPixels* pngPixels, U8* pngEncoding, String graphicOutputAbsolutePath)
{
  RenderGraphicPixelsCallback renderGraphicPixels =
    compileRenderGraphicPixels(
      renderGraphicPixelsFileAbsolutePath,
      projectConfig);
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
}
