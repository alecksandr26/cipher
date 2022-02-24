
#ifndef __ERROR_CIPHER_H_
#define __ERROR_CIPHER_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* This is the error string */
char ERROR[255] = "\033[0;31mError\033[0m: ";

/* catchError: To get an error inside of the program */
void catchError (char *message);

#endif
