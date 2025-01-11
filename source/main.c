#include "PlainTrain.h"
#include "general.h"
#include <general.h>
#include <jansson.h>
#include <limits.h>
#include <string.h>
#include <sys/inotify.h>
#include <sys/stat.h>
#include <unistd.h>
#include <signal.h>

#define INOTIFY_EVENT_SIZE (sizeof(struct inotify_event))
#define INOTIFY_EVENT_BUFFER_EVENT_CAPACITY 4
#define INOTIFY_EVENT_BUFFER_SIZE (INOTIFY_EVENT_BUFFER_EVENT_CAPACITY * INOTIFY_EVENT_SIZE)

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
  int inotifyDescriptor =
    inotify_init();
  inotify_add_watch(
    inotifyDescriptor,
    renderGraphicPixelsFileAbsolutePath,
    IN_MODIFY);
  U8 inotifyEventBuffer[INOTIFY_EVENT_BUFFER_SIZE];
  Bool originalProcessIsMonitoring =
    true__Bool__STATIC_VALUE;
  pid_t childProcessId;
  while (originalProcessIsMonitoring)
  {
    // dont really care how many bytes were read or
    // processing latest vs oldest. just want signal
    // that graphic can be updated. a call to read will block until
    // event processed, and there is only one kind of event being
    // monitored for (modification of renderGraphicPixels.c)
    read(
      inotifyDescriptor,
      inotifyEventBuffer,
      INOTIFY_EVENT_BUFFER_SIZE);
    printf("UPDATED: renderGraphicPixels.c\n");
    if (childProcessId > 0) {
      kill(
        childProcessId, 
        SIGKILL);
    }  
    childProcessId =
      fork();
    if (childProcessId == 0)
    {
      break;
    }
  }
  updateGraphicImage(
    renderGraphicPixelsFileAbsolutePath,
    projectConfig,
    graphicOutputAbsolutePath);
  return 0;
}
