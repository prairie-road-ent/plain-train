// #include "PngEncoding.h"
// #include "PngPixels.h"
// #include <fcntl.h>
// #include <libtcc.h>
// #include <malloc.h>
// #include <stdio.h>
// #include <stdlib.h>
// #include <sys/mman.h>
// #include <sys/stat.h>
#include <jansson.h>

int main(int argc, char* argv[])
{
  json_t* fooJson = json_load_file("foo.json", 0, NULL);
  json_t* namePropertyValue = json_object_get(fooJson, "name");
  printf("%s\n", json_string_value(namePropertyValue));
  json_decref(fooJson);
  // int renderImageScriptFileDescriptor = open(argv[1], O_RDONLY);
  // struct stat renderImageScriptFileStat;
  // fstat(renderImageScriptFileDescriptor, &renderImageScriptFileStat);
  // String renderImageScriptText = (String)mmap(NULL, renderImageScriptFileStat.st_size, PROT_READ, MAP_PRIVATE, renderImageScriptFileDescriptor, 0);
  // TCCState* tccState = tcc_new();
  // tcc_add_include_path(tccState, ".");
  // // tcc_add_library(TCCState *s, const char *libraryname)
  // tcc_set_output_type(tccState, TCC_OUTPUT_MEMORY);
  // tcc_compile_string(tccState, renderImageScriptText);
  // tcc_relocate(tccState);
  // void (*setupImageRender)(TCCState* tccState) = tcc_get_symbol(tccState, "setupImageRender");
  // setupImageRender(tccState);
  // void (*renderImagePixels)(Rgb8bitPngPixels* pngPixels) = tcc_get_symbol(tccState, "renderImagePixels");
  // U32 pixelsWidth = 129;
  // U32 pixelsHeight = 129;
  // U64 pixelsSize =
  //   sizeofRgb8bitPngPixels(pixelsWidth, pixelsHeight);
  // U64 maxEncodingSize =
  //   maxsizeofRgb8bitPngEncoding(pixelsWidth, pixelsHeight);
  // U64 poolSize =
  //   pixelsSize + maxEncodingSize;
  // HeapAllocation pngPool =
  //   (HeapAllocation)malloc(poolSize);
  // Rgb8bitPngPixels* pngPixels =
  //   (Rgb8bitPngPixels*)pngPool;
  // HeapAllocation pngEncoding =
  //   pngPool + pixelsSize;
  // initRgb8bitPngPixels(
  //   pngPixels,
  //   pixelsWidth,
  //   pixelsHeight);
  // initRgb8bitPngEncoding(
  //   pngEncoding,
  //   pngPixels);
  // renderImagePixels(pngPixels);
  // encodeRgb8bitPngPixels(
  //   pngEncoding,
  //   pngPixels);
  // FILE* pngFile_ptr =
  //   fopen(
  //     "foo.png",
  //     "wb");
  // fwrite(
  //   pngEncoding,
  //   1,
  //   getRgb8bitPngEncodingSize(pngEncoding),
  //   pngFile_ptr);
  // fclose(pngFile_ptr);
  // free(pngPool);
  return 0;
}
