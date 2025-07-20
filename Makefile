# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gostroum <gostroum@student.42tokyo.jp>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/04 21:13:43 by gostroum          #+#    #+#              #
#    Updated: 2025/07/20 17:21:19 by gostroum         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = so_long

CC = cc
CFLAGS = -Wall -Wextra -Werror
MLX_DIR = minilibx-linux
MLXFLAGS = -I$(MLX_DIR) 
MLXLINK = -L$(MLX_DIR) -lmlx_Linux -lX11 -lXext
RM = rm -f

SOURCES = main.c utils.c loader.c render.c checker.c errors.c \
	ft_printf.c ft_printf_utils.c \
	get_next_line.c get_next_line_utils.c 

OBJECTS = $(SOURCES:.c=.o)

all: $(NAME)

mlx:
	wget https://cdn.intra.42.fr/document/document/35296/minilibx-linux.tgz -O minilibx-linux.tgz
	tar -xzf minilibx-linux.tgz
	make -C $(MLX_DIR)
	touch mlx

$(NAME): mlx $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) $(MLXLINK) -o $(NAME) 

%.o: %.c
	$(CC) $(CFLAGS) $(MLXFLAGS) -c $< -o $@

clean:
	${RM} $(OBJECTS)
	rm -rf minilibx-linux*
	rm mlx

fclean: clean
	${RM} $(NAME)

re: fclean all

bonus: $(NAME)

.PHONY: all clean fclean re
