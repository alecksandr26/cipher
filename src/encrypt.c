#include "../include/encrypt.h"

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

