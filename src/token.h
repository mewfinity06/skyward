#ifndef TOKEN_H
#define TOKEN_H

#include <stdio.h>
#include <ctype.h>

#include "error.h"

typedef enum {
    ROOT,

    IDENT,
    DOUBLE_QUOTED_STRING,
    SINGLE_QUOTED_STRING,
    NUMBER,
    KEYWORD,

    PLUS,
    MINUS,
    STAR,
    DIVIDE,
    ASSIGNMENT,
    BANG,
    AROBASE,
    POUND,
    DOLLAR,
    PERCENT,
    LEFT_SQRUARE,
    RIGHT_SQUARE,
    PIPE,
    BACK_SLASH,
    COLON,
    DOUBLE_QUOTE,
    SINGLE_QUOTE,
    LEFT_ARROW,
    RIGHT_ARROW,
    DOT,
    QUESTION,
    LEFT_PAREN,
    RIGHT_PAREN,
    LEFT_BRACE,
    RIGHT_BRACE,
    SEMICOLON,
    COMMA,

    PLUS_PLUS,
    MINUS_MINUS,

    PLUS_EQUALS,
    MINUS_EQUALS,
    STAR_EQUALS,
    DIV_EQUALS,

    LESS_EQUAL,
    GREATER_EQUAL,
    DOUBLE_EQUALS,
    BANG_EQUALS,

    LOGICAL_OR,
    LOGICAL_AND,

    SKINNY_ARROW,
    FAT_ARROW,

    UNKNOWN,
    // Add more as needed
    TOKEN_KIND_MAX,
} TokenKind;


char* human(TokenKind kind) {
    assert(TOKEN_KIND_MAX == 48 && "Not all tokens are handled"); 
    switch (kind) {
    case ROOT: return "ROOT";
    case IDENT: return "IDENT";
    case NUMBER: return "NUMBER";
    case KEYWORD: return "KEYWORD";
    case PLUS: return "PLUS";
    case MINUS: return "MINUS";
    case STAR: return "STAR";
    case DIVIDE: return "DIVIDE";
    case ASSIGNMENT: return "ASSIGNMENT";
    case BANG: return "BANG";
    case AROBASE: return "AROBACE";
    case POUND: return "POUND";
    case DOLLAR: return "DOLLAR";
    case PERCENT: return "PERCENT";
    case LEFT_SQRUARE: return "LEFT_SQUARE";
    case RIGHT_SQUARE: return "RIGHT_SQUARE";
    case PIPE: return "PIPE";
    case BACK_SLASH: return "BACK_SLASH";
    case COLON: return "COLON";
    case DOUBLE_QUOTE: return "DOUBLE_QUOTE";
    case SINGLE_QUOTE: return "SINGLE_QUOTE";
    case LEFT_ARROW: return "LEFT_ARROW";
    case RIGHT_ARROW: return "RIGHT_ARROW";
    case DOT: return "DOT";
    case QUESTION: return "QUESTION";
    case LEFT_PAREN: return "LEFT_PAREN";
    case RIGHT_PAREN: return "RIGHT_PAREN";
    case LEFT_BRACE: return "LEFT_BRACE";
    case RIGHT_BRACE: return "RIGHT_BRACE";
    case SEMICOLON: return "SEMICOLON";
    case COMMA: return "COMMA";
    case DOUBLE_QUOTED_STRING: return "DOUBLE_QUOTED_STRING";
    case SINGLE_QUOTED_STRING: return "SINGLE_QUOTED_STRING";
    case PLUS_PLUS: return "PLUS_PLUS";
    case MINUS_MINUS: return "MINUS_MINUS";
    case PLUS_EQUALS: return "PLUS_EQUALS";
    case MINUS_EQUALS: return "MINUS_EQUALS";
    case STAR_EQUALS: return "STAR_EQUAL";
    case DIV_EQUALS: return "DIV_EQUALS";
    case LESS_EQUAL: return "LESS_EQUAL";
    case GREATER_EQUAL: return "GREATER_EQUAL";
    case DOUBLE_EQUALS: return "DOUBLE_EQUALS";
    case BANG_EQUALS: return "BANG_EQUALS";
    case LOGICAL_OR: return "LOGICAL_OR";
    case LOGICAL_AND: return "LOGICAL_AND";
    case SKINNY_ARROW: return "SKINNY_ARROW";
    case FAT_ARROW: return "FAT_ARROW";
    default: return "UNRECOGNIZED_TOKEN";
    }
}




#define keyword_len sizeof(keywords) / sizeof(keywords[0])
const char *keywords[] = {
    // Builtin types
    "Int", "UInt", "Char", "Float", "UFloat", "Byte",
    "Void", "NULL", 
    // Struct keywords
    "struct", "Compact", "Loose", "Enum",
    // Variable keywords
    "mut", "const",
    // Misc keywords
    "func", "impl", "private", "public",
    "if", "else", "switch", "final", "return", "use",
};

int is_identifier(char *word) {
    if (isalpha(word[0])) {
        return 1;
    }
    return 0;
}

int is_keyword(char *word) {
    for (int i = 0; i < (keyword_len); ++i) {
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
    printf("Token - Kind: %s\n", human(token->kind));
    printf("        Word: %.*s\n", (int)(token->end - token->beginning), token->beginning);
    printf("\n");
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

    assert(TOKEN_KIND_MAX == 48 && "Not all tokens are handled");

    if (strcmp(word, "+") == 0) {
        token->kind = PLUS;
    } else if (strcmp(word, "-") == 0) {
        token->kind = MINUS;
    } else if (strcmp(word, "*") == 0) {
        token->kind = STAR;
    } else if (strcmp(word, "/") == 0) {
        token->kind = DIVIDE;
    } else if (strcmp(word, "=") == 0) {
        token->kind = ASSIGNMENT;
    } else if (strcmp(word, "!") == 0) {
        token->kind = BANG;
    } else if (strcmp(word, "@") == 0) {
        token->kind = AROBASE;
    } else if (strcmp(word, "/#") == 0) {
        token->kind = POUND;
    } else if (strcmp(word, "$") == 0) {
        token->kind = DOLLAR;
    } else if (strcmp(word, "%") == 0) {
        token->kind = PERCENT;
    } else if (strcmp(word, "[") == 0) {
        token->kind = LEFT_SQRUARE;
    } else if (strcmp(word, "]") == 0) {
        token->kind = RIGHT_SQUARE;
    } else if (strcmp(word, "|") == 0) {
        token->kind = PIPE;
    } else if (strcmp(word, "\\") == 0) {
        token->kind = BACK_SLASH;
    } else if (strcmp(word, ":") == 0) {
        token->kind = COLON;
    } else if (strcmp(word, "\"") == 0) {
        token->kind = DOUBLE_QUOTE;
    } else if (strcmp(word, "'") == 0) {
        token->kind = SINGLE_QUOTE;
    } else if (strcmp(word, "<") == 0) {
        token->kind = LEFT_ARROW;
    } else if (strcmp(word, ">") == 0) {
        token->kind = RIGHT_ARROW;
    } else if (strcmp(word, ".") == 0) {
        token->kind = DOT;
    } else if (strcmp(word, "++") == 0) {
        token->kind = PLUS_PLUS;
    } else if (strcmp(word, "--") == 0) {
        token->kind = MINUS_MINUS;
    } else if (strcmp(word, "+=") == 0) {
        token->kind = PLUS_EQUALS;
    } else if (strcmp(word, "-=") == 0) {
        token->kind = MINUS_EQUALS;
    } else if (strcmp(word, "*=") == 0) {
        token->kind = STAR_EQUALS;
    } else if (strcmp(word, "/=") == 0) {
        token->kind = DIV_EQUALS;
    } else if (strcmp(word, "<=") == 0) {
        token->kind = LESS_EQUAL;
    } else if (strcmp(word, ">=") == 0) {
        token->kind = GREATER_EQUAL;
    } else if (strcmp(word, "==") == 0) {
        token->kind = DOUBLE_EQUALS;
    } else if (strcmp(word, "!=") == 0) {
        token->kind = BANG_EQUALS;
    } else if (strcmp(word, "&&") == 0) {
        token->kind = LOGICAL_AND;
    } else if (strcmp(word, "||") == 0) {
        token->kind = LOGICAL_OR;
    } else if (strcmp(word, "->") == 0) {
        token->kind = SKINNY_ARROW;
    } else if (strcmp(word, "=>") == 0) {
        token->kind = FAT_ARROW;
    } else if (strcmp(word, "(") == 0) {
        token->kind = LEFT_PAREN;
    } else if (strcmp(word, ")") == 0) {
        token->kind = RIGHT_PAREN;
    } else if (strcmp(word, "{") == 0) {
        token->kind = LEFT_BRACE;
    } else if (strcmp(word, "}") == 0) {
        token->kind = RIGHT_BRACE;
    } else if (strcmp(word, ";") == 0) {
        token->kind = SEMICOLON;
    } else if (strcmp(word, ",") == 0) {
        token->kind = LEFT_SQRUARE;
    } else if (word[0] == '"' && word[strlen(word)-1] == '"') {
        token->kind = DOUBLE_QUOTED_STRING;
    } else if (word[0] == '\'' && word[strlen(word)-1] == '\'') {
        token->kind = SINGLE_QUOTED_STRING;
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