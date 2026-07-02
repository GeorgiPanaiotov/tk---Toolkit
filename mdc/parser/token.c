#include "token.h"

TokenList init_token_list()
{
  TokenList list;
  list.token_capacity = TOKEN_CAPACITY;
  list.token_count = 0;
  list.tokens = malloc(list.token_capacity * sizeof(Token));
  if (list.tokens == NULL)
  {
    perror("init_token_list: malloc");
    exit(EXIT_FAILURE);
  }

  return list;
}

void add_token(TokenList *list, Token token)
{
  if (list->token_count >= list->token_capacity)
  {
    list->token_capacity *= 2;
    Token *temp_tokens = realloc(list->tokens, list->token_capacity * sizeof(Token));
    if (temp_tokens == NULL)
    {
      perror("add_token: realloc");
      free(list->tokens);
      exit(EXIT_FAILURE);
    }
    list->tokens = temp_tokens;
  }
  list->tokens[list->token_count] = token;
  list->token_count++;
}
