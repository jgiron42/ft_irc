# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lejulien <lejulien@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/03/05 13:10:44 by lejulien          #+#    #+#              #
#    Updated: 2021/09/27 22:38:18 by user42           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS	 	=	./srcs/main.cpp		\
				./srcs/Server.cpp	\
				./srcs/channel.cpp	\
				./srcs/client.cpp	\
				./srcs/command.cpp	\
				./srcs/numerics.cpp	\
				./srcs/parsing_message.cpp \
				./srcs/utils.cpp

NAME		=	ircserv

FLAGS		=	 -Wall -Wextra -Werror -std=c++98 -g3
#FLAGS		=	 -std=c++98 -g3 -fsanitize=address

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
	$(COMPILER) $(FLAGS) -c $<  -o $(<:.cpp=.o) -I includes -I srcs/commands

.PHONY:	clean fclean re
