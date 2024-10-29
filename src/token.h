#ifndef TOKEN_H
#define TOKEN_H

#include <stdio.h>
#include <setjmp.h>

#include "error.h"

typedef enum {
    ROOT,
    IDENT,
    NUMBER,
} TokenKind;

char* human(TokenKind kind) {
    switch (kind) {
    case ROOT:
        return "ROOT";
    case IDENT:
        return "IDENT";
    case NUMBER:
        return "NUMBER";
    default:
        return "UNKNOWN";
    }
}

typedef struct Token {
    char *beginning;
    char *end;
    TokenKind kind;
    struct Token *next;

} Token;

Token *token_new(char *beginning, char *end, TokenKind kind) {
    Token *token = (Token*) malloc(sizeof(Token));

    token->beginning = beginning;
    token->end = end;
    token->kind = kind;
    token->next = NULL;

    return token;
}

void token_print(Token *token) {
    printf("Token\n  Kind: %s,\n  Word: `%.*s`\n", human(token->kind), (int)(token->end - token->beginning), token->beginning);
}

Error update_kind(Token *token) {
    Error err = ok;

    size_t length = token->end - token->beginning;
    char *word = malloc(length + 1); // Allocate space with null terminator

    if (!word) {
        ERROR_PREP(err, ERROR_ALLOCATE, "Could not allocate space for word");
        return err; // Return the error if allocation fails
    }

    memcpy(word, token->beginning, length);
    word[length] = '\0'; // Null-terminate the copied string

    // Use strtol for better error handling
    char *endptr;
    long value = strtol(word, &endptr, 10);

    if (*endptr == '\0') { // Successfully parsed entire string as a number
        token->kind = NUMBER;
    } else { // Not a valid number, must be an identifier
        token->kind = IDENT;
    }

    free(word);
    return err; // Return err, which is 'ok' if no errors occurred
}



#endif // TOKEN_H