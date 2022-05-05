//
// Created by Dorian Hardy on 04/05/2022.
//

#include "utils.h"
#include <stdarg.h>

void debug(char *message, ...){
    va_list args;
    va_start(args, message);
    vfprintf(stderr, message, args);
    va_end(args);
}