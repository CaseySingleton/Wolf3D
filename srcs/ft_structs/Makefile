# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: csinglet <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/01/22 18:59:57 by csinglet          #+#    #+#              #
#    Updated: 2019/02/02 15:45:29 by csinglet         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= libftstructs.a

CC		= gcc
CFLAGS	= -Wall -Werror -Wextra -O3
FLAGS	= $(CFLAGS)

FILES	= queue.c stack.c hash_table.c btree.c

OBJ	= $(addprefix build/, $(FILES:.c=.o))

all: $(NAME)

$(NAME): $(OBJ)
	@echo "Creating archive: $(NAME)"
	@ar rc $(NAME) $(OBJ)

build:
	@echo "Creating build directory"
	@mkdir build

build/%.o: srcs/%.c | build
	@echo "  Building $@"
	@$(CC) $(INC_FT) $(INC_PF) -I includes -c $< -o $@

clean:
	@rm -fr build

fclean: clean
	@rm -f $(NAME)

re: fclean all
