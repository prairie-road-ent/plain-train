#include "PngEncoding.h"
#include "PngPixels.h"
#include "general.h"
#include <zlib.h>

U64 calcMaxIdatCompressedPixelsSize(U32 pixelsWidth, U32 pixelsHeight)
{
  return compressBound(
    calcPixelsDataSize(pixelsWidth, pixelsHeight));
}

U64 maxsizeofRgb8bitPngEncoding(U32 pixelsWidth, U32 pixelsHeight)
{
  U64 maxIdatCompressedPixelsSize =
    calcMaxIdatCompressedPixelsSize(pixelsWidth, pixelsHeight);
  return Rgb8bitPngEncoding__SIZE(maxIdatCompressedPixelsSize);
}

PngSignature* atPngSignature(U8* pngEncoding)
{
  return (PngSignature*)(pngEncoding + pngSignature__Rgb8bitPngEncoding__VALUE_ADDRESS_OFFSET);
}

IhdrDataSize* atIhdrDataSize(U8* pngEncoding)
{
  return (IhdrDataSize*)(pngEncoding + ihdrDataSize__Rgb8bitPngEncoding__VALUE_ADDRESS_OFFSET);
}

IhdrSignature* atIhdrSignature(U8* pngEncoding)
{
  return (IhdrSignature*)(pngEncoding + ihdrSignature__Rgb8bitPngEncoding__VALUE_ADDRESS_OFFSET);
}

IhdrDataPngPixelWidth* atIhdrDataPngPixelWidth(U8* pngEncoding)
{
  return (IhdrDataPngPixelWidth*)(pngEncoding + ihdrDataPngPixelWidth__Rgb8bitPngEncoding__VALUE_ADDRESS_OFFSET);
}

IhdrDataPngPixelHeight* atIhdrDataPngPixelHeight(U8* pngEncoding)
{
  return (IhdrDataPngPixelHeight*)(pngEncoding + ihdrDataPngPixelHeight__Rgb8bitPngEncoding__VALUE_ADDRESS_OFFSET);
}

IhdrDataPngChannelBitDepth* atIhdrDataPngChannelBitDepth(U8* pngEncoding)
{
  return (IhdrDataPngChannelBitDepth*)(pngEncoding + ihdrDataPngChannelBitDepth__Rgb8bitPngEncoding__VALUE_ADDRESS_OFFSET);
}

IhdrDataPngChannelKind* atIhdrDataPngChannelKind(U8* pngEncoding)
{
  return (IhdrDataPngChannelKind*)(pngEncoding + ihdrDataPngChannelKind__Rgb8bitPngEncoding__VALUE_ADDRESS_OFFSET);
}

IhdrDataPngCompressionMethod* atIhdrDataPngCompressionMethod(U8* pngEncoding)
{
  return (IhdrDataPngCompressionMethod*)(pngEncoding + ihdrDataPngCompressionMethod__Rgb8bitPngEncoding__VALUE_ADDRESS_OFFSET);
}

IhdrDataPngFilterMethod* atIhdrDataPngFilterMethod(U8* pngEncoding)
{
  return (IhdrDataPngFilterMethod*)(pngEncoding + ihdrDataPngFilterMethod__Rgb8bitPngEncoding__VALUE_ADDRESS_OFFSET);
}

IhdrDataPngInterlaceMethod* atIhdrDataPngInterlaceMethod(U8* pngEncoding)
{
  return (IhdrDataPngInterlaceMethod*)(pngEncoding + ihdrDataPngInterlaceMethod__Rgb8bitPngEncoding__VALUE_ADDRESS_OFFSET);
}

IhdrSignatureDataCrc* atIhdrSignatureDataCrc(U8* pngEncoding)
{
  return (IhdrSignatureDataCrc*)(pngEncoding + ihdrSignatureDataCrc__Rgb8bitPngEncoding__VALUE_ADDRESS_OFFSET);
}

IdatCompressedPixelsSize* atIdatCompressedPixelsSize(U8* pngEncoding)
{
  return (IdatCompressedPixelsSize*)(pngEncoding + idatCompressedPixelsSize__Rgb8bitPngEncoding__VALUE_ADDRESS_OFFSET);
}

IdatSignature* atIdatSignature(U8* pngEncoding)
{
  return (IdatSignature*)(pngEncoding + idatSignature__Rgb8bitPngEncoding__VALUE_ADDRESS_OFFSET);
}

IdatCompressedPixels atIdatCompressedPixels(U8* pngEncoding)
{
  return (IdatCompressedPixels)(pngEncoding + idatCompressedPixels__Rgb8bitPngEncoding__VALUE_ADDRESS_OFFSET);
}

IdatSignatureCompressedPixelsCrc* atIdatSignatureCompressedPixelsCrc(U8* pngEncoding, IdatCompressedPixelsSize idatCompressedPixelsSize)
{
  return (IdatSignatureCompressedPixelsCrc*)(pngEncoding + idatSignatureCompressedPixelsCrc__Rgb8bitPngEncoding__VALUE_ADDRESS_OFFSET(idatCompressedPixelsSize));
}

IendDataSize* atIendDataSize(U8* pngEncoding, IdatCompressedPixelsSize idatCompressedPixelsSize)
{
  return (IendDataSize*)(pngEncoding + iendDataSize__Rgb8bitPngEncoding__VALUE_ADDRESS_OFFSET(idatCompressedPixelsSize));
}

IendSignature* atIendSignature(U8* pngEncoding, IdatCompressedPixelsSize idatCompressedPixelsSize)
{
  return (IendSignature*)(pngEncoding + iendSignature__Rgb8bitPngEncoding__VALUE_ADDRESS_OFFSET(idatCompressedPixelsSize));
}

IendSignatureCrc* atIendSignatureCrc(U8* pngEncoding, IdatCompressedPixelsSize idatCompressedPixelsSize)
{
  return (IendSignatureCrc*)(pngEncoding + iendSignatureCrc__Rgb8bitPngEncoding__VALUE_ADDRESS_OFFSET(idatCompressedPixelsSize));
}

void initRgb8bitPngEncoding(U8* pngEncoding, Rgb8bitPngPixels* pngPixels)
{
  *atIhdrDataPngChannelBitDepth(pngEncoding) =
    ihdrDataPngChannelBitDepth__Rgb8bitPngEncoding__VALUE;
  *atIhdrDataPngChannelKind(pngEncoding) =
    ihdrDataPngChannelKind__Rgb8bitPngEncoding__VALUE;
  *atIhdrDataPngCompressionMethod(pngEncoding) =
    ihdrDataPngCompressionMethod__Rgb8bitPngEncoding__VALUE;
  *atIhdrDataPngFilterMethod(pngEncoding) =
    ihdrDataPngFilterMethod__Rgb8bitPngEncoding__VALUE;
  *atIhdrDataPngInterlaceMethod(pngEncoding) =
    ihdrDataPngInterlaceMethod__Rgb8bitPngEncoding__VALUE;
  *atPngSignature(pngEncoding) =
    swapEndianU64(
      pngSignature__Rgb8bitPngEncoding__VALUE);
  *atIhdrDataSize(pngEncoding) =
    swapEndianU32(
      ihdrDataSize__Rgb8bitPngEncoding__VALUE);
  *atIhdrSignature(pngEncoding) =
    swapEndianU32(
      fourByteStringToU32(
        ihdrSignature__Rgb8bitPngEncoding__VALUE));
  *atIdatSignature(pngEncoding) =
    swapEndianU32(
      fourByteStringToU32(
        idatSignature__Rgb8bitPngEncoding__VALUE));
  *atIhdrDataPngPixelWidth(pngEncoding) =
    swapEndianU32(
      pngPixels->width);
  *atIhdrDataPngPixelHeight(pngEncoding) =
    swapEndianU32(
      pngPixels->height);
  *atIhdrSignatureDataCrc(pngEncoding) =
    swapEndianU32(
      crc32(
        0,
        (Bytef*)atIhdrSignature(pngEncoding),
        (U8*)atIhdrSignatureDataCrc(pngEncoding) - (U8*)atIhdrSignature(pngEncoding)));
}

void encodeRgb8bitPngPixels(U8* pngEncoding, Rgb8bitPngPixels* pngPixels)
{
  z_stream pixelStream;
  pixelStream.zalloc = Z_NULL;
  pixelStream.zfree = Z_NULL;
  pixelStream.opaque = Z_NULL;
  pixelStream.avail_in =
    (uInt)calcPixelsDataSize(
      pngPixels->width,
      pngPixels->height);
  pixelStream.next_in =
    (Bytef*)pngPixels->data_ptr;
  pixelStream.avail_out =
    calcMaxIdatCompressedPixelsSize(
      pngPixels->width,
      pngPixels->height);
  pixelStream.next_out =
    (Bytef*)atIdatCompressedPixels(pngEncoding);
  deflateInit(
    &pixelStream,
    Z_DEFAULT_COMPRESSION);
  deflate(
    &pixelStream,
    Z_FINISH);
  deflateEnd(
    &pixelStream);
  IdatCompressedPixelsSize idatCompressedPixelsSize =
    (U32)pixelStream.total_out;
  *atIdatCompressedPixelsSize(pngEncoding) =
    swapEndianU32(idatCompressedPixelsSize);
  *atIdatSignatureCompressedPixelsCrc(pngEncoding, idatCompressedPixelsSize) =
    swapEndianU32(
      crc32(
        0,
        (Bytef*)atIdatSignature(pngEncoding),
        idatSignature__Rgb8bitPngEncoding__VALUE_SIZE + idatCompressedPixelsSize));
  *atIendDataSize(pngEncoding, idatCompressedPixelsSize) =
    swapEndianU32(
      iendDataSize__Rgb8bitPngEncoding__VALUE);
  *atIendSignature(pngEncoding, idatCompressedPixelsSize) =
    swapEndianU32(
      fourByteStringToU32(
        iendSignature__Rgb8bitPngEncoding__VALUE));
  *atIendSignatureCrc(pngEncoding, idatCompressedPixelsSize) =
    swapEndianU32(
      crc32(
        0,
        (Bytef*)atIendSignature(pngEncoding, idatCompressedPixelsSize),
        iendSignature__Rgb8bitPngEncoding__VALUE_SIZE));
}

U64 getRgb8bitPngEncodingSize(U8* pngEncoding)
{
  return Rgb8bitPngEncoding__SIZE(
    swapEndianU32(
      *atIdatCompressedPixelsSize(pngEncoding)));
}
