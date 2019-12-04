#ifndef INC_3530_LAB5_COMMON_H
#define INC_3530_LAB5_COMMON_H

#include <errno.h>
#include <stdio.h>

#define print_and_file(file, fmt, ...) printf((fmt), __VA_ARGS__); fprintf((file), (fmt), __VA_ARGS__)
#define abort_message_err(e, fmt, ...) printf((fmt), __VA_ARGS__); return (e)
#define abort_error(e) abort_message_err((e), "%s\n", strerror((e)))
#define abort_if_error() if (errno != 0) { abort_error(errno); }

#endif //INC_3530_LAB5_COMMON_H
