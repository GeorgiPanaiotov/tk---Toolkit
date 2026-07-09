#ifndef IO_H
#define IO_H

#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

#include "elf_st.h"

int r_load_file(const char *path, int flags, int modes);
off_t r_get_file_size(int *fd);
void print_file(int *fd, char *buffer, off_t file_size);
void close_fd(int *fd);
char *read_file(int *fd);

#endif