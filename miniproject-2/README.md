Mini-project 2
============

**Due: Sep. 25, 2020 by 11:59 PM US Central Time**.

In this mini-project you are building a basic shell interpreter. It should read a command to be executed along with the command line arguments. To finish this assignment you will need to understand the usage of following systems calls:

- fork
- exec
- wait
- exit

Reading the input is already written for you in `main.c`, you need to complete the `execute` function in `shell.c` to actually execute the command entered. You should create the `build` directory and compile there with `cmake` as usual. A correct execution of the shell program will look something like this:

```
zzk@isis:~/courses/CS4352/miniprojects/miniproject-2/build$ ./shell 
*** Welcome to the CS4352 Shell
CS4352$ ls -l
*** Entered: ls -l (2 words)
total 48
-rw-rw-r-- 1 zzk zzk 11590 szept 11 22:19 CMakeCache.txt
drwxrwxr-x 5 zzk zzk  4096 szept 11 22:24 CMakeFiles
-rw-rw-r-- 1 zzk zzk  1383 szept 11 22:19 cmake_install.cmake
-rw-rw-r-- 1 zzk zzk   903 szept 11 22:19 CTestTestfile.cmake
-rw-rw-r-- 1 zzk zzk  5622 szept 11 22:19 Makefile
-rwxrwxr-x 1 zzk zzk 13096 szept 11 22:24 shell
*** Command exited sucessfully
CS4352$ something
*** Entered: something (1 words)
*** Command not found: something
*** Command exited with 1
CS4352$ ls something
*** Entered: ls something (2 words)
ls: cannot access 'something': No such file or directory
*** Command exited with 2
CS4352$ exit
*** Closing the CS4352 Shell
```

## Tasks

* Finish the implementation of the `execute` function in `shell.c`. Do not modify, change or free the `args` array of input words.
* Select the appropriate `exec` function from the possibilities (see `man exec`). Use the manuals for the required system calls to find the appropriate include files. You might need `#include <sys/types.h>` to access the definition of `pid_t`.
* Make sure you print "Fork failed" if the fork function failed.
* Make sure you print "Command not found" if the exec function failed.
* Make sure you print "Command exited successfully" if the command terminated with a zero status code.
* Make sure you print "Command exited with" if the command terminated with a non-zero status code.

## Evaluation

Your assignment will be graded according to the following criteria:

- **25 points** for the correct usage of and error handling for the `fork` system call.
- **25 points** for the correct usage of and error handling for the `exec` system call.
- **25 points** for the correct usage of and error handling for the `wait` system call.
- **25 points** for the correct and appropriate usage of the `exit` system call.

