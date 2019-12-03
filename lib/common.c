#include <stdio.h>
#include <string.h>

#include "common.h"

int abort_message(const char *msg)
{
    printf("\nERROR: %s\n", msg);
    return 1;
}

int abort_error(int e)
{
    return abort_message(strerror(e));
}

int abort_args(const char *argv0)
{
    char msg[ERROR_ARGS_MSG_LEN + 1];
    bzero(msg, ERROR_ARGS_MSG_LEN + 1);
    snprintf(msg, ERROR_ARGS_MSG_LEN, "invalid args\nUsage: %s <file>", argv0);
    return abort_message(msg);
}
