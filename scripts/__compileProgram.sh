__MAYBE_INFER_RUN_INVOCATION=$1
__CLANG_OPTIONS_ARGUMENTS=$2

if [ ! -d $OUTPUT_DIRECTORY_PATH ]; then
    mkdir -p $OUTPUT_DIRECTORY_PATH
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
clang -E \
    -o $OUTPUT_INCLUDE_PATH \
    ${SOURCE_DIRECTORY_PATH}/plain-train.h