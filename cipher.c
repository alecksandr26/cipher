

#include <stdio.h>

#include <stdlib.h>
#include <stdbool.h>
#include <errno.h>
#include <string.h>
#include <stdint.h>

/* To handle the files */
#include <unistd.h>
#include <fcntl.h>

/* Here I include the created modules */
#include "include/fileobject.h"
#include "include/errorcipher.h"


/* encryptFile: To encrypt the data */
void encryptFile (struct FileToCipher *f)
{
	unsigned short c; /* char caracter */
	int i, i2; /* indexes */
	
	/* Iterates the file */
	while (readFile(f)) {
		i2 = 0;
		/* Here we iterate the readed bytes */
		while (i2 < f->bytesT) {
			/* Now we iterate the key */
			for (i = 0; i < strlen(f->passphrase) && i2 < f->bytesT; ++i) {
				c = f->dataUnencrypted[i2] + *(f->passphrase + i);
				f->dataEncrypted[i2] = (c % 256);
				i2++;
			}
		}
		/* Here we write the encrypted bytes */
		writeFile(f);
	}
}



/* decryptFile: To decrypte the data */
void decryptFile (struct FileToCipher *f)
{
	unsigned short c; /* char caracter */
	int i, i2; /* indexes */
	
	/* Iterates the file */
	while (readFile(f)) {
		i2 = 0;
		/* Here we iterate the readed bytes */
		while (i2 < f->bytesT) {
			/* Now we iterate the key */
			for (i = 0; i < strlen(f->passphrase) && i2 < f->bytesT; ++i) {
			    if (f->dataUnencrypted[i2] < *(f->passphrase + i)) {
					c = f->dataUnencrypted[i2] + 256;
					f->dataEncrypted[i2] = c - *(f->passphrase + i);
				} else
					f->dataEncrypted[i2] = f->dataUnencrypted[i2] - *(f->passphrase + i);
				i2++;
			}
		}
		/* Here we write the uncrypted bytes */
		writeFile(f);
	}
}


/* help: This is a simple help function */
void help (const char *argv)
{
	printf("Usage: %s <file-name> \"<passphrase>\" <'encrypt' || 'decrypt'>\n\n", argv);
	printf("<file-name> = Your file\n");
	printf("\"<passphrase>\" = Your key and also you must use (\"\")\n");
	printf("<'encrypt' || 'decrypt'> = And you must select between 'encrypt' or 'decyprt'\n\n");
	printf("Example: Encrypt: %s foo_file.txt \"foo_passphrase\" encrypt\n", argv);
	printf("Example: Decrypt: %s foo_file.txt \"foo_passphrase\" decrypt\n", argv);
	exit(EXIT_SUCCESS);
}




void main (int argc, const char *argv[])
{
	struct FileToCipher *file;

	/* Here we check if we have errors */
	if (argc == 2 && strcmp(argv[1], "help") == 0)
		help(argv[0]);
		
	if (argc != 4) {
		sprintf(MSG, "Usage: %s <file-name> \"<passphrase>\" <'encrypt' || 'decrypt'>\n", argv[0]);
		catchError(MSG);
	}

	/* Here we create the object and copy the data  and open the file */
	file = createObject();
	
	memcpy(file->passphrase, argv[2], 512);
	file->fd = openFile(argv[1]);
	memcpy(file->name, argv[1], 512);

	/* Here we execute the file */
	if (strcmp(argv[3], "encrypt") == 0)
		encryptFile(file);
	else if (strcmp(argv[3], "decrypt") == 0)
		decryptFile(file);
	else {
		sprintf(MSG, "Usage: <mode> = 'encrypt' || 'decrypte'\n");
		catchError(MSG);
	}
	
	close(file->fd);
	
}
