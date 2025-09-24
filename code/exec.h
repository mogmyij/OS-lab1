#pragma once

#include <unistd.h>
#include "parse.h"

typedef struct j
{
  pid_t pid;
  pid_t groupPid;
  int status;
  
} Job;

extern int commandExecutor(Command);
extern Job execForeground(Command cmd);
extern Job execBackground(Command cmd);
extern pid_t forkAndExec(Pgm *program, int readFd, int writeFd);
extern Job connectPipe(Command cmd);
extern void execBuiltin(Command cmd);
extern int isBuiltin(Command cmd);

void set_current_foreground_pgid(pid_t pgid);
