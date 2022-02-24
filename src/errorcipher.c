#include "../include/errorcipher.h"

/* catchError: Here we get out from the program with an error */
void catchError (char *msg)
{
	strcat(ERROR, msg);
	fprintf(stderr, ERROR);
	exit(EXIT_FAILURE);
}
