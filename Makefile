# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: csinglet <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/01/22 18:59:57 by csinglet          #+#    #+#              #
#    Updated: 2019/02/08 14:35:41 by csinglet         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= Wolf3D

CC			= gcc
CFLAGS		= -Wall -Werror -Wextra -O3
FLAGS		= $(CFLAGS)

FILES		= main.c map.c ray_marching.c line.c circle.c image.c rotation.c matrix.c vector.c input.c

FRAMEWORKS	= -framework OpenGL -framework Appkit

ALL_FILES	= $(FILES) $(LX_FILES) $(CLINE_FILES) $(GLOB_FILES)

OBJ			= $(addprefix build/, $(ALL_FILES:.c=.o))

INC_FT		= -I srcs/libft/includes
LINK_FT		= -L srcs/libft -lft
FT			= $(INC_FT) $(LINK_FT)

INC_PF		= -I srcs/ft_printf/includes
LINK_PF		= -L srcs/ft_printf -lftprintf
PF			= $(INC_PF) $(LINK_PF)

INC_ST		= -I srcs/ft_structs/includes
LINK_ST		= -L srcs/ft_structs -lftstructs
ST			= $(INC_ST) $(LINK_ST)

INC_MLX		= -I srcs/minilibx
LINK_MLX	= -L srcs/minilibx -lmlx
MLX			= $(INC_MLX) $(LINK_MLX)

# INC_GFX		= -I srcs/libgfx/includes
# LINK_GFX	= -L srcs/libgfx -lgfx
# GFX			= $(INC_GFX) $(LINK_GFX)

LIBS		= $(FT) $(PF) $(ST) $(MLX) # $(GFX)
INC_LIBS	= $(INC_FT) $(INC_PF) $(INC_ST) $(INC_LX) $(INC_MLX) # $(INC_GFX)

all: $(NAME)

$(NAME): $(OBJ)
	@echo "Creating libmlx.a"
	@make -C srcs/minilibx
	@echo "Creating libft.a"
	@make -C srcs/libft
	@echo "Creating libftprintf.a"
	@make -C srcs/ft_printf
	@echo "Creating libftstructs.a"
	@make -C srcs/ft_structs
	@echo "Creating: $(NAME)"
	@$(CC) $(FLAGS) $(LIBS) $(FRAMEWORKS) -I includes $(OBJ) -o $@ -ltermcap

build:
	@echo "Creating build directory"
	@mkdir build

build/%.o: srcs/*/%.c | build
	@echo "  Building $@"
	@$(CC) $(INC_LIBS) -I includes -c $< -o $@

clean:
	@rm -fr build
	@make clean -C srcs/libft
	@make clean -C srcs/ft_printf
	@make clean -C srcs/ft_structs

fclean: clean
	@rm -f $(NAME)
	@make fclean -C srcs/libft
	@make fclean -C srcs/ft_printf
	@make fclean -C srcs/ft_structs

re: fclean all
