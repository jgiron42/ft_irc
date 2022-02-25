//
// Created by frtalleu on 2/22/22.
//

#ifndef FT_IRC_WHO_HPP
#define FT_IRC_WHO_HPP


#include "command.hpp"

class who_command : public command {
public:
    list_command(class client &c, class server &s) : command(c, s) {
        this->name = "WHO";
        this->syntax = "[ <nom> [ <o> ] ]";
        generate_token(std::string(syntax));
    };

    void execute() {

    };
};


#endif //FT_IRC_WHO_HPP
