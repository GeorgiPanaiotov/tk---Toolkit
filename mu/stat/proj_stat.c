#include "proj_stat.h"

static const char *suffixes[] = {"B", "KB", "MB", "GB", "TB", "PB"};

ProjectStats mu_init_project()
{
  ProjectStats proj;
  proj.file_count = 0;
  proj.total_stats = (Metrics){0, 0, 0, 0};
  proj.file_capacity = FILE_CAPACITY;
  proj.files = malloc(proj.file_capacity * sizeof(File));
  if (proj.files == NULL)
  {
    perror("init_project: malloc");
    exit(EXIT_FAILURE);
  }

  return proj;
}

void mu_update_metrics(ProjectStats *proj, off_t size, off_t footprint_size)
{
  proj->total_stats.total_file_size += size;
  proj->total_stats.total_file_footprint_size += footprint_size;
}

void format_bytes(char *buf, size_t buf_size, long long bytes)
{
  int i = 0;
  double d_bytes = (double)bytes;

  while (d_bytes >= 1024 && i < 5)
  {
    d_bytes /= 1024;
    i++;
  }

  if (i == 0)
  {
    snprintf(buf, buf_size, "%'lld %s", bytes, suffixes[i]);
  }
  else
  {
    snprintf(buf, buf_size, "%'.3f %s", d_bytes, suffixes[i]);
  }
}