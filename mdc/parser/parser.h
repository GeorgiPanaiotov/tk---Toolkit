#ifndef PARSER_H
#define PARSER_H

#include <string.h>
#include <sys/types.h>
#include <stdbool.h>

#include "token.h"

void mdc_walk(TokenList *list, char *buffer, size_t file_size);
char peek(char *buffer, size_t i, size_t file_size);
const char *token_type_to_string(TokenType type);

#endif