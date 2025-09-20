/*
 * Handles execution of commands
 */
#include <assert.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

#include "exec.h"
#include "parse.h"

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
    pid_t pid = forkAndExec(programList, -1, -1);

    if (pid == -1){

    } else {
      waitpid(pid, NULL, 0);
      j.pid = pid;
      j.groupPid = pid;
      j.status = 0;
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
    execvp(program->pgmlist[0], program->pgmlist);
    perror("execvp failed"); // will only run this when execvp fails
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
