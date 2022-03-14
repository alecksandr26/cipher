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
There are two ways to encrypt a file, we can specify if we want to encrypt or decrypt some files, just be careful to avoid the destruction of any file.
## Specifying
It is easy you only need to select your file put a passphrase and select between "encrypt" or "decrypt", for example to encrypt some  file you can run this.
```
$ cipher foo.txt "foopassphrase" encrypt
```
And to decrypt some file you can run this.
```
$ cipher foo.txt "foopassphrase" decrypt
```
## Without specifying
It is easier, you only need to put the file and the passphrase, with these we are going to encrypt the file.
```
$ cipher foo.txt "foopassphrase"
```
And now the file is enctyped to decrypt the file we only need to run the same command.
```
$ cipher foo.txt "foopassphrase"
```
As I mentioned before be careful running program, because you can destroy some files.
# Help
Also you can run the program with the argument "help" to see how to use this program.
```
$ cipher help
```
# Another functions
Your can run "check" functionality to know if the file is encrypted or not, like this.
```
$ cipher check foo.txt
```