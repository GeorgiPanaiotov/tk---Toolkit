#ifndef TOKEN_H
#define TOKEN_H

#include <stdlib.h>
#include <stdio.h>

typedef enum
{
  TOKEN_HEADING1,
  TOKEN_HEADING2,
  TOKEN_HEADING3,
  TOKEN_HEADING4,
  TOKEN_PARAGRAPH,
  TOKEN_LINEBREAK,
  TOKEN_BOLD,
  TOKEN_ITALIC,
  TOKEN_BLOCKQUOTE,
  TOKEN_LIST_UNORDERED,
  TOKEN_LIST_ORDERED,
  TOKEN_CODE,
  TOKEN_LINK,
  TOKEN_IMAGE
} TokenType;

typedef struct Token
{
  TokenType type;
  char *value;
  int length;
} Token;

typedef struct TokenList
{
  Token *tokens;
  size_t token_count;
  size_t token_capacity;
} TokenList;

#define TOKEN_CAPACITY 256

TokenList init_token_list();
void add_token(TokenList *list, Token token);

#endif