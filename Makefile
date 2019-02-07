# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vbrovenk <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/01/27 16:58:12 by vbrovenk          #+#    #+#              #
#    Updated: 2019/01/27 16:58:13 by vbrovenk         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fractol
INCLUDE = fractol.h
LIBFT_INC = ./libft/includes
LIBFT = libft/libft.a
SRC =	main.c \
		mandelbrot.c

OBJ = $(SRC:.c=.o)
MLX_FLAGS = -lmlx -framework OpenGL -framework AppKit

#UBUNTU_FLAGS = -lm -lmlx -lXext -lX11 -L minilibx -I minilibx
# CFLAGS = -Wall -Wextra -Werror

OFF=\033[0m

RED=\033[31m
REDBOLD=\033[1;31m
GREEN=\033[32m
GREENBOLD=\033[1;32m
YELLOW=\033[33m
YELLOWBOLD=\033[1;33m
PURPLE=\033[35m
PURPLEBOLD=\033[1;35m

all: $(NAME)

$(NAME): $(OBJ)
	@make -C libft/
	@gcc $(OBJ) $(LIBFT) $(MLX_FLAGS) -o $(NAME) -lpthread
	@echo "$(PURPLEBOLD)fractol$(OFF)$(PURPLE) is ready"

%.o: %.c $(INCLUDE)
	@gcc -c $< -o $@ -I $(LIBFT_INC)

clean:
	@make clean -C libft
	@rm -rf $(OBJ)

fclean: clean
	@make fclean -C libft
	@rm -rf $(NAME)

re: fclean all