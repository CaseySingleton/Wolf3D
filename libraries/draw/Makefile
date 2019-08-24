# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: csinglet <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/01/22 18:59:57 by csinglet          #+#    #+#              #
#    Updated: 2018/11/09 23:25:49 by csinglet         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			= libdraw.a

CC				= gcc
CFLAGS			= -Wall -Werror -Wextra -O3
FLAGS			= $(CFLAGS)

FILES			= circle.c image.c line.c matrix.c rotation.c vector.c

SRC				= $(addprefix sources/, $(FILES))
OBJ				= $(addprefix build/, $(FILES:.c=.o))

all: $(NAME)

ft:
	@make -C libft
	@make re

test:
	@$(CC) $(FLAGS) main.c libftprintf.a $(NAME) -o printf -I includes

$(NAME): $(OBJ)
	@echo "Creating archive: $(NAME)"
	@ar rcs $(NAME) $(OBJ)

build:
	@echo "Creating build directory"
	@mkdir build

build/%.o: sources/%.c | build
	@echo "  Building $@"
	@$(CC) $(FLAGS) -I includes -c $< -o $@

clean:
	@rm -fr build

fclean: clean
	@rm -f $(NAME)

re: fclean all
