# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gostroum <gostroum@student.42tokyo.jp>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/04 21:13:43 by gostroum          #+#    #+#              #
#    Updated: 2025/05/07 19:41:47 by gostroum         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = so_long

CC = cc
CFLAGS = -Wall -Wextra -Werror
MLXFLAGS = -I../minilibx-linux 
MLXLINK = -L../minilibx-linux -lmlx_Linux -lX11 -lXext -lXrender 
RM = rm -f

SOURCES = main.c utils.c loader.c render.c checker.c errors.c \
	ft_printf.c ft_printf_utils.c \
	get_next_line.c get_next_line_utils.c 

OBJECTS = $(SOURCES:.c=.o)

all: $(NAME)

$(NAME): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) $(MLXLINK) -o $(NAME) 

%.o: %.c
	$(CC) $(CFLAGS) $(MLXFLAGS) -c $< -o $@

clean:
	${RM} $(OBJECTS)

fclean: clean
	${RM} $(NAME)

re: fclean all

bonus: $(NAME)

.PHONY: all clean fclean re
