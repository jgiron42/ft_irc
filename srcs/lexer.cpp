//     Made by lejulien 01/16/22

#include "../includes/command.hpp"

static void elem_parser(std::string str, int *i, std::list<struct block> &token) {
    block b;
    b.bloc_type = ELEM;
    if (str.find(">") == std::string::npos)
        return ;
    b.value = str.substr(0, str.find(">"));
    *i += str.find(">") + 1;
    token.push_back(b);
}

static void char_parser(std::string str, int *i, std::list<struct block> &token) {
    block b;
    b.bloc_type = CHAR;
    if (str.find("'") == std::string::npos)
        return ;
    b.value = str.substr(0, str.find("'"));
    *i += str.find("'") + 1;
    token.push_back(b);
}

static void string_parser(std::string str, int *i, std::list<struct block> &token) {
    block b;
    b.bloc_type = STR;
    if (str.find("\"") == std::string::npos)
        return ;
    b.value = str.substr(0, str.find("\""));
    *i += str.find("\"") + 1;
    token.push_back(b);
}

static void opt_start_parser(std::string str, int *i, std::list<struct block> &token) {
    block b;
    b.bloc_type = OPT;
    b.value = "";
    token.push_back(b);
}


static void or_parser(std::string str, int *i, std::list<struct block> &token) {
    block b;
    b.bloc_type = OR;
    b.value = "";
    token.push_back(b);
}

static void rep_start_parser(std::string str, int *i, std::list<struct block> &token) {
    block b;
    b.bloc_type = REP;
    b.value = "";
    token.push_back(b);
}

static void rep_end_parser(std::string str, int *i, std::list<struct block> &token) {
    block b;
    b.bloc_type = REPE;
    b.value = "";
    token.push_back(b);
}

static void opt_end_parser(std::string str, int *i, std::list<struct block> &token) {
    block b;
    b.bloc_type = OPTE;
    b.value = "";
    token.push_back(b);
}

std::list<struct block> &command::generate_token(std::string syntax) {
    std::list<struct block> token;
    int i = 0;

    std::string bnf = syntax;
    while (syntax[i] != '\0') {
		if (syntax[i] == '<')
			elem_parser(&syntax[i+1], &i, token);
		else if (syntax[i] == '[')
			opt_start_parser(&syntax[i+1], &i, token);
		else if (syntax[i] == '{')
			rep_start_parser(&syntax[i+1], &i, token);
		else if (syntax[i] == '"')
			string_parser(&syntax[i+1], &i, token);
		else if (syntax[i] == '\'')
			char_parser(&syntax[i+1], &i, token);
		else if (syntax[i] == '|')
			or_parser(&syntax[i+1], &i, token);
		if (syntax[i] == '}')
			rep_end_parser(&syntax[i+1], &i, token);
		else if (syntax[i] == ']')
			opt_end_parser(&syntax[i+1], &i, token);
		i++;
    }
    return token;
}

