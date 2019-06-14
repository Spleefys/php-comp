.PHONY: all run clean

all: build lex

build:
	mkdir -p build

build/main.o: main.c
	gcc -c main.c -o build/main.o

build/lex.o: lex.c
	gcc -c lex.c -o build/lex.o

lex: buld/main.o build/lex.o
	gcc build/main.o build/lex.o -o lex

run:
	./lex t.txt

clean:
	rm -rf build lex
