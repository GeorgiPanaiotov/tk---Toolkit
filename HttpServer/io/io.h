#ifndef IO_H
#define IO_H

#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>

#define DEFAULT_READ_SIZE 8192
#define DEFAULT_HEADER_SIZE 512

void load_file(int* client, const char* path, int flags, int modes);
void send_file(int* fd, char* text, ssize_t buffer_length);
void read_stream(int* client, int* fd, char* buffer);
int open_socket(int domain, int type, int protocol);
struct sockaddr_in configure_server();
void get_path(char* method, char* path, char* request);
char* resolve_path(char* path);
void send_headers(int* client_fd, char* headers);

#endif