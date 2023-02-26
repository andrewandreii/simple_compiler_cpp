#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

enum token_type {
	NUMBER_TOKEN, KEYWORD, ID_TOKEN, OPERATOR, END_OF_LINE
};
const char *token_type_names[] = { "number", "keyword", "id", "operator", "end_of_line" };

struct token {
	token_type type;
	char val[30];
};

const char *operators[] = { "=", "+", "-", "*", "/", "(", ")", NULL };
const int op_precedence[] = { 0, 1, 1, 2, 2, 10, 10 };
int is_operator(char *token) {
	for (int i = 0; operators[i] != 0; ++ i) {
		if (strcmp(token, operators[i]) == 0) {
			return 1;
		}
	}

	return 0;
}

int get_precedence(char *token) {
	for (int i = 0; operators[i] != 0; ++ i) {
		if (strcmp(token, operators[i]) == 0) {
			return op_precedence[i];
		}
	}

	return -1;
}

const char *keywords[] = { "int", "cout", NULL };
int is_keyword(char *token) {
	for (int i = 0; keywords[i] != NULL; ++ i) {
		if (strcmp(token, keywords[i]) == 0) {
			return 1;
		}
	}

	return 0;
}

void tokenize(char *line, token toks[]) {
	char *tok = strtok(line, " ");

	int i = 0;
	while (tok) {
		if (is_keyword(tok)) {
			toks[i].type = KEYWORD;
		} else if (is_operator(tok)) {
			toks[i].type = OPERATOR;
		} else if (strchr("-1234567890", tok[0]) != NULL) {
			toks[i].type = NUMBER_TOKEN;
		} else if ((tok[0] >= 'a' && tok[0] <= 'z') || (tok[0] >= 'A' && tok[0] <= 'Z') || tok[0] == '_') {
			toks[i].type = ID_TOKEN;
		} else {
			cout << "Error: Unknown token " << tok << '\n';
		}
		strcpy(toks[i].val, tok);

		++ i;
		tok = strtok(NULL, " ");
	}

	toks[i].type = END_OF_LINE;
}

void cout_token(token tok) {
	cout << '(' << token_type_names[tok.type] << ')' << tok.val << ' ';
}

int main() {
	ifstream fin("test.mylang");
	char line[500];
	token toks[30];

	while(!fin.eof()) {
		fin.getline(line, 500);
		cout << line << '\n';
		tokenize(line, toks);
		for (int i = 0; toks[i].type != END_OF_LINE; ++ i) {
			cout_token(toks[i]);
		}
		cout << '\n';
	}

	return 0;
}
