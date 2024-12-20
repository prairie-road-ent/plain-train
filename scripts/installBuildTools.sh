__LLVM_VERSION=18.1.8
__INFER_VERSION=1.1.0
__BUILD_TOOLS_OUTPUT_DIRECTORY_PATH=/usr/lib

sudo apt-get update
sudo curl --remote-name --location https://github.com/llvm/llvm-project/releases/download/llvmorg-${__LLVM_VERSION}/clang+llvm-${__LLVM_VERSION}-x86_64-linux-gnu-ubuntu-18.04.tar.xz \
    && sudo tar --directory $__BUILD_TOOLS_OUTPUT_DIRECTORY_PATH --extract --verbose --file ./clang+llvm-${__LLVM_VERSION}-x86_64-linux-gnu-ubuntu-18.04.tar.xz \
    && sudo rm ./clang+llvm-${__LLVM_VERSION}-x86_64-linux-gnu-ubuntu-18.04.tar.xz \
    && sudo ln -s ${__BUILD_TOOLS_OUTPUT_DIRECTORY_PATH}/clang+llvm-${__LLVM_VERSION}-x86_64-linux-gnu-ubuntu-18.04/bin/* /usr/bin \
    && sudo apt-get install -y libncurses5
sudo curl --remote-name --location https://github.com/facebook/infer/releases/download/v${__INFER_VERSION}/infer-linux64-v${__INFER_VERSION}.tar.xz \
    && sudo tar --directory $__BUILD_TOOLS_OUTPUT_DIRECTORY_PATH --extract --verbose --file ./infer-linux64-v${__INFER_VERSION}.tar.xz \
    && sudo rm ./infer-linux64-v${__INFER_VERSION}.tar.xz \
    && sudo ln -s ${__BUILD_TOOLS_OUTPUT_DIRECTORY_PATH}/infer-linux64-v${__INFER_VERSION}/bin/infer /usr/bin/infer \
    && export PATH=/infer/bin:${PATH}