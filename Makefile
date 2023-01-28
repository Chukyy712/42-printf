# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: brcaetan <brcaetan@42lisboa.com>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/06 18:20:40 by brcaetan          #+#    #+#              #
#    Updated: 2023/01/27 22:28:37 by brcaetan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=		libftprintf.a

CC		=		cc

CFLAGS	=		-Wall -Wextra -Werror

RM		=		rm -f

SRC 	=		ft_printf.c

OBJ		=		$(SRC:.c=.o)

all:			$(NAME)

$(NAME):		$(OBJ)
		ar rcs	$(NAME) $(OBJ)

clean:
				$(RM) $(OBJ)

fclean: clean
				$(RM) $(NAME)

re:		fclean	$(NAME)