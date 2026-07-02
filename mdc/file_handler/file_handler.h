#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define READ_SIZE 8192

int open_file(char *path, int flags, int modes);
off_t get_file_size(int *fd);
char *load_file(int *fd);
const char *get_file_ext(char *path);

#endif