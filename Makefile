# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    mkaefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: chermist <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/05/04 18:07:03 by chermist          #+#    #+#              #
#    Updated: 2019/12/16 15:09:00 by chermist         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fractol

CC = gcc

INCDIR = -I minilibx_macos -I libft/includes -I inc

LIBDIR = -L minilibx_macos -L libft

LIB = -lft -lmlx

CFLAGS = -Wall -Werror -Wextra -Ofast $(INCDIR)

FW = -framework OpenGL -framework AppKit

LINUX_FLAGS = -I /usr/X11/include -g -L /usr/X11/lib -lmlx -lX11 -lXext

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

linux:
	@make -C libft/
	@make -C minilibx_linux/
	$(OBJ)
	$(CC) -I libft/includes -I inc -L libft $(LINUX_FLAGS) $(OBJ) -o $(NAME)

DEPS:
	@make -C libft/
	@make -C minilibx_macos/

%.o: %.c %.h

clean:
	make -C libft $@
	make -C minilibx_macos $@
	make -C minilibx_linux $@
	rm -f $(OBJ)

fclean: clean
	make -C libft $@
	rm -f $(NAME)

re: fclean all
