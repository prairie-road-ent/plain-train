__MAYBE_INFER_RUN_INVOCATION=$1
__CLANG_OPTIONS_ARGUMENTS=$2

if [ ! -d $OUTPUT_DIRECTORY_PATH ]; then
    mkdir -p $OUTPUT_DIRECTORY_PATH
fi
$__MAYBE_INFER_RUN_INVOCATION \
    clang $__CLANG_OPTIONS_ARGUMENTS \
        -o $OUTPUT_EXECUTABLE_PATH \
        -lz -lm \
        $(find $SOURCE_DIRECTORY_PATH -name "*.c") \
        /usr/local/lib/libtcc.a