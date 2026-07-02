#include "file_handler.h"

int open_file(char *path, int flags, int modes)
{
  int fd = open(path, flags, modes);
  if (fd == -1)
  {
    perror("open_file: open");
    exit(EXIT_FAILURE);
  }

  return fd;
}

off_t get_file_size(int *fd)
{
  off_t file_size = lseek(*fd, 0, SEEK_END);
  if (file_size == -1)
  {
    perror("get_file_size: lseek");
    close(*fd);
    exit(EXIT_FAILURE);
  }

  lseek(*fd, 0, SEEK_SET);
  return file_size;
}

char *load_file(int *fd)
{
  off_t file_size = get_file_size(fd);
  char *buffer = malloc(file_size + 1);

  if (buffer == NULL)
  {
    perror("load_file: malloc");
    close(*fd);
    exit(EXIT_FAILURE);
  }

  buffer[file_size] = '\0';

  ssize_t read_buffer;
  ssize_t read_buffer_total = 0;

  while (read_buffer_total < file_size)
  {
    read_buffer = read(*fd, buffer + read_buffer_total, READ_SIZE);
    if (read_buffer <= 0)
    {
      break;
    }
    read_buffer_total += read_buffer;
  }
  if (read_buffer == -1)
  {
    perror("load_file: read");
    close(*fd);
    free(buffer);
    exit(EXIT_FAILURE);
  }

  return buffer;
}

const char *get_file_ext(char *path)
{
  char *dot = strrchr(path, '.');

  if (!dot || dot == path)
  {
    return path;
  }
  return dot + 1;
}
