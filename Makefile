C = clang

BINS = cipher
LIBS = lib/fileobject.so lib/errorcipher.so

all: $(BINS)

# To move the program to the binaries files
move: $(BINS)
	sudo mv $< /usr/bin/

lib/errorcipher.so: src/errorcipher.c include/errorcipher.h
	$(C) -fPIC -shared -lc $< -o $@

# Here I compile the libraries 
lib/fileobject.so: src/fileobject.c include/fileobject.h lib/errorcipher.so
	$(C) -fPIC -shared -lc $< lib/errorcipher.so -o $@

cipher: ./cipher.c $(LIBS)
	$(C) $< $(LIBS) -o $@
