/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Wolf3D.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csinglet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/23 17:32:19 by csinglet          #+#    #+#             */
/*   Updated: 2019/08/30 17:20:38 by csinglet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_H
# define WOLF3D_H

# include <math.h>
# include <stdio.h>
# include <sys/time.h>
# include <fcntl.h>
# include <dirent.h>
# include <pthread.h>

# include "libft.h"
# include "get_next_line.h"
# include "ft_printf.h"
# include "draw.h"
# include "player.h"
# include "map.h"

# include "mlx.h"
# include "mlx_keys.h"

# define WIDTH	900
# define HEIGHT	600
# define CENTER_X WIDTH / 2
# define CENTER_Y HEIGHT / 2

# define WALL_COLOR 0xA3F4FF
# define NUM_TEXTURES 6

typedef struct		s_wolf
{
	void			*mlx_ptr;
	void			*win_ptr;
	int				front;
	t_image			*image[2];
	t_map			*map;
	t_player		*player;
	t_input			*input;
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
	int				d;
	int				tex_x;
	int				tex_y;
}					t_ray_vars;

typedef struct		s_thread
{
	t_wolf			*w;
	t_ray_vars		*v;
	int				x;
	int				y;
}					t_thread;

/*
**	render.c
*/

void				*render_scene(void *info);

/*
**	multithreading.c
*/

void				*render_threading(void *p);

/*
**	player.c
*/

void				set_player_position(t_wolf *w);
void				player_init(t_player *player);

/*
**	input.c
*/

int					handle_input(t_wolf *w);
int					toggle_key(int key, t_wolf *w);
int					mouse_motion(int x, int y, t_wolf *w);

/*
**	movement.c
*/

void				player_movement(t_wolf *w);
void				player_strafing(t_wolf *w);
void				player_rotation(t_wolf *w);

/*
**	texture.c
*/

int					shader(float distance, int color);
void				load_all_textures(t_wolf *w);
void				free_textures(t_wolf *w);

#endif
