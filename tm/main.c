#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/types.h>
#include <sys/wait.h>

int tm_main(int argc, char *argv[])
{
  if (argc < 3)
  {
    printf("Please provide a tool to measure!\n");
    exit(EXIT_FAILURE);
  }

  char *cmd_app = argv[1];
  char **new_argv = argv + 1;

  struct timespec start, end;

  pid_t child_id = fork();
  if (child_id == -1)
  {
    perror("fork");
    exit(EXIT_FAILURE);
  }

  int time_status = clock_gettime(CLOCK_MONOTONIC, &start);
  if (time_status == -1)
  {
    perror("clock_gettime");
    exit(EXIT_FAILURE);
  }

  if (child_id == 0)
  {
    execvp(cmd_app, new_argv);
    perror("execvp");
    exit(EXIT_FAILURE);
  }
  else
  {
    int status;
    waitpid(child_id, &status, 0);
    clock_gettime(CLOCK_MONOTONIC, &end);

    double elapsed = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1000000000.0;

    printf("\n-----------------------------------\n");
    printf("\e[1m");
    printf("Execution time: %.6f seconds\n", elapsed);
    printf("\e[0m");
    printf("-----------------------------------\n");
  }
  return 0;
}