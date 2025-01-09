#ifndef PLAIN_TRAIN_H
#define PLAIN_TRAIN_H
#include "general.h"

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

#endif
