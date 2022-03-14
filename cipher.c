#include <stdio.h>

/* Here I include the created modules */
#include "include/fileobject.h"
#include "include/errorcipher.h"
#include "include/encrypt.h"

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

/* check: To check if the file was enctyped or not */
void check (const char *filename)
{
	struct FileToCipher *file;

	file = createObject();
	file->fdRead = openFile(filename);
	if (wasEncrypt(file))
		printf("Yeah, the file '%s' is enctyped\n", filename);
	else
		printf("No, the file '%s' is not enctyped\n", filename);
 
	exit(EXIT_SUCCESS);
}


void main (int argc, const char *argv[])
{
	struct FileToCipher *file;
	unsigned char byte;
	
	/* Here we check if we have errors */
	if (argc == 2 && strcmp(argv[1], "help") == 0)
		help(argv[0]);

	/* Here I check if the file was encrypted */
	if (argc == 3 && strcmp(argv[1], "check") == 0)
		check(argv[2]);

	if (argc != 4 && argc != 3) {
		sprintf(MSG, "Usage: %s <file-name> \"<passphrase>\" <'encrypt' || 'decrypt'>\n", argv[0]);
		catchError(MSG);
	}

	/* Here we create the object and copy the data  and open the file */
	file = createObject();
	
	memcpy(file->passphrase, argv[2], 512);
	file->fdRead = openFile(argv[1]);
	file->fdEncrypting = creat(".encryptingOrDecrypting", 0644);
	memcpy(file->name, argv[1], 512);

	/* Here we execute the action */
	if (argc == 3) {
		if (wasEncrypt(file)) {
			file->offsetRead++;
			decryptFile(file);
		} else {
			byte = ENCRYPT;
			write(file->fdEncrypting, &byte, 1);
			file->offsetWrite++;
			encryptFile(file);
		}
	} else if (strcmp(argv[3], "encrypt") == 0 || strcmp(argv[3], "en") == 0) {
		byte = ENCRYPT;
		write(file->fdEncrypting, &byte, 1);
		file->offsetWrite++;
		encryptFile(file);
	} else if (strcmp(argv[3], "decrypt") == 0 || strcmp(argv[3], "de") == 0) {
		file->offsetRead++;
		decryptFile(file);
	} else { /* if the user doens't select the option */
		sprintf(MSG, "Usage: <mode> = 'encrypt' || 'decrypte'\n");
		catchError(MSG);
	}

	close(file->fdRead);
	close(file->fdEncrypting);
	
	/* here we modify the name of the file */
	rename(".encryptingOrDecrypting", file->name);
	
	exit(EXIT_SUCCESS);
}
