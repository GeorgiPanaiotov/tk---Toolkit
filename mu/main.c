#include <locale.h>
#include "collector.h"

int mu_main(int argc, char *argv[])
{
  if (argc < 2 || strcmp(argv[1], "--help") == 0 || strcmp(argv[1], "-h") == 0)
  {
    printf("Usage: %s <target_directory | target_file>\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  setlocale(LC_NUMERIC, "en_US.UTF-8");

  ProjectStats project = mu_init_project();
  mu_walk(&project, argv[1], O_RDONLY, S_IRUSR | S_IRGRP | S_IROTH);

  char file_size_buf[32];
  char dir_size_buf[32];
  char comb_size_buf[32];

  char file_foot_buf[32];
  char dir_foot_buf[32];
  char comb_foot_buf[32];

  format_bytes(file_size_buf, sizeof(file_size_buf), project.total_stats.total_file_size);
  format_bytes(file_foot_buf, sizeof(file_foot_buf), project.total_stats.total_file_footprint_size);

  format_bytes(dir_size_buf, sizeof(dir_size_buf), project.total_stats.total_dir_size);
  format_bytes(dir_foot_buf, sizeof(dir_foot_buf), project.total_stats.total_dir_footprint_size);

  long long combined_size = project.total_stats.total_dir_size + project.total_stats.total_file_size;
  long long combined_footprint_size = project.total_stats.total_dir_footprint_size + project.total_stats.total_file_footprint_size;

  format_bytes(comb_size_buf, sizeof(comb_size_buf), combined_size);
  format_bytes(comb_foot_buf, sizeof(comb_foot_buf), combined_footprint_size);

  printf("\e[1m");
  printf("%-30s %20s %20s\n", "Metric", "Totals", "Footprint Totals");
  printf("%-30s %20s %20s\n", "------", "------", "------");
  printf("\e[0m");

  printf("%-30s %20s %20s\n", "Total file size", file_size_buf, file_foot_buf);
  printf("%-30s %20s %20s\n", "Total directory size", dir_size_buf, dir_foot_buf);
  printf("%-30s %20s %20s\n\n", "Total combined size", comb_size_buf, comb_foot_buf);
  
  printf("%-30s %'20ld\n\n", "Total files checked", project.file_count);

  for (size_t i = 0; i < project.file_count; i++)
  {
    free(project.files[i].path);
  }

  free(project.files);
  return 0;
}
