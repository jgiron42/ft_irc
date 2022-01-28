//
// Created by joachim on 20/12/2021.
//

#ifndef FT_IRC_EXCEPTIONS_HPP
#define FT_IRC_EXCEPTIONS_HPP
#include <exception>

namespace ft_irc {

	class invalidSyntaxException :public std::exception {
	public:
		invalidSyntaxException() throw() {};
		virtual ~invalidSyntaxException() throw() {};
		const char * what() const  throw() {
			return ("syntax is invalid");
		}
	};
	class syntaxError : public std::exception {
	public:
		syntaxError() throw() {};
		virtual ~syntaxError() throw() {};
		const char * what() const  throw() {
			return ("syntax error");
		}
	};
	class argumentMissing : public std::exception {
	public:
		argumentMissing() throw() {};
		virtual ~argumentMissing() throw() {};
		const char * what() const  throw() {
			return ("missing argument");
		}
	};
}

#endif //FT_IRC_EXCEPTIONS_HPP
