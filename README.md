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
And now you are ready to start using the program.

# Usage
To use the program is easy you only need to select your file put a passphrase and select between "encrypt" or "decrypt", for example to encrypt some  file you can run this.
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
# To do
1. Hash the passphrase.
2. Try to encrypt the files and add extra bytes to know if the file was encrypted or not.
3. Create modules to start the scalability of the project.