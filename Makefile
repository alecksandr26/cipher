
BINS = cipher

all: $(BINS)

# To move the program to the binaries files
move: $(BINS)
	sudo mv cipher /usr/bin/



cipher: ./cipher.c
	cc cipher.c -o cipher
