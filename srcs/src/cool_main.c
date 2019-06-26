/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csinglet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 17:35:32 by csinglet          #+#    #+#             */
/*   Updated: 2019/03/14 17:35:33 by csinglet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Wolf3D.h"

#include <stdio.h>

void		draw_map(t_wolf *wolf)
{
	t_map	*map = wolf->map;
	t_image	*image = wolf->image;
	t_xyz t1;
	t_xyz t2;

	for (int y = 0; y < map->height; y++)
	{
		for (int x = 0; x < map->width; x++)
		{
			if (map->info[y][x] == 0)
				continue ;
			if (x + 1 < map->width && map->info[y][x + 1] > 0)
			{
				t1 = map->vmap[y][x];
				t2 = map->vmap[y][x + 1];
				draw_line_to_image(image, (t_xyz){t1.x, t1.y + 10, 0}, (t_xyz){t2.x, t2.y + 10, 0}, 0xFFFFFF);
				draw_line_to_image(image, (t_xyz){t1.x, t1.y - 10, 0}, (t_xyz){t2.x, t2.y - 10, 0}, 0xFFFFFF);
				draw_line_to_image(image, (t_xyz){t1.x, t1.y + 10, 0}, (t_xyz){t1.x, t1.y - 10, 0}, 0xFFFFFF);
				draw_line_to_image(image, (t_xyz){t2.x, t2.y + 10, 0}, (t_xyz){t2.x, t2.y - 10, 0}, 0xFFFFFF);
			}
			if (y + 1 < map->height && map->info[y + 1][x] > 0)
			{
				t1 = map->vmap[y][x];
				t2 = map->vmap[y + 1][x];
				draw_line_to_image(image, (t_xyz){t1.x, t1.y + 10, 0}, (t_xyz){t2.x, t2.y + 10, 0}, 0xFFFFFF);
				draw_line_to_image(image, (t_xyz){t1.x, t1.y - 10, 0}, (t_xyz){t2.x, t2.y - 10, 0}, 0xFFFFFF);
				draw_line_to_image(image, (t_xyz){t1.x, t1.y + 10, 0}, (t_xyz){t1.x, t1.y - 10, 0}, 0xFFFFFF);
				draw_line_to_image(image, (t_xyz){t2.x, t2.y + 10, 0}, (t_xyz){t2.x, t2.y - 10, 0}, 0xFFFFFF);
			}
		}
	}
}

void		map_set_scale(t_map *m)
{
	float	scale;
	ft_printf("HEIGHT: %d, map->height: %d\n", HEIGHT, m->height);
	ft_printf("HEIGHT / map->height: %d\n", HEIGHT / m->height);
	scale = MIN(HEIGHT / m->height, WIDTH / m->width);
	scale_vmap(m, scale, scale, scale);
}

void		map_to_center(t_map *m)
{
	translate_vmap(m, WIDTH / 2, HEIGHT / 2, 0);
}

void		check_keys(t_wolf *wolf)
{
	if (wolf->input->keys[KEY_ESCAPE])
	{
		ft_printf("Exiting Wolf3D\n");
		exit(0);
	}
	if (wolf->input->keys[KEY_A] || wolf->input->keys[KEY_D])
	{
		float angle = (wolf->input->keys[KEY_A]) ? 0.03 : -0.03;
		wolf->player->angle += angle;
		rotate_vmap_around_point(wolf->map, &(wolf->player->position), angle);
	}
	if (wolf->input->keys[KEY_W] || wolf->input->keys[KEY_S])
		translate_vmap(wolf->map, 0, wolf->input->keys[KEY_W] ? wolf->player->speed : -1, 0);
	if (wolf->input->keys[KEY_Q] || wolf->input->keys[KEY_E])
		translate_vmap(wolf->map, wolf->input->keys[KEY_Q] ? 2 : -2, 0, 0);
	if (wolf->input->keys[KEY_LEFT_SHIFT] == 1)
		wolf->player->speed = 4;
	if (wolf->input->keys[KEY_LEFT_SHIFT] == 0)
		wolf->player->speed = 2;
}

int			draw_loop(t_wolf *wolf)
{
	ft_bzero(wolf->image->buffer, WIDTH * HEIGHT * sizeof(int));
	check_keys(wolf);
	t_xyz	p1 = {WIDTH / 2, HEIGHT / 2};
	t_xyz	p2 = {WIDTH / 2, HEIGHT / 2 - 10};
	t_xyz	t1 = {wolf->cp1.x, 0};
	t_xyz	t2 = {wolf->cp2.x, 0};
	draw_line_to_image(wolf->image, p1, p2, 0x00FF00);
	// draw_line_to_image(wolf->image, wolf->cp1, p1, 0xFFFFFF);
	// draw_line_to_image(wolf->image, wolf->cp2, p1, 0xFFFFFF);
	// draw_line_to_image(wolf->image, wolf->cp1, t1, 0xFFFFFF);
	// draw_line_to_image(wolf->image, wolf->cp2, t2, 0xFFFFFF);
	draw_pixel_to_image(wolf->image, WIDTH / 2, HEIGHT / 2, 0xFF0000);
	draw_pixel_to_image(wolf->image, wolf->cp1.x, wolf->cp1.y, 0x00FF00);
	draw_pixel_to_image(wolf->image, wolf->cp2.x, wolf->cp2.y, 0x00FF00);

	draw_map(wolf);

	mlx_put_image_to_window(wolf->gfx->mlx_ptr, wolf->gfx->win_ptr, wolf->image->ptr, 0, 0);
	return (0);
}

int			main(int argc, char *argv[])
{
	t_wolf	wolf;
	t_gfx	gfx;
	t_map	map;
	t_input	input;
	t_player player;
	int		key;
	int		bpp;
	int		image_length;
	int		endian;

	ft_bzero(&wolf, sizeof(t_wolf));
	ft_bzero(&input, sizeof(t_input));
	wolf.gfx = &gfx;
	wolf.map = &map;
	wolf.input = &input;
	wolf.player = &player;
	wolf.gfx->mlx_ptr = mlx_init();
	wolf.gfx->win_ptr = mlx_new_window(wolf.gfx->mlx_ptr, WIDTH, HEIGHT, "(0.0?)");
	wolf.image = new_image(wolf.gfx->mlx_ptr, wolf.gfx->win_ptr, WIDTH, HEIGHT);
	wolf.map = map_init();
	wolf.map = get_map(argv[1]);
	wolf.map->vmap = get_vmap(wolf.map);
	map_set_scale(wolf.map);
	map_to_center(wolf.map);

	// Angle for rotation
	player.angle = 0;
	// Wall coordinates

	// Player coordinates
	player.position.x = WIDTH / 2;
	player.position.y = HEIGHT / 2;
	player.position.z = 0;

	wolf.cp1.x = WIDTH / 2 + 30;
	wolf.cp1.y = HEIGHT / 2 - 15;
	wolf.cp2.x = WIDTH / 2 - 30;
	wolf.cp2.y = HEIGHT / 2 - 15;

	mlx_do_key_autorepeatoff(wolf.gfx->mlx_ptr);
	mlx_hook(wolf.gfx->win_ptr, 3, 0, toggle_key, &wolf);
	mlx_hook(wolf.gfx->win_ptr, 2, 0, toggle_key, &wolf);
	mlx_loop_hook(gfx.mlx_ptr, draw_loop, &wolf);
	mlx_loop(gfx.mlx_ptr);
	return (0);
}
