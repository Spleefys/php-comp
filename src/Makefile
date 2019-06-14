.PHONY: all run clean

all: build comp

build:
	mkdir -p build

build/main.o: main.c
	gcc -c main.c -o build/main.o

build/lex.o: lex.c
	gcc -c lex.c -o build/lex.o

build/AST.o: AST.c
	gcc -c AST.c -o build/AST.o

build/parse.o: parse.c
	gcc -c parse.c -o build/parse.o

comp: build/main.o build/lex.o build/AST.o build/parse.o
	gcc build/main.o build/lex.o build/AST.o build/parse.o -o comp

run:
	./comp t.txt

clean:
	rm -rf build comp *.gv
