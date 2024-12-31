__MAYBE_INFER_RUN_INVOCATION=$1
__CLANG_OPTIONS_ARGUMENTS=$2

if [ ! -d $OUTPUT_DIRECTORY_PATH ]; then
    mkdir -p $OUTPUT_DIRECTORY_PATH
fi
if [ ! -d $OUTPUT_INCLUDE_DIRECTORY ]; then
    mkdir $OUTPUT_INCLUDE_DIRECTORY
fi
$__MAYBE_INFER_RUN_INVOCATION \
    clang $__CLANG_OPTIONS_ARGUMENTS \
        -o $OUTPUT_BINARY_PATH \
        $(find $SOURCE_DIRECTORY_PATH -name "*.c") \
        /usr/local/lib/libz.a \
        /usr/local/lib/libtcc.a \
        /usr/local/lib/libjansson.a
$__MAYBE_INFER_RUN_INVOCATION \
    clang $__CLANG_OPTIONS_ARGUMENTS \
        -shared -fPIC \
        -o $OUTPUT_LIBRARY_PATH \
        ${SOURCE_DIRECTORY_PATH}/general.c ${SOURCE_DIRECTORY_PATH}/PngPixels.c
sudo cp \
    ${SOURCE_DIRECTORY_PATH}/plain-train.h ${SOURCE_DIRECTORY_PATH}/general.h ${SOURCE_DIRECTORY_PATH}/PngPixels.h \
    $OUTPUT_INCLUDE_DIRECTORY_PATH