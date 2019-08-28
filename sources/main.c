/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csinglet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/16 16:00:21 by csinglet          #+#    #+#             */
/*   Updated: 2019/03/16 16:00:22 by csinglet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "Wolf3D.h"

void			set_hooks(t_wolf *w)
{
	mlx_hook(w->gfx->win_ptr, 2, 0, toggle_key, w);
	mlx_hook(w->gfx->win_ptr, 3, 0, toggle_key, w);
	mlx_hook(w->gfx->win_ptr, 6, 0, mouse_motion, w);
}

int				shader(float distance, int color)
{
	int			new_color;
	int			r;
	int			g;
	int			b;

	new_color = 0;
	r = ((color >> 2 * 8) & 0xFF);
	g = ((color >> 1 * 8) & 0xFF);
	b = ((color >> 0 * 8) & 0xFF);
	distance *= 10;
	if (r > (int)((r / 0xFF) * distance))
		new_color |= (r - (int)((r / (float)0xFF) * distance)) << 2 * 8;
	if (g > (int)((g / 0xFF) * distance))
		new_color |= (g - (int)((g / (float)0xFF) * distance)) << 1 * 8;
	if (b > (int)((b / 0xFF) * distance))
		new_color |= (b - (int)((b / (float)0xFF) * distance)) << 0 * 8;
	return (new_color);
}

static void		init_variables(t_wolf *w, t_ray_vars *v)
{
	v->camera_x = 2 * v->x / (float)WIDTH - 1;
	v->dir_x = w->player->direction.x + w->player->camera.x * v->camera_x;
	v->dir_y = w->player->direction.y + w->player->camera.y * v->camera_x;
	v->map_x = w->player->where.x;
	v->map_y = w->player->where.y;
	v->delta_dist_x = fabs(1 / v->dir_x);
	v->delta_dist_y = fabs(1 / v->dir_y);
	v->hit = 0;
}

static void		determine_step_direction(t_wolf *w, t_ray_vars *v)
{
	if (v->dir_x < 0)
	{
		v->step_x = -1;
		v->dist_x = (w->player->where.x - v->map_x) * v->delta_dist_x;
	}
	else
	{
		v->step_x = 1;
		v->dist_x = (v->map_x + 1.0f - w->player->where.x) * v->delta_dist_x;
	}
	if (v->dir_y < 0)
	{
		v->step_y = -1;
		v->dist_y = (w->player->where.y - v->map_y) * v->delta_dist_y;
	}
	else
	{
		v->step_y = 1;
		v->dist_y = (v->map_y + 1.0f - w->player->where.y) * v->delta_dist_y;
	}
}

static void		dda(t_wolf *w, t_ray_vars *v)
{
	while (v->hit == 0)
	{
		if (v->dist_x < v->dist_y)
		{
			v->dist_x += v->delta_dist_x;
			v->map_x += v->step_x;
			v->side = 0;
		}
		else
		{
			v->dist_y += v->delta_dist_y;
			v->map_y += v->step_y;
			v->side = 1;
		}
		if (w->map->info[v->map_y][v->map_x] != 0)
			v->hit = 1;
	}
	if (v->side == 0)
		v->dist = (v->map_x - w->player->where.x + (1 - v->step_x)
			/ 2) / v->dir_x;
	else
		v->dist = (v->map_y - w->player->where.y + (1 - v->step_y)
			/ 2) / v->dir_y;
}

static void		draw_wall(t_wolf *w, t_ray_vars *v, int y)
{
	float	wall_x;
	int		d;
	int		tex_x;
	int		tex_y;
	int		texture_choice;

	if (v->side == 0)
		wall_x = w->player->where.y + v->dist * v->dir_y;
	else
		wall_x = w->player->where.x + v->dist * v->dir_x;
	wall_x -= floor(wall_x);
	tex_x = wall_x * 32;
	if ((v->side == 0 && v->dir_x > 0) || (v->side == 1 && v->dir_y < 0))
		tex_x = 32 - tex_x - 1;
	while (y < v->line_end)
	{
		d = y * 256 - HEIGHT * 128 + v->line_height * 128;
		tex_y = ((d * 32) / v->line_height) / 256;
		texture_choice = (abs(w->map->info[v->map_y][v->map_x] - 1)) % NUM_TEXTURES;
		pixel(w->image, v->x, y, shader(v->dist,
			w->textures[texture_choice]->buffer[tex_y * 32 + tex_x]));
		y++;
	}
}

void			*render(void *info)
{
	int			i;
	t_wolf		*w;
	t_ray_vars	v;

	w = ((t_thread *)info)->w;
	v.x = ((t_thread *)info)->x;
	while (v.x < WIDTH)
	{
		init_variables(w, &v);
		determine_step_direction(w, &v);
		dda(w, &v);
		v.line_height = (HEIGHT / v.dist);
		v.line_start = -v.line_height / 2 + HEIGHT / 2;
		v.line_end = v.line_height / 2 + HEIGHT / 2;
		if (v.line_start < 0)
			v.line_start = 0;
		if (v.line_end > HEIGHT)
			v.line_end = HEIGHT;
		line(w->image, (t_xyz){v.x, v.line_start, 0}, (t_xyz){v.x, 0, 0}, 0x447c80);
		line(w->image, (t_xyz){v.x, v.line_end, 0}, (t_xyz){v.x, HEIGHT, 0}, 0x2b2b2b);
		draw_wall(w, &v, v.line_start);
		v.x += NUMBER_OF_THREADS;
	}
	return (NULL);
}

int				draw_loop(t_wolf *w)
{
	int			i;
	pthread_t	threads[NUMBER_OF_THREADS];
	t_thread	params[NUMBER_OF_THREADS];

	i = -1;
	ft_bzero(w->image->buffer, WIDTH * HEIGHT * sizeof(int));
	mlx_clear_window(w->gfx->mlx_ptr, w->gfx->win_ptr);
	handle_input(w);
	while (++i < NUMBER_OF_THREADS)
	{
		params[i].w = w;
		params[i].x = i;
		if (pthread_create(&threads[i], NULL, render, &params[i]) != 0)
			ft_printf("Error\n");
	}
	i = -1;
	while (++i < NUMBER_OF_THREADS)
		pthread_join(threads[i], NULL);
	mlx_put_image_to_window(w->gfx->mlx_ptr, w->gfx->win_ptr, w->image->ptr, 0, 0);
	return (0);
}

void			set_player_position(t_wolf *w)
{
	int			y;
	int			x;

	y = -1;
	while (++y < w->map->height)
	{
		x = -1;
		while (++x < w->map->width)
		{
			if (w->map->info[y][x] == 0)
			{
				ft_printf("Setting player position at: (%d.5, %d.5)\n", x, y);
				w->player->where.x = x + 0.5f;
				w->player->where.y = y + 0.5f;
				return ;
			}
		}
	}
}

void			player_init(t_player *player)
{
	player->where.x = 0;
	player->where.y = 0;
	player->direction.x = -1;
	player->direction.y = 0;
	player->camera.x = 0.0f;
	player->camera.y = 1.0f;
}

void			start(char *file_path)
{
	t_wolf		w;
	t_gfx		gfx;
	t_input		input;
	t_player 	player;

	w.map_path = file_path;
	w.gfx = &gfx;
	w.input = &input;
	w.map = get_map(file_path);
	w.gfx->mlx_ptr = mlx_init();
	w.gfx->win_ptr = mlx_new_window(w.gfx->mlx_ptr, WIDTH, HEIGHT, "RayCaster");
	w.image = new_image(w.gfx->mlx_ptr, WIDTH, HEIGHT);
	player_init(&player);
	w.player = &player;
	set_player_position(&w);
	load_all_textures(&w);
	set_hooks(&w);
	mlx_do_key_autorepeatoff(w.gfx->mlx_ptr);
	mlx_loop_hook(w.gfx->mlx_ptr, draw_loop, &w);
	mlx_loop(w.gfx->mlx_ptr);
}

int				main(int argc, char *argv[])
{
	if (argc > 1)
		start(argv[1]);
	else
		ft_printf("usage: Wolf3D \"map\"");
	return (0);
}
