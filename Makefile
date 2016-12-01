# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kbensado <kbensado@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/01/21 02:48:50 by kbensado          #+#    #+#              #
#    Updated: 2016/11/15 09:18:41 by kbensado         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC =		gcc

NAME =		ft_ls

CFLAGS =	-Wall -Wextra -Werror

SRC =		main.c dir.c error.c file.c flag.c launch.c list.c list2.c list3.c macro.c macro2.c macro3.c macro4.c macro5.c macro6.c macro7.c print.c

OBJ =		$(SRC:.c=.o)

all:		$(NAME)

$(NAME):		$(OBJ)
			@make -C libft
			@make -C ft_printf
			@$(CC) $(CFLAGS) -I libft -c $(SRC)
			@$(CC) $(CFLAGS) -I ft_printf -c $(SRC)
			@$(CC) $(CFLAGS) -o $(NAME) $(OBJ) -L libft -lft -L ft_printf -lftprintf
			@echo ... Compilation of ft_ls DONE !

clean:
			@rm -rf $(OBJ)
			@make clean -C libft
			@make clean -C ft_printf
			@echo ... Objects clean in ft_ls !

fclean:		clean
			@rm -rf $(NAME)
			@make fclean -C libft
			@make fclean -C ft_printf
			@echo ... Name clean in ft_ls !

re:			fclean all
			@echo ... ft_ls retry !


.PHONY: all, re, fclean, clean
