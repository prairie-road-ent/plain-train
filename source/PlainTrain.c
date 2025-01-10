#include "PlainTrain.h"
#include <fcntl.h>
#include <jansson.h>
#include <libtcc.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

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

RenderGraphicPixelsCallback compileRenderGraphicPixels(String renderGraphicPixelsFileAbsolutePath, PlainTrainConfig* projectConfig)
{
  int imageRenderPixelsFileDescriptor =
    open(
      renderGraphicPixelsFileAbsolutePath,
      O_RDONLY);
  struct stat imageRenderPixelsFileStat;
  fstat(
    imageRenderPixelsFileDescriptor,
    &imageRenderPixelsFileStat);
  String imageRenderPixelsSourceFileText =
    (String)mmap(
      NULL,
      imageRenderPixelsFileStat.st_size,
      PROT_READ,
      MAP_PRIVATE,
      imageRenderPixelsFileDescriptor,
      0);
  close(imageRenderPixelsFileDescriptor);
  TCCState* tccState =
    tcc_new();
  tcc_set_output_type(
    tccState,
    TCC_OUTPUT_MEMORY);
  tcc_compile_string(
    tccState,
    imageRenderPixelsSourceFileText);
  tcc_add_library(
    tccState,
    "plain-train");
  for (U64 linkedLibraryIndex = 0; linkedLibraryIndex < projectConfig->renderGraphicPixelsLinkedLibraries.elementsCount; linkedLibraryIndex++)
  {
    tcc_add_library(
      tccState,
      &projectConfig->renderGraphicPixelsLinkedLibraries.elements[linkedLibraryIndex]);
  }
  tcc_relocate(
    tccState);
  return (RenderGraphicPixelsCallback)
    tcc_get_symbol(
      tccState,
      "renderGraphicPixels");
}
