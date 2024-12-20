FROM mcr.microsoft.com/devcontainers/base:ubuntu
USER vscode
ENV PROJECT_DIRECTORY_PATH=/workspaces/mechanism-cc
ENV OUTPUT_DIRECTORY_PATH=${PROJECT_DIRECTORY_PATH}/out
ENV OUTPUT_EXECUTABLE_PATH=${OUTPUT_DIRECTORY_PATH}/mechanism_cc
ENV DEPENDENCIES_DIRECTORY_PATH=${PROJECT_DIRECTORY_PATH}/dependencies
ENV SOURCE_DIRECTORY_PATH=${PROJECT_DIRECTORY_PATH}/source
ENV MAIN_SOURCE_FILE_PATH=${SOURCE_DIRECTORY_PATH}/main.c
COPY ./scripts/installBuildTools.sh /tmp
RUN bash ./tmp/installBuildTools.sh
RUN sudo rm /tmp/installBuildTools.sh