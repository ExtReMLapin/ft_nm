# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pfichepo <pfichepo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/03/21 10:28:45 by pfichepo          #+#    #+#              #
#    Updated: 2018/03/27 10:30:28 by pfichepo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME_NM = ft_nm
NAME_OTOOL = ft_otool

CC = clang
CFLAGS = -O0 -g -Wall -Wextra -Werror -I ./includes
SRCSNM 	= ar.c \
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

SRCSOTOOL	= ar.c \
		init.c \
		lib2.c \
		libs.c \
		libs2.c \
		lists.c \
		main.c \
		otool.c \
		x64.c \
		x86.c \
		xfat.c \
		xfat2.c \
		libft.c

SRCNM = ./srcs/nm/
OBJNM = $(addprefix $(SRCNM), $(SRCSNM:.c=.o))

SRCOTOOL = ./srcs/otool/
OBJOTOOL = $(addprefix $(SRCOTOOL), $(SRCSOTOOL:.c=.o))
	
all: $(NAME_NM) $(NAME_OTOOL)

$(NAME_NM): $(OBJNM)
	@echo Compiling $(NAME_NM) ...
	@$(CC) -o $(NAME_NM) $(OBJNM)
	
$(NAME_OTOOL): $(OBJOTOOL)
	@echo Compiling $(NAME_OTOOL) ...
	@$(CC) -o $(NAME_OTOOL) $(OBJOTOOL)

clean:
	@rm -f $(OBJNM)
	@rm -f $(OBJOTOOL)

fclean: clean
	@rm -f $(NAME_NM)
	@rm -f $(NAME_OTOOL)

re: fclean all

.PHONY: clean fclean all re $(NAME_NM) $(NAME_OTOOL)