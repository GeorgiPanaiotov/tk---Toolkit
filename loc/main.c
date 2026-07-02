#include <locale.h>
#include "walker.h"

int loc_main(int argc, char *argv[])
{
  if (argc < 2)
  {
    printf("Insufficient arguments!\n");
    exit(EXIT_FAILURE);
  }

  setlocale(LC_NUMERIC, "en_US.UTF-8");

  Project project = loc_init_project();
  loc_walk(&project, argv[1], O_RDONLY, S_IRUSR | S_IRGRP | S_IROTH);

  size_t i = 0;
  while (i < project.file_count)
  {
    loc_update_metrics(&project, &project.files[i].lines);
    i++;
  }
  get_code_total(&project);
  calculate_language_stats(&project);

  printf("Total files checked: %'ld\n", project.file_count);
  printf("Total files skipped: %'ld\n\n", project.files_skipped);

  printf("Total lines of code: %'lld\n", project.total_stats.total);
  printf("Blank lines: %'ld\n", project.total_stats.blank_count);
  printf("Code lines: %'ld\n", project.total_stats.code_count);
  printf("Comment lines: %'ld\n\n", project.total_stats.comment_count);

  printf("\n%-20s %15s\n", "Language", "Lines of Code");
  printf("------------------------------------\n");

  for (size_t i = 0; i < project.language_count; i++)
  {
    if (project.language_stats[i].stats.total == 0)
    {
      continue;
    }

    printf("%-20s %'15lld\n", project.language_stats[i].language, project.language_stats[i].stats.total);
  }
  printf("------------------------------------\n");

  for (size_t i = 0; i < project.file_count; i++)
  {
    free(project.files[i].path);
  }

  free(project.files);
  exit(EXIT_SUCCESS);
}