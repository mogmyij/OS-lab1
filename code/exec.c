/*
 * Handles execution of commands
 */
#include <stdio.h>
#include <unistd.h>

#include "exec.h"
#include "parse.h"

int commandExecutor(Command cmd){
  Pgm *commandList = cmd.pgm;

  //determine which helper function to call

  

  return 1;
}

/*
 * execute and wait for program(s) to terminate
 */
Job execForeground(Command cmd){

}

/*
 * execute and pass Job to jobList to handle and terminate without leaving zombies
 */
Job execBackground(Command cmd){

}

/*
 * Given the program it will fork and execute it and return the PID 
 *
 * program: 
 * contains the program name and args
 *
 * readFd:
 * contains the file descriptors to redirect stdin to
 * use NULL when there is no need to redirect stdin/stdout
 *
 * writeFd:
 * contains the file descriptors to redirect stdout to
 * use NULL when there is no need to redirect stdin/stdout
 */
pid_t forkAndExec(Pgm program, int readFd, int writeFd) {

}

/*
 * connects programs together into a pipe and groups their pid into a process group
 */
Job connectPipe(Command cmd){

}

//returns void because built in commands do not fork and excec hence no jobs created
void execBuiltin(Command cmd){

}
