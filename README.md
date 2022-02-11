# cipher
Is a simple encryption program which encypts any file by a given passphrase.

# Install
Just run the Makefile.
```
$ make
```
And to move this executable program just use the argument "move".
```
$ make move
```
And now you are ready to start using this program.

# Usage
To use this program is easy you only need to select your file put a passphrase and select between "encrypt" or "decrypt", for example to encrypt some  file you can run this.
```
$ cipher foo.txt "foopassphrase" encrypt
```
And to decrypt some file you can run this.
```
$ cipher foo.txt "foopassphrase" decrypt
```
Also you can run the program with the argument "help" to see how to use this program.
```
$ cipher help
```