#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "shell.h"

void execute(char *const args[])
{
  int i;
  int stat_loc;
  pid_t c_pid;

  printf("*** Entered:");
  for (i = 0; args[i] != NULL; i++)
    printf(" %s", args[i]);
  printf(" (%d words)\n", i);

  // example code here...
  // char *argv[] = {"ls", "-l", NULL};
  // execvp(argv[0], argv); -> executes 'ls -l'

  c_pid = fork();
  if (c_pid < 0)
  {
    /*FAILED FORK PROCESS*/

    perror("Fork failed");
    exit(1);
  }
  else if (c_pid == 0)
  {
    /*CHILD PROCESS*/

    // Failed execvp() function call
    if (execvp(args[0], args) < 0)
    {
      perror(args[0]);
      exit(1);
    }
    else
    {
      // Successfull execvp() function call
      execvp(args[0], args);
      printf("a;lsdkjfha;lskdjnfa;sdkjfna");
      exit(0);
    }
  }
  else
  {
    /*PARENT PROCESS*/
    pid_t wpid = waitpid(c_pid, &stat_loc, 0);
    if (!WIFEXITED(stat_loc))
    {
      printf("*** Command exited successfully with exit status %d\n", WIFEXITED(stat_loc));
    }
    else
    {
      printf("Command exited with %d", i);
      printf("Child: %d", wpid);
    }
  }
}
