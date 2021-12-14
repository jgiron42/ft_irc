//
// Created by joachim on 14/12/2021.
//

#ifndef FT_IRC_T_TOKEN_HPP
#define FT_IRC_T_TOKEN_HPP
#include <list>
#include <string>
#include <stack>
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

template <class C>
class token_it{
public:
	typedef typename C::iterator iterator;
	typedef typename iterator::value_type value_type;
	typedef typename iterator::pointer pointer;
	typedef typename iterator::reference reference;
	typedef typename iterator::difference_type difference_type;
	typedef std::bidirectional_iterator_tag iterator_category;
	token_it() {}
	token_it(token_it const &src) : i(src.i), loop_begin(src.loop_begin) {}
	token_it(iterator const &src) : i(src), loop_begin() {}
	token_it &operator=(token_it const &src) {
		this->i = src.i;
		this->loop_begin = src.loop_begin;
		return (*this);
	}
	token_it &operator=(iterator const &src) {
		this->i = src;
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
		i = this->recursive_advance(++token_it(*this), c).i;
	}
	token_it &skip_loop()
	{
		int scope = 1;
		while (scope > 0)
		{
			if (this->i->bloc_type == REP || this->i->bloc_type == OPT)
				scope++;
			else if (this->i->bloc_type == REPE || this->i->bloc_type == OPTE)
				scope--;
			++*this;
		}
		return (*this);
	}
	friend bool operator==(const token_it &lhs, const token_it &rhs) {
		return (lhs.i == rhs.i);
	}
	friend bool operator!=(const token_it &lhs, const token_it &rhs) {
		return (lhs.i != rhs.i);
	}
private:
	iterator i;
	std::stack<token_it> loop_begin;
	token_it recursive_advance(token_it current, char c){
		token_it tmp;
		switch (current->bloc_type)
		{
			case CHAR:
				if (c != current->value[0])
					return (iterator(0));
				++*this;
				return (*this);
			case REP:
				tmp = recursive_advance(++token_it(current),c);
				if (tmp != iterator(0))
				{
					loop_begin.push(this->i);
					return (tmp);
				}
				return (recursive_advance(token_it(current).skip_loop().i,c));
			case REPE:
				tmp = recursive_advance(this->loop_begin.top(),c);
				if (tmp != iterator(0))
				{
					this->loop_begin.pop();
					return (tmp);
				}
				return (recursive_advance(++token_it(current),c));
			case OPT:
				tmp = recursive_advance(++token_it(current),c);
				if (tmp != iterator(0))
					return (tmp);
				return (recursive_advance(token_it(current).skip_loop().i,c));
			case OPTE:
				return (recursive_advance(++token_it(current),c));
			default:
			case ELEM:
				return (*this);
		}
	}
};



#endif //FT_IRC_T_TOKEN_HPP
