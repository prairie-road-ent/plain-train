// #include "general.h"

// void executeImageRenderPixels(String relativeImageConfigPath)
// {
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
//   json_array_foreach(imageRenderPixelsLinkedLibrariesArray, currentLibraryIndex, currentLibraryLabel)
//   {
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
// }