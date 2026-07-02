#include "file_handler.h"
#include "parser.h"
#include "ast.h"

int main(int argc, char *argv[])
{
  if (argc < 2)
  {
    printf("Insufficient Arguments!\n");
    exit(EXIT_FAILURE);
  }

  TokenList token_list = init_token_list();

  int fd = open_file(argv[1], O_RDONLY, S_IRUSR | S_IRGRP | S_IROTH);
  char *buffer = load_file(&fd);
  size_t file_size = strlen(buffer);

  mdc_walk(&token_list, buffer, file_size);

  close(fd);
  const char *ext = get_file_ext(argv[1]);

  if (strcmp(ext, "md") != 0)
  {
    printf("%s\n", buffer);
    free(buffer);
    exit(EXIT_SUCCESS);
  }

  for (size_t i = 0; i < token_list.token_count; i++)
  {
    printf("%s: %.*s\n", token_type_to_string(token_list.tokens[i].type), token_list.tokens[i].length, token_list.tokens[i].value);
  }

  free(buffer);
  return 0;
}