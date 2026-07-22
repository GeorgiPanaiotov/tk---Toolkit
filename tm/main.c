#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <sys/resource.h>

static const char *suffixes[] = {"B", "KB", "MB", "GB", "TB"};

int tm_main(int argc, char *argv[])
{
  if (argc < 2 || strcmp(argv[1], "--help") == 0 || strcmp(argv[1], "-h") == 0)
  {
    printf("Usage: %s <program_name> [args...]\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  char *cmd_app = argv[1];
  char **new_argv = argv + 1;

  struct timespec start, end;
  struct rusage p_rusage;

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

    int rusage_status = getrusage(RUSAGE_CHILDREN, &p_rusage);
    if (rusage_status == -1)
    {
      printf("There was an error getting the resources used!\n");
    }

    char ram_mem_buf[32];
    size_t buf_size = sizeof(ram_mem_buf) / sizeof(ram_mem_buf[0]);

    int i = 0;

#ifdef __linux__
    double d_bytes = (double)p_rusage.ru_maxrss * 1024.0f;
#else
    double d_bytes = (double)p_rusage.ru_maxrss;
#endif

    while (d_bytes >= 1024 && i < 5)
    {
      d_bytes /= 1024;
      i++;
    }

    if (i == 0)
    {
      snprintf(ram_mem_buf, buf_size, "%'ld %s", p_rusage.ru_maxrss, suffixes[i]);
    }
    else
    {
      snprintf(ram_mem_buf, buf_size, "%'.3f %s", d_bytes, suffixes[i]);
    }

    double elapsed = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1000000000.0;

    printf("\n-----------------------------------\n");
    printf("\e[1m");
    printf("RAM used: %s\n", ram_mem_buf);
    printf("Execution time: %.6f seconds\n", elapsed);
    printf("\e[0m");
    printf("-----------------------------------\n");
  }
  return 0;
}
