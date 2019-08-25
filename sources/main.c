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

void			dda(t_wolf *w)
{

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
	distance *= 6;
	if (r > (int)((r / 0xFF) * distance))
		new_color |= (r - (int)((r / (float)0xFF) * distance)) << 2 * 8;
	if (g > (int)((g / 0xFF) * distance))
		new_color |= (g - (int)((g / (float)0xFF) * distance)) << 1 * 8;
	if (b > (int)((b / 0xFF) * distance))
		new_color |= (b - (int)((b / (float)0xFF) * distance)) << 0 * 8;
	return (new_color);
}

void			*render(void *info)
{
	t_wolf		*w;
	int			x;
	float		camera_x;
	float		ray_dir_x;
	float		ray_dir_y;

	w = ((t_thread *)info)->w;
	x = ((t_thread *)info)->x;
	while (x < WIDTH)
	{
		camera_x = 2 * x / (float)WIDTH - 1;
		ray_dir_x = w->player->direction.x + w->player->camera.x * camera_x;
		ray_dir_y = w->player->direction.y + w->player->camera.y * camera_x;
		
		int 	map_x;
		int		map_y;
		float	side_dist_x;
		float	side_dist_y;
		float	delta_dist_x;
		float	delta_dist_y;
		float	perp_wall_dist;
		int		step_x;
		int		step_y;
		int		hit;
		int		side;
		int		line_height;
		int		line_start;
		int		line_end;

		map_x = w->player->where.x;
		map_y = w->player->where.y;
		delta_dist_x = fabs(1 / ray_dir_x);
		delta_dist_y = fabs(1 / ray_dir_y);
		hit = 0;
		if (ray_dir_x < 0)
		{
			step_x = -1;
			side_dist_x = (w->player->where.x - map_x) * delta_dist_x;
		}
		else
		{
			step_x = 1;
			side_dist_x = (map_x + 1.0f - w->player->where.x) * delta_dist_x;
		}
		if (ray_dir_y < 0)
		{
			step_y = -1;
			side_dist_y = (w->player->where.y - map_y) * delta_dist_y;
		}
		else
		{
			step_y = 1;
			side_dist_y = (map_y + 1.0f - w->player->where.y) * delta_dist_y;
		}
		// DDA
		while (hit == 0)
		{
			if (side_dist_x < side_dist_y)
			{
				side_dist_x += delta_dist_x;
				map_x += step_x;
				side = 0;
			}
			else
			{
				side_dist_y += delta_dist_y;
				map_y += step_y;
				side = 1;
			}
			if (w->map->info[map_y][map_x] > 0)
			{
				hit = 1;
			}
		}
		// Determine distance to wall
		if (side == 0)
		{
			perp_wall_dist = (map_x - w->player->where.x + (1 - step_x) / 2) / ray_dir_x;
		}
		else
		{
			perp_wall_dist = (map_y - w->player->where.y + (1 - step_y) / 2) / ray_dir_y;
		}
		line_height = (HEIGHT / perp_wall_dist);
		line_start = -line_height / 2 + HEIGHT / 2;
		line_end = line_height / 2 + HEIGHT / 2;
		if (line_start < 0)
		{
			line_start = 0;
		}
		if (line_end > HEIGHT)
		{
			line_end = HEIGHT;
		}
		line(w->image, (t_xyz){x, line_start, 0}, (t_xyz){x, 0, 0}, SKY_COLOR);
		line(w->image, (t_xyz){x, line_start, 0}, (t_xyz){x, line_end, 0}, shader(perp_wall_dist, WALL_COLOR_1));
		line(w->image, (t_xyz){x, line_end, 0}, (t_xyz){x, HEIGHT, 0}, FLOOR_COLOR);
		x += NUMBER_OF_THREADS;
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
		{
			ft_printf("Error\n");
			return (1);
		}
	}
	i = -1;
	while (++i < NUMBER_OF_THREADS)
	{
		pthread_join(threads[i], NULL);
	}
	mlx_put_image_to_window(w->gfx->mlx_ptr, w->gfx->win_ptr, w->image->ptr, 0, 0);
	return (0);
}

void			set_player_position(t_player *player, t_map *map)
{
	int			y;
	int			x;

	y = -1;
	while (++y < map->height)
	{
		x = -1;
		while (++x < map->width)
		{
			if (map->info[y][x] == 0)
			{
				player->where.x = x;
				player->where.y = y;
				ft_printf("x: %d, y: %d\n", x, y);
				return ;
			}
		}
	}
}

void			player_init(t_player *player)
{
	player->where.x = 5;
	player->where.y = 5;
	player->direction.x = -1;
	player->direction.y = 0;
	player->camera.x = 0.0f;
	player->camera.y = 1.0f;
	player->vertical_offset = 0;
}

// Trying to set player position at a valid location

void			start(char *file_path)
{
	t_wolf		w;
	t_gfx		gfx;
	t_map		map;
	t_input		input;
	t_player 	player;

	w.gfx = &gfx;
	w.input = &input;
	w.map = get_map(file_path);
	w.gfx->mlx_ptr = mlx_init();
	w.gfx->win_ptr = mlx_new_window(w.gfx->mlx_ptr, WIDTH, HEIGHT, "RayCaster");
	w.image = new_image(w.gfx->mlx_ptr, WIDTH, HEIGHT);

	player_init(&player);
	set_player_position(&player, &map);
	w.player = &player;

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
