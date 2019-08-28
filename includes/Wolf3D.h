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

# define WIDTH	1280
# define HEIGHT	720
# define CENTER_X WIDTH / 2
# define CENTER_Y HEIGHT / 2

# define WALL_COLOR 0xA3F4FF
# define NUM_TEXTURES 3

typedef struct		s_object
{
	t_line			line;
	struct s_object	*next;
}					t_object;

typedef struct		s_wolf
{
	char			*map_path;
	t_gfx			*gfx;
	t_image			*image;
	t_map			*map;
	t_player		*player;
	t_input			*input;
	t_object		*objects;
	t_image			*textures[NUM_TEXTURES];
}					t_wolf;

typedef struct		s_ray_vars
{
	int				x;
	float			camera_x;
	float			dir_x;
	float			dir_y;
	int 			map_x;
	int				map_y;
	float			dist_x;
	float			dist_y;
	float			delta_dist_x;
	float			delta_dist_y;
	float			dist;
	int				step_x;
	int				step_y;
	int				hit;
	int				side;
	int				line_height;
	int				line_start;
	int				line_end;
}					t_ray_vars;

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

/*
**	texture.c
*/

t_image				*load_texture(char *texture_data, t_wolf *w);
void				load_all_textures(t_wolf *w);

// float				ray_march(t_wolf *w, t_xyz point, float angle, int color);

#endif
