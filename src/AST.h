#ifndef AST_H
#define AST_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "lex.h"

struct AST {
    char *string;
    tokens* Token;
    struct child* children;
    int idNode;
    int type;
    struct idTable* table;
};

struct AST* initASTNode();

struct child {
    struct AST *Node;
    struct child *next;
};

struct child *chinit();
struct child *addChild(struct child *spisok, struct AST *Node);

void add_child(struct AST* Node, struct AST* parent);

void setString(struct AST* node, char *str);
void setToken(struct AST* node, tokens *token);

struct child* searchLastChild(struct AST* node);
struct AST* getLastChild(struct AST* node);
void deleteLastChild(struct AST *node);
void swapChild(struct AST *parent, struct AST *newChild);
void addNewChild(struct AST *parent, struct AST *newChild);

void createTree(struct AST* Node);
void createConnect(FILE *graph, struct AST* Node);
void createBox(FILE *graph, struct AST* Node);
void toGvNode(FILE *graph, struct AST* Node);

#endif