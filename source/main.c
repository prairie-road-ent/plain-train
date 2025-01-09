#include "PlainTrain.h"
#include "general.h"
#include <jansson.h>
#include <limits.h>
#include <linux/limits.h>
#include <stdio.h>
#include <string.h>

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

// void loadProjectConfig(PlainTrainConfig* projectConfigResult, String projectConfigFileAbsolutePath)
// {
//   json_t* projectConfigJson =
//     json_load_file(
//       projectConfigFileAbsolutePath,
//       0,
//       NULL);
//   String graphicNameReference =
//     (String)json_string_value(
//       json_object_get(
//         projectConfigJson,
//         "graphicName"));
//   U32 graphicPixelsWidthValue =
//     (U32)json_number_value(
//       json_object_get(
//         projectConfigJson,
//         "graphicPixelsWidth"));
//   U32 graphicPixelsHeightValue =
//     (U32)json_number_value(
//       json_object_get(
//         projectConfigJson,
//         "graphicPixelsHeight"));
//   json_t* renderGraphicPixelsLinkedLibrariesJsonReference =
//     json_object_get(
//       projectConfigJson,
//       "renderGraphicPixelsLinkedLibraries");
//   U64 graphicNameStringSize =
//     strlen(graphicNameReference) + 1;
//   U64 renderGraphicPixelsLinkedLibrariesSize = 0;
//   U64 renderGraphicPixelsLinkedLibrariesCount = 0;
//   size_t linkedLibraryIndex;
//   json_t* linkedLibraryLinkLabel;
//   json_array_foreach(renderGraphicPixelsLinkedLibrariesJsonReference, linkedLibraryIndex, linkedLibraryLinkLabel)
//   {
//     renderGraphicPixelsLinkedLibrariesSize =
//       renderGraphicPixelsLinkedLibrariesSize + sizeof(String) + strlen((String)json_string_value(linkedLibraryLinkLabel)) + 1;
//     renderGraphicPixelsLinkedLibrariesCount =
//       renderGraphicPixelsLinkedLibrariesCount + 1;
//   }
//   projectConfigResult =
//     (PlainTrainConfig*)malloc(
//       sizeof(PlainTrainConfig) + graphicNameStringSize + renderGraphicPixelsLinkedLibrariesSize);
//   projectConfigResult->graphicName =
//     (String)((U8*)projectConfigResult + sizeof(PlainTrainConfig));
//   strncpy(
//     projectConfigResult->graphicName,
//     graphicNameReference,
//     strlen(graphicNameReference));
//   projectConfigResult->graphicPixelsWidth =
//     graphicPixelsWidthValue;
//   projectConfigResult->graphicPixelsHeight =
//     graphicPixelsHeightValue;
//   projectConfigResult->renderGraphicPixelsLinkedLibraries.elementsCount =
//     renderGraphicPixelsLinkedLibrariesCount;
//   projectConfigResult->renderGraphicPixelsLinkedLibraries.elements =
//     (String*)((U8*)projectConfigResult + sizeof(PlainTrainConfig) + graphicNameStringSize);
//   json_array_foreach(renderGraphicPixelsLinkedLibrariesJsonReference, linkedLibraryIndex, linkedLibraryLinkLabel)
//   {
//     // strncpy(
//     //   projectConfigResult->renderGraphicPixelsLinkedLibraries.elements[linkedLibraryIndex],
//     //   json_string_value(linkedLibraryLinkLabel),
//     //   strlen(json_string_value(linkedLibraryLinkLabel)));
//   }
//   json_decref(projectConfigJson);
//   printf("%s\n", (String)((U8*)projectConfigResult + sizeof(PlainTrainConfig) + graphicNameStringSize));
//   printf("%d\n", projectConfigResult->graphicPixelsWidth);
//   printf("%d\n", projectConfigResult->graphicPixelsHeight);
//   printf("%d\n", projectConfigResult->renderGraphicPixelsLinkedLibraries.elementsCount);
//   // for (U64 foo = 0; foo < projectConfigResult->renderGraphicPixelsLinkedLibraries.elementsCount; foo++)
//   // {
//   //   printf("%s\n", projectConfigResult->renderGraphicPixelsLinkedLibraries.elements[foo]);
//   // }
// }

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
  printf("%s\n", projectConfigFileAbsolutePath);
  printf("%s\n", projectOutputDirectoryAbsolutePath);
  printf("%s\n", renderGraphicPixelsFileAbsolutePath);
  // PlainTrainConfig* projectConfig;
  // loadProjectConfig(
  //   projectConfig,
  //   projectConfigFileAbsolutePath);
  // free(projectConfig);
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
