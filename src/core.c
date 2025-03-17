#include <stdlib.h>

#include <core.h>

char *err_msg(status_codes_t code) {
    switch (code) {
    case -1:
        return "[Memory Error]: Dynamic allocation of memory failed!";
        break;

    case -2:
        return "[Memory Error]: Failed accessing memory!";
        break;

    case -3:
        return "[Memory Error]: Accessed memory was corrupted!";
        break;

    case -10:
        return "[Array Error]: Accessed array was empty!";
        break;

    case -11:
        return "[Array Error]: Index was out of bounds!";
        break;

    case -12:
        return "[Array Error]: Array excedded maximum allowed size!";
        break;

    case -13:
        return "[Array Error]: Passed array was NULL!";
        break;

    case -15:
        return "[Validation Error]: Passed parameters to function were "
               "invalid!";
        break;

    case -16:
        return "[Validation Error]: Validation state is invalid!";
        break;

    case -17:
        return "[Validation Error]: Validation failed!";
        break;

    case -20:
        return "[Runtime Error]: Operation failed to execute!";
        break;

    case -21:
        return "[Runtime Error]: Calculation within operation failed!";
        break;

    case -22:
        return "[Runtime Error]: Function is not implemented yet!";
        break;

    default:
        return NULL;
        break;
    }
}