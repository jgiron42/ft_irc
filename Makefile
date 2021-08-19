# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lejulien <lejulien@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/03/05 13:10:44 by lejulien          #+#    #+#              #
#    Updated: 2021/08/20 00:53:35 by lejulien         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS	 	=	./srcs/main.cpp		\
				./srcs/Server.cpp	\
				./srcs/channel.cpp	\
				./srcs/client.cpp

NAME		=	ircserv

#FLAGS		=	 -Wall -Wextra -Werror -std=c++98
FLAGS		=	 -std=c++98

OBJS		=	$(SRCS:.cpp=.o)

COMPILER = clang++

all:	$(NAME)

$(NAME):	$(OBJS)
	$(COMPILER) -o $(NAME) $(FLAGS) $(OBJS)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.cpp.o:
	$(COMPILER) $(FLAGS) -c $<  -o $(<:.cpp=.o) -I includes

.PHONY:	clean fclean re
