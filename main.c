#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <errno.h>

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

typedef struct Error {
    enum ErrorType {
        ERROR_NONE = 0,
        ERROR_ARGS,
        ERROR_TYPE,
        ERROR_GENERIC,
        ERROR_SYNTAX,
        ERROR_TOD0,
        ERROR_MAX,
    } type;
    char *msg;
} Error;

Error ok = { ERROR_NONE, NULL };

void print_error(Error err) {
    if (err.type == ERROR_NONE) { return; }
    printf("ERROR | ");
    assert(ERROR_MAX == 6);
    switch (err.type) {
    default:
        printf("Unknown error type...");
        break;
    case ERROR_TOD0:
        printf("TODO (not implemented)");
        break;
    case ERROR_SYNTAX:
        printf("Invalid syntax");
        break;
    case ERROR_TYPE:
        printf("Mismatched types");
        break;
    case ERROR_ARGS:
        printf("Invalud arguments");
        break;
    case ERROR_GENERIC:
        break;
    case ERROR_NONE:
        break;
    }
    putchar('\n');
    if (err.msg) {
        printf("      ` %s\n", err.msg);
    }
}

#define is_ok(err)                              \
    ((err).type == ERROR_NONE)

#define ERROR_CREATE(n, t, message)             \
    Error (n) = { (t), (message) }

#define ERROR_PREP(n, t, message)               \
    (n).type = (t);                             \
    (n).msg = (message);

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

Error parse_file(char *source) {
    char *beg = source;
    char *end = source;
    Error err = ok;

    size_t total = 0;

    while ((err = lex(end, &beg, &end)).type == ERROR_NONE) {
        if (end - beg == 0) { break; }
        printf("lexed: %.*s\n", end - beg, beg);
        total++;
    }

    printf("Printed %ld total tokens\n", total);

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