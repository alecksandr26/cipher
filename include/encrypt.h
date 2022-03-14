#ifndef __ENCRYPT_H_
#define __ENCRYPT_H_

#include "./fileobject.h"

/* encryptFile: To encrypt the data */
void encryptFile (struct FileToCipher *f);

/* decryptFile: To decrypte the data */
void decryptFile (struct FileToCipher *f);

#endif
