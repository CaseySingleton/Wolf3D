/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Wolf3D.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csinglet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/23 17:32:19 by csinglet          #+#    #+#             */
/*   Updated: 2019/02/23 17:32:20 by csinglet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_H
# define WOLF3D_H

# include <math.h>
# include <stdio.h>
# include <fcntl.h>

# include "libft.h"
# include "get_next_line.h"
# include "ft_printf.h"
# include "draw.h"
# include "player.h"
# include "map.h"

# include "mlx.h"
# include "mlx_keys.h"

# define WIDTH	1600
# define HEIGHT	900
# define MINI_MAP_SIZE WIDTH / 6
# define CENTER_X WIDTH / 2
# define CENTER_Y HEIGHT / 2

# define SKY_COLOR 0xBDFCFF
# define WALL_COLOR_1 0xFFE6BE
# define WALL_COLOR_2 0xBAFFDB
# define FLOOR_COLOR 0x918D87

typedef struct		s_object
{
	t_line			line;
	struct s_object	*next;
}					t_object;

typedef struct		s_wolf
{
	t_gfx			*gfx;
	t_image			*image;
	t_map			*map;
	t_player		*player;
	t_input			*input;
	t_object		*objects;
}					t_wolf;

typedef struct		s_thread
{
	t_wolf			*w;
	int				x;
}					t_thread;

/*
**	input.c
*/

int					toggle_key(int key, t_wolf *w);
int					handle_input(t_wolf *w);
int					mouse_motion(int x, int y, t_wolf *w);

/*
**	ray_marching.c
*/

// float				ray_march(t_wolf *w, t_xyz point, float angle, int color);

#endif
