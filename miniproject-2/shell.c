#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "shell.h"

void execute(char *const args[])
{
  // variable to track the number of arguments passes into this function
  int i;
  // variable to track the status of child process
  int stat_loc;
  // variable to track the child's PID
  pid_t c_pid;

  // counts and prints the args passes into the function
  printf("*** Entered:");
  for (i = 0; args[i] != NULL; i++)
    printf(" %s", args[i]);
  printf(" (%d words)\n", i);

  // example code here for how to use execvp() ...
  // char *argv[] = {"ls", "-l", NULL};
  // execvp(argv[0], argv); -> executes 'ls -l'

  //create for for child process
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
    // execute the execvp function by the number of words passed into this function.
    execvp(args[0], args);
    // the rest of this else if block runs if the arguments passed into execvp are invalid and the system call fails
    printf("*** Command not found: %s\n", args[0]);
    // exiting the child process in an 'abnormal' way because the command(s) are invalid 
    exit(1);
  }
  else
  {
    /*PARENT PROCESS*/
    // reaping the child by calling wait()
    wait(&stat_loc);
    // should always be true but is defined so that we can use WEXITSTATUS in line 54
    if (WIFEXITED(stat_loc))
    {
      // use WEXITSTATUS allows us to check how the child process exited and gives us a flag to see if it was a normal exiting or not
      if (!WEXITSTATUS(stat_loc))
      {
        // successful exiting and reaping of the child process!!!
        printf("*** Command exited successfully\n");
        /* using the print statements in the next 2 lines for testing purposes*/
        // printf("*** WIFEXITED: %d\n", WIFEXITED(stat_loc));
        // printf("*** WEXITSTATUS: %d\n", WEXITSTATUS(stat_loc));
      }
      else
      {
        printf("*** Command exited with %d\n", i);
      }
    }
  }
}
