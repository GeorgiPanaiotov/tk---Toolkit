#include "io.h"

int main()
{
  // load_file("./html/index.html", O_RDONLY, S_IRUSR | S_IRGRP | S_IROTH);
  int server_fd = open_socket(AF_INET, SOCK_STREAM, 0);

  char request_buffer[DEFAULT_READ_SIZE + 1];
  request_buffer[DEFAULT_READ_SIZE] = '\0';

  char method[16];
  char path[256];

  struct sockaddr_in client_addr;
  int mock_client = -1;

  while (1)
  {
    socklen_t client_size = sizeof(client_addr);
    int client_fd = accept(server_fd, (struct sockaddr *)&client_addr, &client_size);
    if (client_fd == -1)
    {
      perror("main: accept");
      close(server_fd);
      exit(EXIT_FAILURE);
    }
    read_stream(&mock_client, &client_fd, request_buffer);
    get_path(method, path, request_buffer);
    char *file_name = resolve_path(path);
    load_file(&client_fd, file_name, O_RDONLY, S_IRUSR | S_IRGRP | S_IROTH);

    close(client_fd);
  }

  close(server_fd);
  return 0;
}