# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    mkaefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: chermist <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/05/04 18:07:03 by chermist          #+#    #+#              #
#    Updated: 2019/10/31 16:38:34 by chermist         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fractol

CC = gcc

INCDIR = -I minilibx -I libft/includes -I inc

LIBDIR = -L minilibx -L libft

LIB = -lft -lmlx

CFLAGS = -Wall -Werror -Wextra $(INCDIR)

FW = -framework OpenGL -framework AppKit

SRCDIR = src

SRC =	main.c	\
		draw.c	\
		fractals.c	\
		bonus_fractals.c \
		events.c

OBJ = $(SRC:.c=.o)

vpath %.c $(SRCDIR)

all: DEPS $(NAME)

$(NAME): $(OBJ)
	$(CC) $(INCDIR) $(LIBDIR) $(LIB) $(FW) $(OBJ) -o $@

DEPS:
	@make -C libft/
	@make -C minilibx/

%.o: %.c %.h

clean:
	make -C libft $@
	make -C minilibx $@
	rm -f $(OBJ)

fclean: clean
	make -C libft $@
	rm -f $(NAME)

re: fclean all
