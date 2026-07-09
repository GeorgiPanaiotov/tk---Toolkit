#include "io.h"

int r_load_file(const char *path, int flags, int modes)
{
  int fd = open(path, flags, modes);
  if (fd == -1)
  {
    perror("r_load_file: open");
    exit(EXIT_FAILURE);
  }

  return fd;
}

off_t r_get_file_size(int *fd)
{
  off_t file_size = lseek(*fd, 0, SEEK_END);
  if (file_size == -1)
  {
    perror("r_get_file_size: lseek");
    close_fd(fd);
    exit(EXIT_FAILURE);
  }

  lseek(*fd, 0, SEEK_SET);
  return file_size;
}

void print_file(int *fd, char *buffer, off_t file_size)
{
  ssize_t write_buffer;
  ssize_t write_buffer_total = 0;

  while (write_buffer_total < file_size)
  {
    write_buffer = write(1, buffer + write_buffer_total, file_size - write_buffer_total);
    if (write_buffer == -1)
    {
      perror("print_file: write");
      close_fd(fd);
      exit(EXIT_FAILURE);
      free(buffer);
    }
    write_buffer_total += write_buffer;
  }
}

void close_fd(int *fd)
{
  close(*fd);
}

char *read_file(int *fd)
{
  ssize_t read_buffer;
  ssize_t read_buffer_total = 0;
  off_t file_size = r_get_file_size(fd);
  char *buffer = malloc(file_size + 1);
  buffer[file_size] = '\0';

  while (read_buffer_total < file_size)
  {
    read_buffer = read(*fd, buffer + read_buffer_total, file_size - read_buffer_total);
    if (read_buffer == -1)
    {
      perror("read_file: read");
      free(buffer);
      close_fd(fd);
      exit(EXIT_FAILURE);
    }
    read_buffer_total += read_buffer;
  }

  // print_file(fd, buffer, file_size);
  return buffer;
}
