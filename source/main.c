#include "PlainTrain.h"
#include "PngEncoding.h"
#include "PngPixels.h"
#include "general.h"
#include <fcntl.h>
#include <jansson.h>
#include <libtcc.h>
#include <limits.h>
#include <linux/limits.h>
#include <stdio.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

void removePathTrailingDelimiter(String pathResult, String pathSource)
{
  U64 pathSourceLength =
    strlen(pathSource);
  pathSource[pathSourceLength - 1] == PATH_SEPARATOR
    ? strncpy(
        pathResult,
        pathSource,
        pathSourceLength - 1)
    : strncpy(
        pathResult,
        pathSource,
        pathSourceLength);
}

void resolveDirectoryChildPath(String childFilePathResult, String parentDirectoryAbsolutePath, String childName)
{
  sprintf(
    childFilePathResult,
    "%s%s%s",
    parentDirectoryAbsolutePath,
    "/",
    childName);
}

int main(int argc, char* argv[])
{
  String projectDirectoryAbsolutePathArgument = argv[1];
  StringBuffer projectDirectoryAbsolutePath[PATH_MAX];
  removePathTrailingDelimiter(
    projectDirectoryAbsolutePath,
    projectDirectoryAbsolutePathArgument);
  StringBuffer projectConfigFileAbsolutePath[PATH_MAX];
  StringBuffer renderGraphicPixelsFileAbsolutePath[PATH_MAX];
  StringBuffer projectOutputDirectoryAbsolutePath[PATH_MAX];
  resolveDirectoryChildPath(
    projectConfigFileAbsolutePath,
    projectDirectoryAbsolutePath,
    projectConfigFileName__PlainTrain__VALUE);
  resolveDirectoryChildPath(
    projectOutputDirectoryAbsolutePath,
    projectDirectoryAbsolutePath,
    projectOutputDirectoryName__PlainTrain__VALUE);
  resolveDirectoryChildPath(
    renderGraphicPixelsFileAbsolutePath,
    projectDirectoryAbsolutePath,
    renderGraphicPixelsFileName__PlainTrain__VALUE);
  json_t* projectConfigJson =
    json_load_file(
      projectConfigFileAbsolutePath,
      0,
      NULL);
  U64 projectConfigSize =
    sizeofPlainTrainConfig(
      projectConfigJson);
  PlainTrainConfig* projectConfig =
    (PlainTrainConfig*)malloc(projectConfigSize);
  initPlainTrainConfig(
    projectConfig,
    projectConfigJson);
  json_decref(projectConfigJson);
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
  RenderGraphicPixelsCallback renderGraphicPixels =
    (RenderGraphicPixelsCallback)tcc_get_symbol(
      tccState,
      "renderGraphicPixels");
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
  mkdir(
    projectOutputDirectoryAbsolutePath,
    0755);
  StringBuffer graphicOutputFilename[strlen(projectConfig->graphicName) + 4 + 1];
  sprintf(
    graphicOutputFilename,
    "%s%s",
    projectConfig->graphicName,
    ".png");
  StringBuffer graphicOutputAbsolutePath[PATH_MAX];
  resolveDirectoryChildPath(
    graphicOutputAbsolutePath,
    projectOutputDirectoryAbsolutePath,
    graphicOutputFilename);
  FILE* pngFile_ptr =
    fopen(
      graphicOutputAbsolutePath,
      "wb");
  fwrite(
    pngEncoding,
    1,
    getRgb8bitPngEncodingSize(pngEncoding),
    pngFile_ptr);
  fclose(pngFile_ptr);
  free(pngPool);
  return 0;
}

// #include "PngEncoding.h"
// #include "PngPixels.h"
// #include "general.h"
// #include <fcntl.h>
// #include <jansson.h>
// #include <libgen.h>
// #include <libtcc.h>
// #include <stdio.h>
// #include <string.h>
// #include <sys/mman.h>
// #include <sys/stat.h>

// String removeRelativePathDotSlash(String relativePath)
// {
//   return strncmp(relativePath, "./", 2) == 0 ? strdup(relativePath + 2) : strdup(relativePath);
// }

// int main(int argc, char* argv[])
// {
//   String relativeImageConfigPath = argv[1];
//   json_t* imageConfigJson = json_load_file(relativeImageConfigPath, 0, NULL);
//   String imageName = json_string_value(json_object_get(imageConfigJson, "imageName"));
//   U32 imagePixelWidth = json_number_value(json_object_get(imageConfigJson, "imagePixelWidth"));
//   U32 imagePixelHeight = json_number_value(json_object_get(imageConfigJson, "imagePixelHeight"));
//   String imageRenderPixelsRelativePath = json_string_value(json_object_get(imageConfigJson, "imageRenderPixelsRelativePath"));
//   json_t* imageRenderPixelsLinkedLibrariesArray = json_object_get(imageConfigJson, "imageRenderPixelsLinkedLibraries");
//   String imageDirectoryRelativePath = dirname(strdup(relativeImageConfigPath));
//   U32 imageDirectoryRelativePathLength = strlen(imageDirectoryRelativePath);
//   String imageRenderPixelsRelativeTruncatedPath = removeRelativePathDotSlash(imageRenderPixelsRelativePath);
//   U32 imageRenderPixelsRelativeTruncatedPathLength = strlen(imageRenderPixelsRelativeTruncatedPath);
//   char imageRenderPixelsResolvedRelativePath[imageDirectoryRelativePathLength + 1 + imageRenderPixelsRelativeTruncatedPathLength];
//   sprintf(imageRenderPixelsResolvedRelativePath, "%s%s%s", imageDirectoryRelativePath, "/", imageRenderPixelsRelativeTruncatedPath);
//   U32 imageNameLength = strlen(imageName);
//   char imageNameResolvedRelativePath[imageDirectoryRelativePathLength + 1 + imageNameLength + 4];
//   sprintf(imageNameResolvedRelativePath, "%s%s%s%s", imageDirectoryRelativePath, "/", imageName, ".png");
//   int imageRenderPixelsFileDescriptor = open(imageRenderPixelsResolvedRelativePath, O_RDONLY);
//   struct stat imageRenderPixelsFileStat;
//   fstat(imageRenderPixelsFileDescriptor, &imageRenderPixelsFileStat);
//   String imageRenderPixelsSourceFileText = (String)mmap(NULL, imageRenderPixelsFileStat.st_size, PROT_READ, MAP_PRIVATE, imageRenderPixelsFileDescriptor, 0);
//   TCCState* tccState = tcc_new();
//   tcc_set_output_type(tccState, TCC_OUTPUT_MEMORY);
//   tcc_compile_string(tccState, imageRenderPixelsSourceFileText);
//   tcc_add_library(tccState, "plain-train");
//   size_t currentLibraryIndex;
//   json_t* currentLibraryLabel;
//   json_array_foreach(imageRenderPixelsLinkedLibrariesArray, currentLibraryIndex, currentLibraryLabel) {
//     tcc_add_library(tccState, json_string_value(currentLibraryLabel));
//   }
//   json_decref(imageConfigJson);
//   tcc_relocate(tccState);
//   void (*imageRenderPixels)(Rgb8bitPngPixels* pngPixels) = tcc_get_symbol(tccState, "imageRenderPixels");
//   U64 pixelsSize =
//     sizeofRgb8bitPngPixels(imagePixelWidth, imagePixelHeight);
//   U64 maxEncodingSize =
//     maxsizeofRgb8bitPngEncoding(imagePixelWidth, imagePixelHeight);
//   U64 poolSize =
//     pixelsSize + maxEncodingSize;
//   HeapAllocation pngPool =
//     (HeapAllocation)malloc(poolSize);
//   Rgb8bitPngPixels* pngPixels =
//     (Rgb8bitPngPixels*)pngPool;
//   HeapAllocation pngEncoding =
//     pngPool + pixelsSize;
//   initRgb8bitPngPixels(
//     pngPixels,
//     imagePixelWidth,
//     imagePixelHeight);
//   initRgb8bitPngEncoding(
//     pngEncoding,
//     pngPixels);
//   imageRenderPixels(pngPixels);
//   encodeRgb8bitPngPixels(
//     pngEncoding,
//     pngPixels);
//   FILE* pngFile_ptr =
//     fopen(
//       imageNameResolvedRelativePath,
//       "wb");
//   fwrite(
//     pngEncoding,
//     1,
//     getRgb8bitPngEncodingSize(pngEncoding),
//     pngFile_ptr);
//   fclose(pngFile_ptr);
//   free(pngPool);
//   return 0;
// }
