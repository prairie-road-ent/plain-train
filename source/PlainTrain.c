#include "PlainTrain.h"
#include <jansson.h>
#include <string.h>

U64 sizeofPlainTrainConfig(json_t* plainTrainConfigJson)
{
  U64 graphicNameSize =
    json_string_length(
      json_object_get(
        plainTrainConfigJson,
        "graphicName"));
  U64 renderGraphicPixelsLinkedLibrariesSize = 0;
  size_t includedLibraryIndex;
  json_t* linkedLibraryLabel;
  json_array_foreach(
    json_object_get(
      plainTrainConfigJson,
      "renderGraphicPixelsLinkedLibraries"),
    includedLibraryIndex,
    linkedLibraryLabel)
  {
    renderGraphicPixelsLinkedLibrariesSize =
      renderGraphicPixelsLinkedLibrariesSize + sizeof(String) + json_string_length(linkedLibraryLabel) + 1;
  }
  return sizeof(PlainTrainConfig) + graphicNameSize + renderGraphicPixelsLinkedLibrariesSize;
}

void initPlainTrainConfig(PlainTrainConfig* plainTrainConfig, json_t* plainTrainConfigJson)
{
  plainTrainConfig->graphicName =
    (String)((U8*)plainTrainConfig + sizeof(PlainTrainConfig));
  strcpy(
    plainTrainConfig->graphicName,
    json_string_value(
      json_object_get(
        plainTrainConfigJson,
        "graphicName")));
  plainTrainConfig->graphicPixelsWidth =
    (U32)json_number_value(
      json_object_get(
        plainTrainConfigJson,
        "graphicPixelsWidth"));
  plainTrainConfig->graphicPixelsHeight =
    (U32)json_number_value(
      json_object_get(
        plainTrainConfigJson,
        "graphicPixelsHeight"));
  plainTrainConfig->renderGraphicPixelsLinkedLibraries.elements =
    (String*)((U8*)plainTrainConfig + sizeof(PlainTrainConfig) + strlen((plainTrainConfig->graphicName)) + 1);
  U64 renderGraphicPixelsLinkedLibrariesCount = 0;
  size_t linkedLibraryIndex;
  json_t* linkedLibraryLinkLabel;
  json_array_foreach(
    json_object_get(
      plainTrainConfigJson,
      "renderGraphicPixelsLinkedLibraries"),
    linkedLibraryIndex,
    linkedLibraryLinkLabel)
  {
    renderGraphicPixelsLinkedLibrariesCount =
      renderGraphicPixelsLinkedLibrariesCount + 1;
    strcpy(
      (String)&plainTrainConfig->renderGraphicPixelsLinkedLibraries.elements[linkedLibraryIndex],
      json_string_value(linkedLibraryLinkLabel));
  }
  plainTrainConfig->renderGraphicPixelsLinkedLibraries.elementsCount =
    renderGraphicPixelsLinkedLibrariesCount;
}
