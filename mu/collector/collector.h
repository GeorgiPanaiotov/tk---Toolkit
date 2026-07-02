#ifndef COLLECTOR_H
#define COLLECTOR_H

#include <fcntl.h>
#include <sys/stat.h>
#include <dirent.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>

#include "proj_stat.h"

#define BLOCK_SIZE 512

void mu_walk(ProjectStats *proj, char* path, int flags, int modes);
void mu_add_file_to_proj(File file, ProjectStats *proj);
bool mu_skip_dir(char *directory);

#endif