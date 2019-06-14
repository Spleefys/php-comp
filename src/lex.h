#ifndef LEX_H
#define LEX_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct tokens {
    char lexeme[60];
    char token[60];
    int row;
    int column;
    struct tokens *next;
} tokens;
tokens *init();
tokens *addlexeme(tokens *List, char *token, char *lexeme, int row, int column);
char *dict(char *lexeme);
tokens* ident(int argc, char const *argv);
void printtok(tokens *head);

#endif
