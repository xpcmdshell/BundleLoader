.DEFAULT: all
.PHONY: loader testmod 

CC=clang
CCFLAGS=-DDEBUG

all: clean debug testmod	

dir:
	@mkdir -p build

debug: dir loader.c
	@echo "[*] Building loader (debug)"
	@mkdir -p build
	@$(CC) $(CCFLAGS) -Wno-deprecated-declarations loader.c -o build/loader 

testmod: dir testmod.c
	@echo "[*] Building test module"
	@$(CC) -bundle testmod.c -o build/testmod

clean:
	@echo "[*] Cleaning"
	@-rm -rf build