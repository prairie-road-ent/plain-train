#include "PlainTrain.h"
#include "general.h"
#include <jansson.h>
#include <limits.h>
#include <string.h>
#include <sys/stat.h>

int main(int argc, char* argv[])
{
  String projectDirectoryAbsolutePathArgument = argv[1];
  StringBuffer projectDirectoryAbsolutePath[PATH_MAX];
  removePathTrailingDelimiter(
    projectDirectoryAbsolutePath,
    projectDirectoryAbsolutePathArgument);
  StringBuffer projectConfigFileAbsolutePath[PATH_MAX];
  StringBuffer renderGraphicPixelsFileAbsolutePath[PATH_MAX];
  StringBuffer projectOutputDirectoryAbsolutePath[PATH_MAX];
  resolveDirectoryChildPath(
    projectConfigFileAbsolutePath,
    projectDirectoryAbsolutePath,
    projectConfigFileName__PlainTrain__VALUE);
  resolveDirectoryChildPath(
    projectOutputDirectoryAbsolutePath,
    projectDirectoryAbsolutePath,
    projectOutputDirectoryName__PlainTrain__VALUE);
  mkdir(
    projectOutputDirectoryAbsolutePath,
    0755);
  resolveDirectoryChildPath(
    renderGraphicPixelsFileAbsolutePath,
    projectDirectoryAbsolutePath,
    renderGraphicPixelsFileName__PlainTrain__VALUE);
  json_t* projectConfigJson =
    json_load_file(
      projectConfigFileAbsolutePath,
      0,
      NULL);
  U64 projectConfigSize =
    sizeofPlainTrainConfig(
      projectConfigJson);
  PlainTrainConfig* projectConfig =
    (PlainTrainConfig*)malloc(projectConfigSize);
  initPlainTrainConfig(
    projectConfig,
    projectConfigJson);
  json_decref(projectConfigJson);
  StringBuffer graphicOutputFilename[strlen(projectConfig->graphicName) + strlen(".png") + 1];
  sprintf(
    graphicOutputFilename,
    "%s%s",
    projectConfig->graphicName,
    ".png");
  StringBuffer graphicOutputAbsolutePath[PATH_MAX];
  resolveDirectoryChildPath(
    graphicOutputAbsolutePath,
    projectOutputDirectoryAbsolutePath,
    graphicOutputFilename);
  updateGraphicImage(
    renderGraphicPixelsFileAbsolutePath,
    projectConfig,
    graphicOutputAbsolutePath);
  return 0;
}
