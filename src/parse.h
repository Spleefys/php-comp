#ifndef PARSE_H
#define PARSE_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "lex.h"
#include "AST.h"

typedef struct parse {
    tokens* Tokens;
    tokens* lookahead;
    int count;
    struct AST *root;
} Parse;

Parse* parse;

struct AST* initParse(tokens* Tokens);
void Start(Parse* parser);
void StList( );
void input(struct AST* inputNode);
void semiid();
void print(struct AST *node);
void initi(struct AST* node);
void varorarr(struct AST* node);
void litornum(struct AST* node);
void type();
void term(struct AST* node);
void add_prior1(struct AST* node);
void add_prior2(struct AST* node);
void mult_prior1(struct AST* node);
void mult_prior2(struct AST* node);
void group(struct AST* node);
void mult_prior_oper(struct AST* node);
void add_prior_oper(struct AST* node);
void id_or_sign_number(struct AST* node);
void method_or_array(struct AST* node);
void call_method(struct AST* node);
void pass_arg(struct AST* node);
void tail_pass_arg(struct AST* node);
void sign_number(struct AST* node);
void sign(struct AST* node);
void ifstmt(struct AST* StartNode);
void expression(struct AST* node);
void first_prior_expr1(struct AST* node);
void first_prior_expr2(struct AST* node);
void group_expr (struct AST* node);
void condition(struct AST* node);
void dowhile(struct AST* StartNode);

void match(char* x);
void consume();
tokens* nextToken();
tokens* getLookahead();
void printErrorMessage(int row, int column, char *x);

#endif