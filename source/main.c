#include "PngEncoding.h"
#include "PngPixels.h"
#include <fcntl.h>
#include <libtcc.h>
#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>

int main(int argc, char* argv[])
{
  int renderImageScriptFileDescriptor = open(argv[1], O_RDONLY);
  struct stat renderImageScriptFileStat;
  fstat(renderImageScriptFileDescriptor, &renderImageScriptFileStat);
  String renderImageScriptText = (String)mmap(NULL, renderImageScriptFileStat.st_size, PROT_READ, MAP_PRIVATE, renderImageScriptFileDescriptor, 0);
  TCCState* tcc_state = tcc_new();
  tcc_add_include_path(tcc_state, ".");
  tcc_set_output_type(tcc_state, TCC_OUTPUT_MEMORY);
  tcc_compile_string(tcc_state, renderImageScriptText);
  tcc_add_file(tcc_state, "./PngEncoding.o");
  tcc_add_file(tcc_state, "./PngPixels.o");
  tcc_add_file(tcc_state, "./general.o");
  tcc_relocate(tcc_state);
  void (*renderImagePixels)(Rgb8bitPngPixels* pngPixels) = tcc_get_symbol(tcc_state, "renderImagePixels");
  U32 pixelsWidth = 129;
  U32 pixelsHeight = 129;
  U64 pixelsSize =
    sizeofRgb8bitPngPixels(pixelsWidth, pixelsHeight);
  U64 maxEncodingSize =
    maxsizeofRgb8bitPngEncoding(pixelsWidth, pixelsHeight);
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
    pixelsWidth,
    pixelsHeight);
  initRgb8bitPngEncoding(
    pngEncoding,
    pngPixels);
  renderImagePixels(pngPixels);
  encodeRgb8bitPngPixels(
    pngEncoding,
    pngPixels);
  FILE* pngFile_ptr =
    fopen(
      "foo.png",
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
