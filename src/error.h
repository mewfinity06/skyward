#ifndef ERROR_H
#define ERROR_H

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



#endif