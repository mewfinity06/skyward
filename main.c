#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <errno.h>

#include "src/error.h"
#include "src/token.h"

char *get_contents(char *path) {
    FILE *file = fopen(path, "r");
    if (!file) {
        printf("Could not open file at %s\n", path);
        return NULL;
    }

    // Buffer to store processed content without comments
    char *contents = malloc(1);
    if (!contents) {
        fclose(file);
        return NULL;
    }
    contents[0] = '\0';  // Initialize to an empty string

    // Line buffer for reading each line
    char line[256];
    size_t total_length = 0;

    while (fgets(line, sizeof(line), file)) {
        // Check for a single-line comment indicator `//`
        char *comment_start = strstr(line, "//");
        if (comment_start) {
            *comment_start = '\0';  // Truncate line at `//`
        }

        // Append the uncommented line to `contents`
        size_t line_length = strlen(line);
        char *new_contents = realloc(contents, total_length + line_length + 1);
        if (!new_contents) {
            free(contents);
            fclose(file);
            return NULL;
        }
        contents = new_contents;
        strcpy(contents + total_length, line);
        total_length += line_length;
    }

    fclose(file);
    return contents;
}

void print_usage(char **argv) {
    printf("Usage: %s <args> <file_path>\n", argv[0]);
}

const char *whitespace = " \r\n";
const char *delimiters = " \r\n!@#$\%^&*()_-+=[]{}|\\:;\"\'<>,.?/";

Error lex(char *source, char **beg, char **end) {
    Error err = ok;
    if (!source || !beg || !end) {
        ERROR_PREP(err, ERROR_ARGS, "Cannot lex empty source");
        return err;
    }
    *beg = source;
    *beg += strspn(*beg, whitespace);
    *end = *beg;
    if (**end == '\0') { return err; }
    *end += strcspn(*beg, delimiters);
    if (*end == *beg) {
        *end += 1;
    }
    return err;
}

// Error parse_file(char *source) {
//     char *beg = source;
//     char *end = source;
//     Error err = ok;

//     size_t total = 0;

//     Token *tokens = (Token*) malloc(sizeof(Token));
//     Token *curr_token = token_new(&beg, &end, ROOT);

//     tokens = curr_token;

//     while ((err = lex(end, &beg, &end)).type == ERROR_NONE) {
//         if (end - beg == 0) { break; }
//         // printf("lexed: %.*s\n", end - beg, beg);

//         curr_token->beginning = &beg;
//         curr_token->end = &end;
//         curr_token->kind = IDENT;

//         tokens = realloc(tokens, (total + 1) * sizeof(Token));
//         tokens[total] = *curr_token;

//         total++;
//     }

//     for (size_t i = 0; i < total; i++) {
//         token_print(&tokens[i]);
//     }

//     printf("Printed %ld total tokens\n", total);

//     return err;
// }

Error parse_file(char *source) {
    char *beg = source;
    char *end = source;
    Error err = ok;

    size_t total = 0;
    size_t capacity = 1;

    Token *tokens = (Token*) malloc(capacity * sizeof(Token));
    if (tokens == NULL) {
        ERROR_PREP(err, ERROR_ALLOCATE, "Unable to allocate tokens");
        return err;
    } // Handle allocation failure

    while ((err = lex(end, &beg, &end)).type == ERROR_NONE) {
        if (end - beg == 0) break;

        Token curr_token;
        curr_token.beginning = beg;
        curr_token.end = end;
        curr_token.kind = IDENT;

        update_kind(&curr_token);

        // Reallocate memory if capacity is reached
        if (total >= capacity) {
            capacity *= 2; // Increase capacity, e.g., double
            Token *new_tokens = realloc(tokens, capacity * sizeof(Token));
            if (new_tokens == NULL) { // Handle realloc failure
                free(tokens);
                ERROR_PREP(err, ERROR_ALLOCATE, "Unable to reallocate tokens");
                return err;
            }
            tokens = new_tokens;
        }

        tokens[total++] = curr_token;
    }

    for (size_t i = 0; i < total; i++) {
        token_print(&tokens[i]);
    }

    printf("Printed %ld total tokens\n", total);

    free(tokens); // Free allocated memory for tokens

    return err;
}


int main(int argc, char **argv) {
    if (argc <= 1) {
        print_usage(argv);
        return 1;
    }

    char* file_contents = get_contents(argv[1]);

    Error err = parse_file(file_contents);
    print_error(err);

}