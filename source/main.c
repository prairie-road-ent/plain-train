#include "PlainTrain.h"
#include "PngEncoding.h"
#include "PngPixels.h"
#include "general.h"
#include <fcntl.h>
#include <general.h>
#include <jansson.h>
#include <limits.h>
#include <signal.h>
#include <string.h>
#include <sys/inotify.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <unistd.h>

typedef struct
{
  U32 frameIndex;
  pid_t frameProcessId;
  Rgb8bitPngPixels* framePixels;
  U8* frameEncoding;
} FrameRendererProcess;

typedef struct
{
  pid_t graphicProcessId;
  pid_t graphicProcessGroupId;
  U32 graphicFrameRendererCount;
  FrameRendererProcess* graphicFrameRenderers;
} GraphicRendererProcess;

#define INOTIFY_EVENT_SIZE (sizeof(struct inotify_event))
#define INOTIFY_EVENT_BUFFER_EVENT_CAPACITY 4
#define INOTIFY_EVENT_BUFFER_SIZE (INOTIFY_EVENT_BUFFER_EVENT_CAPACITY * INOTIFY_EVENT_SIZE)

void killGraphicFrameRenderers()
{
  printf("todo\n");
}

int main(int argc, char* argv[])
{
    signal(SIGINT, killGraphicFrameRenderers);
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
  U64 pixelsSize =
    sizeofRgb8bitPngPixels(
      projectConfig->graphicPixelsWidth,
      projectConfig->graphicPixelsHeight);
  U64 maxEncodingSize =
    maxsizeofRgb8bitPngEncoding(
      projectConfig->graphicPixelsWidth,
      projectConfig->graphicPixelsHeight);
  U32 systemCoreCount =
    sysconf(_SC_NPROCESSORS_ONLN);
  U32 frameRendererCount =
    systemCoreCount;
  U64 pixelsPoolSize =
    systemCoreCount * pixelsSize;
  U64 encodingPoolSize =
    systemCoreCount * maxEncodingSize;
  U64 rendererPoolSize =
    sizeof(GraphicRendererProcess) + frameRendererCount * sizeof(FrameRendererProcess);
  U64 pngPoolSize =
    pixelsPoolSize + encodingPoolSize + rendererPoolSize;
  int poolSharedMemoryKey = 1234;
  int poolSharedMemoryId =
    shmget(
      poolSharedMemoryKey,
      pngPoolSize,
      0666 | IPC_CREAT);
  HeapAllocation pngPool =
    shmat(
      poolSharedMemoryId,
      NULL,
      0);
  // (HeapAllocation)malloc(pngPoolSize);
  HeapAllocation pixelsPool =
    pngPool;
  HeapAllocation encodingPool =
    pngPool + pixelsPoolSize;
  GraphicRendererProcess* graphicRendererProcess =
    (GraphicRendererProcess*)(encodingPool + encodingPoolSize);
  graphicRendererProcess->graphicProcessId =
    -1;
  graphicRendererProcess->graphicProcessGroupId =
    -1;
  graphicRendererProcess->graphicFrameRendererCount =
    frameRendererCount;
  graphicRendererProcess->graphicFrameRenderers =
    (FrameRendererProcess*)((U8*)graphicRendererProcess + sizeof(GraphicRendererProcess));
  for (U16 rendererIndex = 0; rendererIndex < graphicRendererProcess->graphicFrameRendererCount; rendererIndex++)
  {
    FrameRendererProcess* currentFrameRenderer =
      graphicRendererProcess->graphicFrameRenderers + rendererIndex;
    currentFrameRenderer->framePixels =
      (Rgb8bitPngPixels*)(pixelsPool + (pixelsSize * rendererIndex));
    currentFrameRenderer->frameEncoding =
      (U8*)(encodingPool + (maxEncodingSize * rendererIndex));
    initRgb8bitPngPixels(
      currentFrameRenderer->framePixels,
      projectConfig->graphicPixelsWidth,
      projectConfig->graphicPixelsHeight);
  }
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
  int inotifyFlags =
    fcntl(
      inotifyDescriptor,
      F_GETFL,
      0);
  fcntl(
    inotifyDescriptor,
    F_SETFL,
    inotifyFlags | O_NONBLOCK);
  inotify_add_watch(
    inotifyDescriptor,
    renderGraphicPixelsFileAbsolutePath,
    IN_MODIFY);
  U8 inotifyEventBuffer[INOTIFY_EVENT_BUFFER_SIZE];
  pid_t forkProcessIdResult = -1;
  while (true__Bool__STATIC_VALUE)
  {
    if (forkProcessIdResult > 0 && graphicRendererProcess->graphicProcessId > 0 && graphicRendererProcess->graphicProcessId != graphicRendererProcess->graphicProcessGroupId)
    {
      continue;
    }
    else if (forkProcessIdResult > 0 && graphicRendererProcess->graphicProcessId == -1)
    {
      continue;
    }
    // dont really care how many bytes were read or
    // processing latest vs oldest. just want signal
    // that graphic can be updated. a call to read will block until
    // event processed, and there is only one kind of event being
    // monitored for (modification of renderGraphicPixels.c)
    // NOTE: when running from codespaces, events seem to be double emitted
    // which isnt much of a problem when rendering a single image
    // but when we render a bunch of frames for a video
    // that will have to be handled more elegantly by
    // double reading or something
    int inotifyEventBytesRead =
      read(
        inotifyDescriptor,
        inotifyEventBuffer,
        INOTIFY_EVENT_BUFFER_SIZE);
    printf("%d\n", graphicRendererProcess->graphicProcessId);
    if (inotifyEventBytesRead > 0 && graphicRendererProcess->graphicProcessId == -1)
    {
      printf("initial fork\n");
      forkProcessIdResult =
        fork();
    }
    else if (inotifyEventBytesRead > 0 && graphicRendererProcess->graphicProcessId > 0 && graphicRendererProcess->graphicProcessId == graphicRendererProcess->graphicProcessGroupId)
    {
      printf("secondary fork\n");
      kill(
        -graphicRendererProcess->graphicProcessGroupId,
        SIGKILL);
      forkProcessIdResult =
        fork();
    }

    if (forkProcessIdResult == 0)
    {
      break;
    }
    usleep(1000000);
  }
  if (forkProcessIdResult == 0)
  {
    graphicRendererProcess->graphicProcessId =
      getpid();
    setpgid(
      graphicRendererProcess->graphicProcessId,
      graphicRendererProcess->graphicProcessId);
    graphicRendererProcess->graphicProcessGroupId =
      graphicRendererProcess->graphicProcessId;
    while (1)
    {
      printf("%d\n", graphicRendererProcess->graphicProcessId);
      usleep(1000000);
    }
  }
  // not sure if parent process really needs to cleanup
  // free(pngPool);
  // close(inotifyDescriptor);
  return 0;
}
