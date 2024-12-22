#ifndef ERROR_HANDLING_H
#define ERROR_HANDLING_H

#include <stdio.h>
#include <stdlib.h>

// Function prototypes for error handling
void handle_error(const char *msg);
void handle_error_with_code(const char *msg, int error_code);

#endif // ERROR_HANDLING_H
