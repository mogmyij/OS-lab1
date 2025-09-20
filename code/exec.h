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
