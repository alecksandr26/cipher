#include "../include/fileobject.h"

/* openFile: This function just opens the file */
int openFile (const char *fileName)
{
	int fd; /* file descriptor */
	
	if ((fd = open(fileName, O_RDWR)) < 0) {
		sprintf(MSG, "Opening the file '%s': %s\n", fileName, strerror(errno));
		catchError(MSG);
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
		sprintf(MSG, "Error wrinting inside of the file '%s': %s\n", f->name, strerror(errno));
		catchError(MSG);
	}

	f->offsetWrite += f->bytesT;
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


