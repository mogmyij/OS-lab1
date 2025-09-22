/*
 * Handles execution of commands
 */
#include <assert.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#include <termios.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/stat.h>

#include "exec.h"
#include "parse.h"

void set_current_foreground_pgid(pid_t pgid);

int commandExecutor(Command cmd){

  //determine which helper function to call 

  if (isBuiltin(cmd)) {//is a buiilt-in command
  
  } else if (cmd.background){//is a background command

  } else {

    Job job = execForeground(cmd);//is not a background commandExecutor

    if (job.status != -1){ //check if executed successfuly
      return 1;
    } else {
      return -1;
    }
  }
  

}

/*
 * execute and wait for program(s) to terminate
 */
Job execForeground(Command cmd){
  // loop through each program in the command and run them 
  Pgm *programList = cmd.pgm;
  Job j;

  //since next is NULL it means that there is only 1 program hence no pipe
  if (programList->next == NULL){ 
    // Open redirection files if specified and prepare FDs for the child
    int inFd = -1;
    int outFd = -1;

    if (cmd.rstdin != NULL){
      inFd = open(cmd.rstdin, O_RDONLY);
      if (inFd == -1){
        perror("open rstdin failed");
        j.pid = -1;
        j.groupPid = -1;
        j.status = -1;
        return j;
      }
    }

    if (cmd.rstdout != NULL){
      outFd = open(cmd.rstdout, O_WRONLY | O_CREAT | O_TRUNC, 0666);
      if (outFd == -1){
        if (inFd != -1){
          (void)close(inFd);
        }
        perror("open rstdout failed");
        j.pid = -1;
        j.groupPid = -1;
        j.status = -1;
        return j;
      }
    }

    pid_t pid = forkAndExec(programList, inFd, outFd);
    // Parent closes its copy of any redirection FDs to avoid descriptor leaks
    if (inFd != -1){
      (void)close(inFd);
    }
    if (outFd != -1){
      (void)close(outFd);
    }

    if (pid == -1){
      j.pid = -1;
      j.groupPid = -1;
      j.status = -1;
    } else {
      //Put child into its own process group
      (void)setpgid(pid, pid);
      (void)tcsetpgrp(STDIN_FILENO, pid);
      set_current_foreground_pgid(pid);

      int status = 0;
      for (;;) {
        if (waitpid(pid, &status, 0) == -1) {
          if (errno == EINTR) {
            continue;
          }
          break;
        }
        break;
      }

      // Restore terminal to the shell
      (void)tcsetpgrp(STDIN_FILENO, getpgrp());
      set_current_foreground_pgid(-1);
      j.pid = pid;
      j.groupPid = pid;
      j.status = status;
    }
    return j;
  } else {
    j = connectPipe(cmd);
    return j;
  }
}

/*
 * execute and pass Job to jobList to handle and terminate without leaving zombies
 */
Job execBackground(Command cmd){

}

/*
 * Given the program it will fork and execute it and return the PID 
 *
 * Parameters:
 * program: contains the program name and args
 * readFd: contains the file descriptors to redirect stdin to
 *         use -1 when there is no need to redirect stdin/stdout
 * writeFd:contains the file descriptors to redirect stdout to
 *         use -1 when there is no need to redirect stdin/stdout
 *
 * Return value:
 * returns pid of the child and -1 if failed
 */
pid_t forkAndExec(Pgm *program, int readFd, int writeFd) {
  assert(program != NULL);

  pid_t pid;

  pid = fork();
  if (pid == -1) {
    perror("Fork failed");
    return -1;
  } else if (pid == 0) { //child
    // Child: create its own process group
    (void)setpgid(0, 0);
    // Default SIGINT handling so Ctrl-C terminates the child
    (void)signal(SIGINT, SIG_DFL);
    (void)signal(SIGTSTP, SIG_DFL);

    // Child: wire provided FDs to STDIN/STDOUT using dup2 when present
    if (readFd != -1){
      if (dup2(readFd, STDIN_FILENO) == -1){
        perror("dup2 stdin failed");
        _exit(126);
      }
      (void)close(readFd);
    }

    if (writeFd != -1){
      if (dup2(writeFd, STDOUT_FILENO) == -1){
        perror("dup2 stdout failed");
        _exit(126);
      }
      (void)close(writeFd);
    }

    execvp(program->pgmlist[0], program->pgmlist);
    perror("execvp failed"); // will only run this when execvp fails
    _exit(127);
  } else { //parent does not wait because it depends on what the caller wants to do
    return pid;
  }
}

/*
 * connects programs together into a pipe and groups their pid into a process group
 */
Job connectPipe(Command cmd){

}

//returns void because built in commands do not fork and excec hence no jobs created
void execBuiltin(Command cmd){

}

int isBuiltin(Command cmd){
  return 0;
}
