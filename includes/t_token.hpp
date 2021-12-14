//
// Created by joachim on 14/12/2021.
//

#ifndef FT_IRC_T_TOKEN_HPP
#define FT_IRC_T_TOKEN_HPP
#include <list>
#include <string>
#include "command.hpp"
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

class command;

template <template <typename> class C>
class token_it{
public:
	typedef typename C<block>::iterator iterator;
	typedef typename iterator::value_type value_type;
	typedef typename iterator::pointer pointer;
	typedef typename iterator::reference reference;
	typedef typename iterator::difference_type difference_type;
	typedef std::bidirectional_iterator_tag iterator_category;
	token_it() {}
	token_it(token_it const &src) : i(src.i) {}
	token_it &operator=(token_it const &src) {
		this->i = src.i;
		return (*this);
	}
	reference operator*() {
		return (*i);
	}
	pointer operator->() {
		return (i.operator->());
	}
	token_it &operator++() {
		++i;
		return (*this);
	}
	token_it operator++(int) {
		token_it tmp = *this;
		i++;
		return (tmp);
	}
	token_it &operator--() {
		--i;
		return (*this);
	}
	token_it operator--(int) {
		token_it tmp = *this;
		i--;
		return (tmp);
	}
	void advance(char c) {
		iterator next = *this;
		++next;
		switch (next->bloc_type)
		{
			case CHAR:
				if (c != next->value[0])
					throw command::argumentMissing();
				++*this;
				return;
			case REP:
				break;
			case REPE:
				break;
			case OPT:
				break;
			case OPTE:
				break;
			case ELEM:
				break;
		}
	}
private:
	iterator i;
	void recursive_advance(char c);
};


#endif //FT_IRC_T_TOKEN_HPP
