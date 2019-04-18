# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: akhossan <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/03/30 15:55:08 by akhossan          #+#    #+#              #
#    Updated: 2019/04/05 15:30:53 by akhossan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	libft.a

CFLAGS		=	-Werror -Wall -Wextra

SRC			=	$(wildcard *.c)

all:$(NAME)

$(NAME):
	gcc -c $(CFLAGS) -I. $(SRC)
	ar rc $(NAME) *.o
	ranlib $(NAME)

clean:
	/bin/rm -f *.o

fclean: clean
	/bin/rm -f $(NAME)

re: fclean all
