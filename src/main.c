#include "lex.h"

int main(int argc, char const *argv[]) {
	tokens* Tokens = ident(argc, argv[1]);
    printtok(Tokens);
    return 0;
}
