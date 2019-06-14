#include "lex.h"

tokens *init() {
    tokens *tok;
    tok = (tokens*)malloc(sizeof(tokens));
    tok->row = -1;
    tok->next = NULL;
    return tok;
}

tokens *addlexeme(tokens *spisok, char *token, char *lexeme, int row, int column) {
    if (spisok->row == -1) {
        strcpy(spisok->lexeme, lexeme);
        strcpy(spisok->token, token);
        spisok->row = row;
        spisok->column = column;
        return spisok;
    } else {
        tokens *spisok2;
        spisok2 = (tokens*)malloc(sizeof(tokens));
        spisok->next = spisok2;
        strcpy(spisok2->lexeme, lexeme);
        strcpy(spisok2->token, token);
        spisok2->row = row;
        spisok2->column = column;
        spisok2->next = NULL;
        return spisok2;
    }
    return NULL;
}

char *dict(char *lexeme) {
    if(strcmp(lexeme, "require") == 0)
        return "input";
    if(strcmp(lexeme, "print") == 0)
        return "print";
	if(strcmp(lexeme, "echo") == 0)
        return "echo";
    if(strcmp(lexeme, "+") == 0)
        return "plus";
    if(strcmp(lexeme, "-") == 0)
        return "minus";
    if(strcmp(lexeme, "*") == 0)
        return "multiply";
    if(strcmp(lexeme, "/") == 0)
        return "divide";
    if(strcmp(lexeme, "\\") == 0)
        return "div";
    if(strcmp(lexeme, "^") == 0)
        return "pow";
    if(strcmp(lexeme, "mod") == 0)
        return "mod";
    if(strcmp(lexeme, "=") == 0)
        return "equal";
    if((strcmp(lexeme, "<>") == 0||strcmp(lexeme, "!=") == 0))
        return "not_equal";
    if(strcmp(lexeme, ">") == 0)
        return "more";
    if(strcmp(lexeme, "<") == 0)
        return "less";
    if(strcmp(lexeme, ">=") == 0)
        return "more_or_equal";
    if(strcmp(lexeme, "<=") == 0)
        return "less_or_equal";
    if(strcmp(lexeme, "if") == 0)
        return "if";
    if(strcmp(lexeme, "then") == 0)
        return "then";
    if(strcmp(lexeme, "else") == 0)
        return "else";
    if(strcmp(lexeme, "do") == 0)
        return "do";
    if(strcmp(lexeme, "while") == 0)
        return "while";
    if(strcmp(lexeme, "$") == 0)
        return "var";
    if(strcmp(lexeme, "<?php") == 0)
        return "start";
    if(strcmp(lexeme, "?>") == 0)
        return "end";
    if(strcmp(lexeme, "(") == 0)
        return "l_paren";
    if(strcmp(lexeme, ")") == 0)
        return "r_paren";
    if(strcmp(lexeme, ",") == 0)
        return "comma";
    if(strcmp(lexeme, ";") == 0)
        return "semi";
	if(lexeme[0] == '"') {
		if (lexeme[strlen(lexeme)-1] == '"')
			return "literal";
		else
			return "unknown";
    }

	if (lexeme[0] >= '0' && lexeme[0] <= '9') {
		for (int i = 1; i < strlen(lexeme); i++) {
			if (!(lexeme[i] >= '0' && lexeme[i] <= '9'))
				return "unknown";	
		} 
		return "numeric";
	}

	if ((lexeme[0] >= 'A' && lexeme[0] <= 'Z') ||
		(lexeme[0] >= 'a' && lexeme[0] <= 'z') || (lexeme[0] == '_')) {
	
		for (int i = 1; i < strlen(lexeme); i++) {
			if (!((lexeme[i] >= 'A' && lexeme[i] <= 'Z') ||
				(lexeme[i] >= 'a' && lexeme[i] <= 'z') || (lexeme[i] == '_') ||
				(lexeme[i] >= '0' && lexeme[i] <= '9')))
				return "unknown";
		}
		return "id";
	}
	return "unknown";
}

tokens *ident(int argc, char const *argv) {
	char buf[100];
	if (argc > 1) {
		FILE *file;

		file = fopen (argv, "r");

		if (file == NULL) {
			printf("error\n");
			return NULL;
		}

		tokens *spisok = init();
		tokens *head = spisok;

		char sign;
		int i = 0;
		int row = 1, column = 1;
		char *token = (char *) malloc(sizeof(char) * 80);

		while ((sign = fgetc(file)) != EOF) {		
            //литералы
			if (sign == '"') {
				buf[i] = sign;
				i++;
				column++;
				while ((sign = fgetc(file)) != '"' && sign != '\n') {
					buf[i] = sign;
					i++;
					column++;
				}
				if (sign == '"') {
					buf[i] = sign;
					i++;
					column++;
				}
				buf[i] = '\0';

				token = dict(buf);
				spisok = addlexeme(spisok, token, buf, row, column-i);

				i = 0;
				continue;
			}

			//игнор пробелов
			else if (sign == ' ') {
				if (i == 0) {
					column++;
					continue;
				}

				buf[i] = '\0';

				token = dict(buf);
				spisok = addlexeme(spisok, token, buf, row, column-i);

				i = 0;
				column++;
				continue;
			}
			//новая строка
			else if (sign == '\n') {
				if (i == 0){
					column = 1;
					row++;
					continue;
				}

				buf[i] = '\0';
				
				token = dict(buf);
				spisok = addlexeme(spisok, token, buf, row, column-i);

				column = 1;
				row++;
				i = 0;
				continue;
			}
			//игнор комментов
			else if (sign == '/'){
				if ((sign = fgetc(file)) == '/') {
					while ((sign = fgetc(file)) != '\n')
							continue;
					i = 0;
					row++;
					column = 1;
					continue;
				}
				else if (sign == '*') {
					sign = fgetc(file);
					while (sign != '*' && (sign = fgetc(file)) != '/'){
						if (sign == '\n') {
							row++;
						}
						continue;
					}
					sign = fgetc(file);
					i = 0;
					column = 1;
					continue;
				}
				else if (i != 0) {
					buf[i] = '\0';

					token = dict(buf);
					spisok = addlexeme(spisok, token, buf, row, column-i);

					i = 0;
				}
				else{
					buf[i] = sign;
					i++;
					column++;
					buf[i] = '\0';

					token = dict(buf);
					spisok = addlexeme(spisok, token, buf, row, column-i);

					i = 0;
					continue;
				}

			}
			//знаки в один символ
			else if (sign == ',' || sign == ';' || sign == '+' || sign == '-' ||
				sign == '=' || sign == '*' || sign == '\\' || sign == '^' ||
				sign == '(' || sign == ')') {
				
				if (i != 0) {
					buf[i] = '\0';

					token = dict(buf);
					spisok = addlexeme(spisok, token, buf, row, column-i);

					i = 0;
				}

				buf[i] = sign;
				i++;
				column++;
				buf[i] = '\0';

				token = dict(buf);
				spisok = addlexeme(spisok, token, buf, row, column-i);

				i = 0;
				continue;
			}

			else if (sign == '$') {
				buf[i] = sign;
				i++;
				column++;
				buf[i] = '\0';

				token = dict(buf);
				spisok = addlexeme(spisok, token, buf, row, column-i);

				i = 0;
				continue;
			}

			else if (sign == '?') {
				buf[i] = sign;
				i++;
				column++;
				if ((sign = fgetc(file)) == '>') {
					buf[i] = sign;
					i++;
					column++;
					buf[i] = '\0';

					token = dict(buf);
					spisok = addlexeme(spisok, token, buf, row, column-i);

					row++;
					i = 0;
					continue;
				}else {
					buf[i] = '\0';

					token = dict(buf);
					spisok = addlexeme(spisok, token, buf, row, column-i);

					i = 0;

					if (sign == ' ') {
						column++;
						continue;
					}
				}
			}

			else if (sign == '>') {
				if (i != 0) {
					buf[i] = '\0';

					token = dict(buf);
					spisok = addlexeme(spisok, token, buf, row, column-i);

					i = 0;
				}

				buf[i] = sign;
				i++;
				column++;

				if ((sign = fgetc(file)) == '=') {
					buf[i] = sign;
					i++;
					column++;
					buf[i] = '\0';

					token = dict(buf);
					spisok = addlexeme(spisok, token, buf, row, column-i);

					i = 0;
					continue;
				} else {
					buf[i] = '\0';

					token = dict(buf);
					spisok = addlexeme(spisok, token, buf, row, column-i);

					i = 0;

					if (sign == ' ') {
						column++;
						continue;
					}
				}
			}

			else if (sign == '<') {
				if (i != 0) {
					buf[i] = '\0';

					token = dict(buf);
					spisok = addlexeme(spisok, token, buf, row, column-i);

					i = 0;
				}
				buf[i] = sign;
				i++;
				column++;

				sign = fgetc(file);

				if ((sign == '=') || (sign == '>')) {
					buf[i] = sign;
					i++;
					column++;
					buf[i] = '\0';

					token = dict(buf);
					spisok = addlexeme(spisok, token, buf, row, column-i);

					i = 0;
					continue;
				} else if ((sign == '?')) {
					buf[i] = sign;
					i++;
					column++;
					while ((sign = fgetc(file)) != '\n'){
						buf[i] = sign;
						i++;
						column++;
						continue;
					}
					buf[i] = '\0';

					token = dict(buf);
					spisok = addlexeme(spisok, token, buf, row, column-i);

					row++;
					i = 0;
					continue;
				} else {
					buf[i] = '\0';

					token = dict(buf);
					spisok = addlexeme(spisok, token, buf, row, column-i);

					i = 0;

					if (sign == ' ') {
						column++;
						continue;
					}
				}
			}
			buf[i] = sign;
			i++;
			column++;
		}
		if (i != 0) {
			buf[i] = '\0';

			token = dict(buf);
			spisok = addlexeme(spisok, token, buf, row, column-i);

			i = 0;
		}
		spisok = addlexeme(spisok, "eof", "", row, column-i);
		
		fclose (file);
	
		return head;
	}
	return NULL;
}

void printtok(tokens *head) {
    tokens *print;
    print = head;
    while (print != NULL) {
        printf("Loc=<%d:%d> %s '%s'\n", print->row, print->column, print->token, print->lexeme);
        print = print->next;
    }
}
