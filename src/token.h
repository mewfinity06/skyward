#ifndef TOKEN_H
#define TOKEN_H

#include <stdio.h>

#include "error.h"

typedef enum {
    ROOT,
    IDENT,
} TokenKind;

typedef struct Token {
    char *beginning;
    char *end;
    TokenKind kind;

    struct Token *next_token;

} Token;

Token *token_new(char *beginning, char *end, TokenKind kind) {
    Token *token = (Token*) malloc(sizeof(Token));

    token->beginning = beginning;
    token->end = end;
    token->kind = kind;
    token->next_token = NULL;

    return token;
}

void token_print(Token *token) {
    printf("Token\n  Kind: %d,\n  Word: `%.*s`\n", token->kind, token->end - token->beginning, token->beginning);
}  


#endif // TOKEN_H