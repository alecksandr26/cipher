
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <errno.h>
#include <string.h>

#include <unistd.h>
#include <fcntl.h>



#define SIZE_BUF 2048

const char ERROR[] = "\033[0;31mError\033[0m";


struct FileToCipher {
	int fd; /* file descriptor */
	char *name;
	char *passphrase;
	unsigned char dataEncrypted[SIZE_BUF];
	unsigned char dataUnencrypted[SIZE_BUF];
	unsigned offsetRead;
	unsigned offsetWrite;
	unsigned bytesT; /* The num of bytes transferred */
};


/* openFile: This function just opens the file */
int openFile (const char *fileName)
{
	int fd; /* file descriptor */
	
	if ((fd = open(fileName, O_RDWR)) < 0) {
		fprintf(stderr, "%s: Opening the file '%s': %s\n", ERROR, fileName, strerror(errno));
		exit(EXIT_FAILURE);
	}

	return fd;
}


/* readFile: This function read the data inside of the file */
bool readFile (struct FileToCipher *f)
{	
	if ((f->bytesT = pread(f->fd, f->dataUnencrypted, SIZE_BUF, f->offsetRead)) ==  0)
		return false;
	
	f->offsetRead += f->bytesT;
	return true;
}


/* writeFile: This function will write the data inside of the file */
void writeFile (struct FileToCipher *f)
{
	long bytesT; /* bytes transferred */
	if ((bytesT = pwrite(f->fd, f->dataEncrypted, f->bytesT, f->offsetWrite)) != f->bytesT) {
		fprintf(stderr, "%s: Error wrinting inside of the file '%s': %s\n",
				ERROR, f->name, strerror(errno));
		exit(EXIT_FAILURE);
	}

	f->offsetWrite += f->bytesT;
}


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


/* createObject: Here we create and prepare our object */
struct FileToCipher *createObject ()
{
	struct FileToCipher *f = (struct FileToCipher *) malloc(sizeof(struct FileToCipher));

	f->name = (char *) malloc(512);
	f->passphrase = (char *) malloc(512);
	f->offsetRead = 0;
	f->offsetWrite = 0;

	memset(f->name, 0, 512);
	memset(f->passphrase, 0, 512);
	
	return f;
}




void main (int argc, const char *argv[])
{
	struct FileToCipher *file;

	/* Here we check if we have errors */
	if (argc == 2 && strcmp(argv[1], "help") == 0)
		help(argv[0]);
		
	if (argc != 4) {
		fprintf(stderr, "%s: Usage: %s <file-name> \"<passphrase>\" <'encrypt' || 'decrypt'>\n", ERROR, argv[0]);
		exit(EXIT_FAILURE);
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
		fprintf(stderr, "%s: Usage: <mode> = 'encrypt' || 'decrypte'\n", ERROR);
		exit(EXIT_FAILURE);
	}
	
	close(file->fd);
	
}
