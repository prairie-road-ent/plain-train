#include "PngEncoding.h"
#include "PngPixels.h"
#include <fcntl.h>
#include <libtcc.h>
#include "general.h"
#include <jansson.h>
#include <libgen.h>
#include <stdio.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>

String removeRelativePathDotSlash(String relativePath)
{
  return strncmp(relativePath, "./", 2) == 0 ? strdup(relativePath + 2) : strdup(relativePath);
}

int main(int argc, char* argv[])
{
  String relativeImageConfigPath = argv[1];
  json_t* imageConfigJson = json_load_file(relativeImageConfigPath, 0, NULL);
  String imageName = json_string_value(json_object_get(imageConfigJson, "imageName"));
  U32 imagePixelWidth = json_number_value(json_object_get(imageConfigJson, "imagePixelWidth"));
  U32 imagePixelHeight = json_number_value(json_object_get(imageConfigJson, "imagePixelHeight"));
  String imageRenderPixelsRelativePath = json_string_value(json_object_get(imageConfigJson, "imageRenderPixelsRelativePath"));
  String imageDirectoryRelativePath = dirname(strdup(relativeImageConfigPath));
  U32 imageDirectoryRelativePathLength = strlen(imageDirectoryRelativePath);
  String imageRenderPixelsRelativeTruncatedPath = removeRelativePathDotSlash(imageRenderPixelsRelativePath);
  U32 imageRenderPixelsRelativeTruncatedPathLength = strlen(imageRenderPixelsRelativeTruncatedPath);
  char imageRenderPixelsResolvedRelativePath[imageDirectoryRelativePathLength + 1 + imageRenderPixelsRelativeTruncatedPathLength];
  sprintf(imageRenderPixelsResolvedRelativePath, "%s%s%s", imageDirectoryRelativePath, "/", imageRenderPixelsRelativeTruncatedPath);
  U32 imageNameLength = strlen(imageName);
  char imageNameResolvedRelativePath[imageDirectoryRelativePathLength + 1 + imageNameLength + 4];
  sprintf(imageNameResolvedRelativePath, "%s%s%s%s", imageDirectoryRelativePath, "/", imageName, ".png");
  json_decref(imageConfigJson);
  int imageRenderPixelsFileDescriptor = open(imageRenderPixelsResolvedRelativePath, O_RDONLY);
  struct stat imageRenderPixelsFileStat;
  fstat(imageRenderPixelsFileDescriptor, &imageRenderPixelsFileStat);
  String imageRenderPixelsSourceFileText = (String)mmap(NULL, imageRenderPixelsFileStat.st_size, PROT_READ, MAP_PRIVATE, imageRenderPixelsFileDescriptor, 0);
  TCCState* tccState = tcc_new();
  tcc_add_include_path(tccState, imageDirectoryRelativePath);
  tcc_set_output_type(tccState, TCC_OUTPUT_MEMORY);
  tcc_compile_string(tccState, imageRenderPixelsSourceFileText);
  char pngEncodingObjectFilePath[imageDirectoryRelativePathLength + 1 + strlen("PngEncoding.o")];
  sprintf(pngEncodingObjectFilePath, "%s%s%s", imageDirectoryRelativePath, "/", "PngEncoding.o");
  tcc_add_file(tccState, pngEncodingObjectFilePath);
  char pngPixelsObjectFilePath[imageDirectoryRelativePathLength + 1 + strlen("PngPixels.o")];
  sprintf(pngPixelsObjectFilePath, "%s%s%s", imageDirectoryRelativePath, "/", "PngPixels.o");
  tcc_add_file(tccState, pngPixelsObjectFilePath);
  char generalObjectFilePath[imageDirectoryRelativePathLength + 1 + strlen("general.o")];
  sprintf(generalObjectFilePath, "%s%s%s", imageDirectoryRelativePath, "/", "general.o");
  tcc_add_file(tccState, generalObjectFilePath);
  tcc_relocate(tccState);
  void (*imageRenderPixels)(Rgb8bitPngPixels* pngPixels) = tcc_get_symbol(tccState, "imageRenderPixels");
  U64 pixelsSize =
    sizeofRgb8bitPngPixels(imagePixelWidth, imagePixelHeight);
  U64 maxEncodingSize =
    maxsizeofRgb8bitPngEncoding(imagePixelWidth, imagePixelHeight);
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
    imagePixelWidth,
    imagePixelHeight);
  initRgb8bitPngEncoding(
    pngEncoding,
    pngPixels);
  imageRenderPixels(pngPixels);
  encodeRgb8bitPngPixels(
    pngEncoding,
    pngPixels);
  FILE* pngFile_ptr =
    fopen(
      imageNameResolvedRelativePath,
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
