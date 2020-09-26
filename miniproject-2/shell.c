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
    execvp(args[0], args);
    printf("*** Command not found: %s\n", args[0]);

    exit(1);
  }
  else
  {
    /*PARENT PROCESS*/
    wait(&stat_loc);
    if (WIFEXITED(stat_loc))
    {
      if (!WEXITSTATUS(stat_loc))
      {
        // printf("*** WIFEXITED: %d\n", WIFEXITED(stat_loc));
        // printf("*** WEXITSTATUS: %d\n", WEXITSTATUS(stat_loc));
        printf("*** Command exited successfully\n");
      }
      else
      {
        printf("*** Command exited with %d\n", i);
      }
    }
  }
}
