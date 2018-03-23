# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pfichepo <pfichepo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/03/21 10:28:45 by pfichepo          #+#    #+#              #
#    Updated: 2018/03/23 10:23:10 by pfichepo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_nm
CC = clang
CFLAGS = -O0 -g -Wall -Wextra -Werror -arch x86_64 -I ./includes
SRCS = 	ar.c \
		init.c \
		lib2.c \
		libs.c \
		libs2.c \
		lists.c \
		main.c \
		nm.c \
		sections.c \
		x64.c \
		x86.c \
		xfat.c \
		xfat2.c \
		libft.c

SRCF = ./srcs/nm/
OBJS = $(addprefix $(SRCF), $(SRCS:.c=.o))
	
all : $(NAME)

$(NAME): $(OBJS)
	@echo Compiling $(NAME) ...
	@$(CC) -o $(NAME) $(OBJS)
	

clean:
	@rm -f $(OBJS)

fclean: clean
	@rm -f $(NAME)

re: fclean all

start:
	./$(NAME)

.PHONY: clean fclean all re $(NAME) start