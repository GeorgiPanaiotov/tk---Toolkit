#ifndef PROJSTAT_H
#define PROJSTAT_H

#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct File
{
  char *path;
  off_t size;
  off_t footprint_size;
} File;

typedef struct Metrics
{
  long long total_file_size;
  long long total_dir_size;
  long long total_file_footprint_size;
  long long total_dir_footprint_size;
} Metrics;

typedef struct ProjectStats
{
  File *files;
  size_t file_count;
  size_t file_capacity;
  Metrics total_stats;
} ProjectStats;

#define FILE_CAPACITY 256

ProjectStats mu_init_project();
void mu_update_metrics(ProjectStats *proj, off_t size, off_t footprint_size);
void format_bytes(char *buf, size_t buf_size, long long bytes);

#endif