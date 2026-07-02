#include "io.h"

void load_file(int *client, const char *path, int flags, int modes)
{
  int fd = open(path, flags, modes);
  if (fd == -1)
  {
    perror("load_file: open");
    exit(EXIT_FAILURE);
  }

  off_t file_size = lseek(fd, 0, SEEK_END);
  if (file_size == -1)
  {
    perror("load_file: lseek");
    close(fd);
    exit(EXIT_FAILURE);
  }
  lseek(fd, 0, SEEK_SET);

  char buffer[file_size + 1];
  buffer[file_size] = '\0';

  char headers[DEFAULT_HEADER_SIZE];
  char *content_type = strstr(path, ".html") ? "text/html" : "text/css";

  snprintf(headers,
           sizeof(headers),
           "HTTP/1.1 200 OK or is it\r\n"
           "Content-Type: %s\r\n"
           "Content-Length: %zu\r\n"
           "\r\n",
           content_type,
           file_size);

  send_headers(client, headers);

  read_stream(client, &fd, buffer);

  close(fd);
}

void send_file(int *fd, char *text, ssize_t buffer_length)
{
  ssize_t total_written = 0;
  while (total_written < buffer_length)
  {
    ssize_t write_buffer = write(*fd, text + total_written, buffer_length - total_written);
    if (write_buffer == -1)
    {
      perror("send_file: write");
      close(*fd);
      exit(EXIT_FAILURE);
    }
    total_written += write_buffer;
  }
}

void read_stream(int *client, int *fd, char *buffer)
{
  ssize_t read_buffer;
  while ((read_buffer = read(*fd, buffer, DEFAULT_READ_SIZE)) > 0)
  {
    buffer[read_buffer] = '\0';
    if (*client != -1)
    {
      send_file(client, buffer, read_buffer);
    }
    else
    {
      if (strstr(buffer, "\r\n\r\n"))
      {
        break;
      }
    }
  }

  if (read_buffer == -1)
  {
    perror("load_file: read");
    close(*fd);
    exit(EXIT_FAILURE);
  }
}

int open_socket(int domain, int type, int protocol)
{
  int socket_fd = socket(domain, type, protocol);
  if (socket_fd == -1)
  {
    perror("open_socket: socket");
    exit(EXIT_FAILURE);
  }

  struct sockaddr_in server_config = configure_server();
  int bind_status = bind(socket_fd, (struct sockaddr *)&server_config, (socklen_t)sizeof(server_config));
  if (bind_status == -1)
  {
    perror("open_socket: bind");
    close(socket_fd);
    exit(EXIT_FAILURE);
  }

  int listen_status = listen(socket_fd, 16);
  if (listen_status == -1)
  {
    perror("open_socket: listen");
    close(socket_fd);
    exit(EXIT_FAILURE);
  }

  return socket_fd;
}

struct sockaddr_in configure_server()
{
  struct sockaddr_in server = {0};
  server.sin_addr.s_addr = htonl(INADDR_ANY);
  server.sin_family = AF_INET;
  server.sin_port = htons(8080);

  return server;
}

void get_path(char *method, char *path, char *request)
{
  sscanf(request, "%15s %255s", method, path);
}

char *resolve_path(char *path)
{
  if (strcmp(path, "/style.css") == 0)
  {
    return "./html/style.css";
  }
  if (strcmp(path, "/") == 0)
  {
    return "./html/index.html";
  }
  return "./html/index.html";
}

void send_headers(int *client_fd, char *headers)
{
  send_file(client_fd, headers, strlen(headers));
}
