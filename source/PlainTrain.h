#ifndef PLAIN_TRAIN_H
#define PLAIN_TRAIN_H
#include "PngPixels.h"
#include "general.h"
#include <jansson.h>

#define projectConfigFileName__PlainTrain__VALUE "plain-train.json"
#define projectOutputDirectoryName__PlainTrain__VALUE "output"
#define renderGraphicPixelsFileName__PlainTrain__VALUE "renderGraphicPixels.c"

typedef struct
{
  U64 elementsCount;
  String* elements;
} StringArray;

typedef struct
{
  String graphicName;
  U32 graphicPixelsWidth;
  U32 graphicPixelsHeight;
  StringArray renderGraphicPixelsLinkedLibraries;
} PlainTrainConfig;

typedef void (*RenderGraphicPixelsCallback)(Rgb8bitPngPixels*);

U64 sizeofPlainTrainConfig(json_t* plainTrainConfigJson);
void initPlainTrainConfig(PlainTrainConfig* plainTrainConfig, json_t* plainTrainConfigJson);
RenderGraphicPixelsCallback compileRenderGraphicPixels(String renderGraphicPixelsFileAbsolutePath, PlainTrainConfig* projectConfig);
void updateGraphicImage(String renderGraphicPixelsFileAbsolutePath, PlainTrainConfig* projectConfig, Rgb8bitPngPixels* pngPixels, U8* pngEncoding, String graphicOutputAbsolutePath);

#endif
