#ifndef WALKER_H
#define WALKER_H

#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/stat.h>
#include <dirent.h>
#include <stdbool.h>

#include "proj.h"

void loc_walk(Project *proj, char *path, int flags, int modes);
off_t get_file_size(int *fd);
char *load_file(int *fd);
File parse_file(char *buffer, char *path);
const char *get_file_ext(char *path);
char *get_file_language(char *path);
void loc_add_file_to_proj(File file, Project *proj);
bool check_char(char c, char cmp);
void parse_char(File* file, char c);
bool loc_skip_dir(char *directory);

#endif