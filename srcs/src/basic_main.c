/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csinglet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/16 20:41:29 by csinglet          #+#    #+#             */
/*   Updated: 2019/03/16 20:41:30 by csinglet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Wolf3D.h"

int				draw_loop(t_wolf *w)
{
	float	xRatio = WIDTH / (w->map->width + 1) / 4;
	float	yRatio = HEIGHT / (w->map->height + 1) / 4;

	ft_bzero(w->image->buffer, WIDTH * HEIGHT * sizeof(int));
	mlx_clear_window(w->gfx->mlx_ptr, w->gfx->win_ptr);
	handle_input(w);

	// printf("Player: (%f, %f)\n", w->player->where.x, w->player->where.y);
	for (int x = 0; x < WIDTH; x++)
	{
		float	camera;
		t_xyz	ray;
		int		step_x;
		int		step_y;
		float	delta_dist_x;
		float	delta_dist_y;
		float	side_dist_x;
		float	side_dist_y;
		float	perp_wall_dist;
		int		map_x;
		int		map_y;
		int		side;
		float	line_height;
		int		draw_start;
		int		draw_end;
	
		camera = 2 * (float)x / (float)WIDTH - 1;
		ray.x = w->player->direction.x + w->player->camera.x * camera;
		ray.y = w->player->direction.y + w->player->camera.y * camera;
		delta_dist_x = (int)fabs(1 / ray.x);
		delta_dist_y = (int)fabs(1 / ray.y);
		map_x = w->player->where.x;
		map_y = w->player->where.y;
		if (ray.x < 0)
		{
			step_x = -1;
			side_dist_x = (w->player->where.x - map_x) * delta_dist_x;
		}
		else
		{
			step_x = 1;
			side_dist_x = (map_x + 1 - w->player->where.x) * delta_dist_x;
		}
		if (ray.x < 0)
		{
			step_y = -1;
			side_dist_y = (w->player->where.y - map_y) * delta_dist_y;
		}
		else
		{
			step_y = 1;
			side_dist_y = (map_y + 1 - w->player->where.y) * delta_dist_y;
		}
		// printf("side_dist_x: %f\n", side_dist_x);
		// printf("side_dist_y: %f\n", side_dist_y);
		while (1)
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
				// printf("w->map->info[%d][%d]: %d\n", map_y / w->map->height, map_x / w->map->width, w->map->info[map_y / w->map->height][map_x / w->map->width]);
				break ;
			}
		}
		if (side == 0)
		{
			perp_wall_dist = (map_x - w->player->where.x + (1 - step_x) / 2) / ray.x;
		}
		else
		{
			perp_wall_dist = (map_y - w->player->where.y + (1 - step_y) / 2) / ray.y;
		}
		// printf("perp_wall_dist: %f\n", perp_wall_dist);
		line_height = HEIGHT / perp_wall_dist;
		// printf("line_height: %f\n", line_height);
		draw_start = -line_height / 2 + HEIGHT / 2;
		draw_start = draw_start < 0 ? 0 : draw_start;
		draw_end = line_height / 2 + HEIGHT / 2;
		draw_end = draw_end > HEIGHT ? HEIGHT - 1 : draw_end;
		// printf("draw_start: %d, draw_end: %d\n", draw_start, draw_end);
		line(w->image, (t_xyz){x, draw_start, 0}, (t_xyz){x, 0, 0}, 0x1102aa);
		line(w->image, (t_xyz){x, draw_start, 0}, (t_xyz){x, draw_end, 0}, 0xFF0FFF);
		line(w->image, (t_xyz){x, draw_end, 0}, (t_xyz){x, HEIGHT - 1, 0}, 0x333333);
	}
	mlx_put_image_to_window(w->gfx->mlx_ptr, w->gfx->win_ptr, w->image->ptr, 0, 0);
	return (0);
}

void			set_hooks(t_wolf *w)
{
	mlx_hook(w->gfx->win_ptr, 2, 0, toggle_key, w);
	mlx_hook(w->gfx->win_ptr, 3, 0, toggle_key, w);
	mlx_hook(w->gfx->win_ptr, 6, 0, mouse_motion, w);
}

void			start(char *file_path)
{
	t_wolf		w;
	t_gfx		gfx;
	t_map		map;
	t_input		input;
	t_player 	player;

	w.gfx = &gfx;
	w.gfx->mlx_ptr = mlx_init();
	w.gfx->win_ptr = mlx_new_window(w.gfx->mlx_ptr, WIDTH, HEIGHT, "RayCaster");

	w.map = &map;
	w.map = get_map(file_path);

	w.image = new_image(w.gfx->mlx_ptr, w.gfx->win_ptr, WIDTH, HEIGHT);

	w.input = &input;

	w.player = &player;
	w.player->where.x = w.map->width / 2;
	w.player->where.y = w.map->height / 2;
	printf("where: (%f, %f)\n", w.player->where.x, w.player->where.y);
	w.player->direction.x = -1.0f;
	w.player->direction.y = 0.0f;
	w.player->camera.x = 0.0f;
	w.player->camera.y = 1.00f;
	w.player->angle = M_PI;

	// printf("cos: %f, sin: %f\n", cos(w.player->angle), round(sin(w.player->angle)));

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
