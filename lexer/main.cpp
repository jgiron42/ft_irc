/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lejulien <lejulien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/10 17:17:38 by lejulien          #+#    #+#             */
/*   Updated: 2021/09/24 17:36:12 by lejulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <list>
#include <string>
#include <iostream>
#include <utility>

// These define should be added

#ifndef TOKEN_UTILITY
#define TOKEN_UTILITY
#define ELEM 0
#define OPT  1
#define OPTE 2
#define REP  3
#define REPE 4
#define STR  5
#define CHAR 6
#define OR	 4
#endif

struct block {
	int bloc_type;
	std::string value;
};

// in the .hpp file

std::string block_enum_printer(block b)
{
	if (b.bloc_type == ELEM)
		return ("ELEM");
	else if (b.bloc_type == OPT)
		return ("OPT");
	else if (b.bloc_type == OPTE)
		return ("OPTE");
	else if (b.bloc_type == REP)
		return ("REP");
	else if (b.bloc_type == REPE)
		return ("REPE");
	else if (b.bloc_type == STR)
		return ("STR");
	else if (b.bloc_type == CHAR)
		return ("CHAR");
	else if (b.bloc_type == OR)
		return ("OR");

	return ("unknown");
}

void elem_parser(char *str, int *i, std::list<block> &token)
{
	block b;
	b.bloc_type = ELEM;
	std::string s(str);
	if (s.find(">") == std::string::npos)
		return ;
	b.value = s.substr(0, s.find(">"));
	*i += s.find(">") + 1;
	token.push_back(b);
}

void
	char_parser(char *str, int *i, std::list<block> &token)
{
	block b;
	b.bloc_type = CHAR;
	std::string s(str);
	if (s.find("'") == std::string::npos)
		return ;
	b.value = s.substr(0, s.find("'"));
	*i += s.find("'") + 1;
	token.push_back(b);
}

void
	string_parser(char *str, int *i, std::list<block> &token)
{
	block b;
	b.bloc_type = STR;
	std::string s(str);
	if (s.find("\"") == std::string::npos)
		return ;
	b.value = s.substr(0, s.find("\""));
	*i += s.find("\"") + 1;
	token.push_back(b);
}

void
	rep_start_parser(char *str, int *i, std::list<block> &token)
{
	block b;
	b.bloc_type = REP;
	b.value = "";
	token.push_back(b);
}

void
	opt_start_parser(char *str, int *i, std::list<block> &token)
{
	block b;
	b.bloc_type = OPT;
	b.value = "";
	token.push_back(b);
}

void
	or_parser(char *str, int *i, std::list<block> &token)
{
	block b;
	b.bloc_type = OR;
	b.value = "";
	token.push_back(b);
}

void
	rep_end_parser(char *str, int *i, std::list<block> &token)
{
	block b;
	b.bloc_type = REPE;
	b.value = "";
	token.push_back(b);
}

void
	opt_end_parser(char *str, int *i, std::list<block> &token)
{
	block b;
	b.bloc_type = OPTE;
	b.value = "";
	token.push_back(b);
}

// This function needs to be added in the command object \/

void
	add_block(std::list<block> &token, int bt, std::string val)
{
	block b;

	b.bloc_type = bt;
	b.value = val;
	token.push_back(b);
}

// only this one up there

void print(std::list<block> list)
{
    for (std::list<block>::iterator itra = list.begin(); itra != list.end(); itra++) {
        std::cout << "add_block(" << block_enum_printer(*itra) << ", \"" << itra->value << "\");" << std::endl;
    }
}

int
	main(int ac, char **av)
{
	std::list<block> token;
	int i = 0;

	if (ac != 2)
	{
		std::cout << "please enter a bnf syntax" << std::endl;
		return 1;
	}
	std::string bnf(av[1]);
	std::cout << "received bnf : " << bnf << std::endl;
	while (av[1][i] != '\0')
	{
		if (av[1][i] == '<')
			elem_parser(&av[1][i+1], &i, token);
		else if (av[1][i] == '[')
			opt_start_parser(&av[1][i+1], &i, token);
		else if (av[1][i] == '{')
			rep_start_parser(&av[1][i+1], &i, token);
		else if (av[1][i] == '"')
			string_parser(&av[1][i+1], &i, token);
		else if (av[1][i] == '\'')
			char_parser(&av[1][i+1], &i, token);
		else if (av[1][i] == '|')
			or_parser(&av[1][i+1], &i, token);
		if (av[1][i] == '}')
			rep_end_parser(&av[1][i+1], &i, token);
		else if (av[1][i] == ']')
			opt_end_parser(&av[1][i+1], &i, token);
		i++;
	}
	print(token);
	//delete token;
	return 0;
}
