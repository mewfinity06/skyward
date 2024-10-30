#ifndef TOKEN_H
#define TOKEN_H

#include <stdio.h>
#include <ctype.h>

#include "error.h"

typedef enum {
    ROOT,
    IDENT,
    NUMBER,
    KEYWORD,
    OPERATOR_PLUS,
    OPERATOR_MINUS,
    OPERATOR_MULTIPLY,
    OPERATOR_DIVIDE,
    ASSIGNMENT,
    COMPARISON_EQUAL,
    COMPARISON_NOT_EQUAL,
    LEFT_PAREN,
    RIGHT_PAREN,
    LEFT_BRACE,
    RIGHT_BRACE,
    SEMICOLON,
    COMMA,
    STRING_LITERAL,
    CHAR_LITERAL,
    UNKNOWN,
    // Add more as needed
    TOKEN_KIND_MAX,
} TokenKind;


char* human(TokenKind kind) {
    assert(TOKEN_KIND_MAX == 20 && "Not all tokens are handled");
    switch (kind) {
    case ROOT:
        return "ROOT";
    case IDENT:
        return "IDENT";
    case NUMBER:
        return "NUMBER";
    case KEYWORD:
        return "KEYWORD";
    case OPERATOR_PLUS:
        return "OPERATOR_PLUS";
    case OPERATOR_MINUS:
        return "OPERATOR_MINUS";
    case OPERATOR_MULTIPLY:
        return "OPERATOR_MULTIPLY";
    case OPERATOR_DIVIDE:
        return "OPERATOR_DIVIDE";
    case ASSIGNMENT:
        return "ASSIGNMENT";
    case COMPARISON_EQUAL:
        return "COMPARISON_EQUAL";
    case COMPARISON_NOT_EQUAL:
        return "COMPARISON_NOT_EQUAL";
    case LEFT_PAREN:
        return "LEFT_PAREN";
    case RIGHT_PAREN:
        return "RIGHT_PAREN";
    case LEFT_BRACE:
        return "LEFT_BRACE";
    case RIGHT_BRACE:
        return "RIGHT_BRACE";
    case SEMICOLON:
        return "SEMICOLON";
    case COMMA:
        return "COMMA";
    case STRING_LITERAL:
        return "STRING_LITERAL";
    case CHAR_LITERAL:
        return "CHAR_LITERAL";
    case UNKNOWN:
        return "UNKNOWN";
    default:
        return "UNKNOWN";
    }
}


#define keyword_len sizeof(keywords) / sizeof(keywords[0])
const char *keywords[] = {
    "Int", "UInt", "Char", "Float", "UFloat", "Byte",
    "Void", "NULL", "struct", "Compact", "Loose", "Enum",
    "use", "mut", "const", "func", "impl", "private", "public",
    "if", "else", "switch", "final", "return"
};

int is_identifier(char *word) {
    if (isalpha(word[0])) {
        return 1;
    }
    return 0;
}

int is_keyword(char *word) {
    for (int i = 0; i < keyword_len; ++i) {
        if (strcmp(word, keywords[i]) == 0) { return 1; }
    }
    return 0;
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
    char *word = malloc(length + 1);
    if (!word) {
        ERROR_PREP(err, ERROR_ALLOCATE, "Could not allocate space for word");
        return err;
    }
    memcpy(word, token->beginning, length);
    word[length] = '\0'; // Null-terminate for string functions

    if (strcmp(word, "+") == 0) {
        token->kind = OPERATOR_PLUS;
    } else if (strcmp(word, "-") == 0) {
        token->kind = OPERATOR_MINUS;
    } else if (strcmp(word, "*") == 0) {
        token->kind = OPERATOR_MULTIPLY;
    } else if (strcmp(word, "/") == 0) {
        token->kind = OPERATOR_DIVIDE;
    } else if (atoi(word) != 0 || strcmp(word, "0") == 0) {
        token->kind = NUMBER;
    } else if (is_keyword(word)) {
        token->kind = KEYWORD;
    } else if (is_identifier(word)) {
        token->kind = IDENT;
    } else {
        token->kind = UNKNOWN;
    }

    free(word);
    return ok;
}


int token_compare(Token *token1, Token *token2) {

    size_t len1 = token1->end - token1->beginning;
    char *word1 = (char*) malloc(len1 + 1);

    size_t len2 = token2->end - token2->beginning;
    char *word2 = (char*) malloc(len2 + 1);

    if (!word1 || !word2) {
        return 0;
    }

    memcpy(word1, token1->beginning, len1);
    memcpy(word2, token2->beginning, len2);

    if (token1->kind != token2->kind ||
        !strcmp(word1, word2)) { 
        free(word1);
        free(word2);
        return 0; 
    }

    free(word1);
    free(word2);
    
    return 1;
}


#endif // TOKEN_H