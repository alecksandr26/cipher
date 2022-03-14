#ifndef __OBJ_FILE_H_
#define __OBJ_FILE_H_
/* This dependency that handle the file */

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <stdbool.h>

/* To handle the files */
#include <unistd.h>
#include <fcntl.h>

/* Here we include the error catching dependency */
#include "../include/errorcipher.h"

#define SIZE_BUF 2048

/* To save the error msg */
char MSG[255];


/* This is the structure that is going to manage the file */
struct FileToCipher {
	int fdRead; /* file descriptor of the reading file */
	int fdEncrypting; /* file descriptor of the encrypted file */
	char *name;
	char *passphrase;
    int8_t dataEncrypted[SIZE_BUF];
    int8_t dataUnencrypted[SIZE_BUF];
	unsigned offsetRead;
	unsigned offsetWrite;
	unsigned bytesT; /* The num of bytes transferred */
};

/* openFile: This function just opens the file */
int openFile (const char *fileName);

/* readFile: This function read the data inside of the file */
bool readFile (struct FileToCipher *file);

/* writeFile: This function will write the data inside of the file */
void writeFile (struct FileToCipher *file);

/* wasEncrypt: To know if the file was encrypted or not */
bool wasEncrypt (struct FileToCipher *file);

/* createObject: Here we create and prepare our object */
struct FileToCipher *createObject ();

#endif

