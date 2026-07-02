#include "parser.h"

void mdc_walk(TokenList *list, char *buffer, size_t file_size)
{
  size_t i = 0;
  while (i < file_size && buffer[i] != '\0')
  {
    if (buffer[i] == '\n')
    {
      Token new_line_token = {.length = 1, .type = TOKEN_LINEBREAK, .value = &buffer[i]};
      add_token(list, new_line_token);
      i++;
      continue;
    }
    if (buffer[i] == '#')
    {
      int heading_count = 0;

      while (i < file_size && buffer[i] == '#')
      {
        heading_count++;
        i++;
      }

      Token heading_token;

      if (buffer[i] == ' ')
      {

        if (heading_count == 1)
          heading_token.type = TOKEN_HEADING1;
        else if (heading_count == 2)
          heading_token.type = TOKEN_HEADING2;
        else if (heading_count == 3)
          heading_token.type = TOKEN_HEADING3;
        else
          heading_token.type = TOKEN_HEADING4;

        i++;
      }
      size_t text_start = i;

      while (i < file_size && buffer[i] != '\0' && buffer[i] != '\n' && buffer[i] != '#' && buffer[i] != '*' && buffer[i] != '_' && buffer[i] != '`')
      {
        i++;
      }

      heading_token.length = i - text_start;
      heading_token.value = &buffer[text_start];
      add_token(list, heading_token);
      continue;
    }
    if (buffer[i] == '*' || buffer[i] == '_')
    {
      if (peek(buffer, i + 1, file_size) == buffer[i])
      {
        Token bold_token = {.type = TOKEN_BOLD, .value = &buffer[i], .length = 2};
        add_token(list, bold_token);
        i += 2;
        continue;
      }
      else
      {
        Token italic_token = {.type = TOKEN_ITALIC, .value = &buffer[i], .length = 1};
        add_token(list, italic_token);
        i++;
        continue;
      }
    }
    if (buffer[i] == '`')
    {
      Token code_token = {.type = TOKEN_CODE, .value = &buffer[i], .length = 1};
      add_token(list, code_token);
      i++;
      continue;
    }
    if (buffer[i] == '>')
    {
      Token block_quote_token;
      block_quote_token.type = TOKEN_BLOCKQUOTE;

      size_t text_start = i + 1;
      while (i < file_size && buffer[i] != '\0' && buffer[i] != '\n')
      {
        i++;
      }
      block_quote_token.length = i - text_start;
      block_quote_token.value = &buffer[text_start];
      add_token(list, block_quote_token);
      continue;
    }

    size_t text_start = i;
    while (i < file_size && buffer[i] != '\0' && buffer[i] != '\n' && buffer[i] != '#' && buffer[i] != '*' && buffer[i] != '_' && buffer[i] != '`')
    {
      i++;
    }

    Token text_token = {.type = TOKEN_PARAGRAPH, .value = &buffer[text_start], .length = i - text_start};
    add_token(list, text_token);
  }
}

char peek(char *buffer, size_t i, size_t file_size)
{
  if (i < file_size)
  {
    return buffer[i];
  }
  return '\0';
}

const char *token_type_to_string(TokenType type)
{
  switch (type)
  {
  case TOKEN_HEADING1:
    return "HEADING 1";
  case TOKEN_HEADING2:
    return "HEADING 2";
  case TOKEN_HEADING3:
    return "HEADING 3";
  case TOKEN_HEADING4:
    return "HEADING 4";
  case TOKEN_BLOCKQUOTE:
    return "BLOCKQUOTE";
  case TOKEN_BOLD:
    return "BOLD";
  case TOKEN_CODE:
    return "CODE";
  case TOKEN_IMAGE:
    return "IMAGE";
  case TOKEN_ITALIC:
    return "ITALIC";
  case TOKEN_LINEBREAK:
    return "LINEBREAK";
  case TOKEN_LINK:
    return "LINK";
  case TOKEN_LIST_ORDERED:
    return "ORDERED LIST";
  case TOKEN_LIST_UNORDERED:
    return "UNORDERED LIST";
  case TOKEN_PARAGRAPH:
    return "PARAGRAPH";
  default:
    return "UNKNOWN";
  }
}