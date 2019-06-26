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

void			draw_map(t_wolf *w)
{
	t_xyz		t1;
	t_xyz		t2;

	for (int y = 0; y < w->map->height; y++)
	{
		for (int x = 0; x < w->map->width; x++)
		{
			if (w->map->info[y][x] == 0)
				continue ;
			t1 = w->map->vmap[y][x];
			vector_translate(&t1, CENTER_X, CENTER_Y, 0);
			if (x + 1 < w->map->width && w->map->info[y][x + 1] > 0)
			{
				t2 = w->map->vmap[y][x + 1];
				vector_translate(&t2, CENTER_X, CENTER_Y, 0);
				line(w->image, t1, t2, 0xFFFFFF);
			}
			if (y + 1 < w->map->height && w->map->info[y + 1][x] > 0)
			{
				t2 = w->map->vmap[y + 1][x];
				vector_translate(&t2, CENTER_X, CENTER_Y, 0);
				line(w->image, t1, t2, 0xFFFFFF);
			}
		}

	}
}

int				draw_loop(t_wolf *w)
{
	handle_input(w);
	ft_bzero(w->image->buffer, WIDTH * HEIGHT * sizeof(int));
	mlx_clear_window(w->gfx->mlx_ptr, w->gfx->win_ptr);
	draw_map(w);
	circle(w->image, (t_xyz){w->player->px, w->player->py, 0}, 10, 0x00FF00);
	line(w->image, (t_xyz){w->player->px, w->player->py, 0}, (t_xyz){w->player->px + cos(w->player->angle) * 15, w->player->py + sin(w->player->angle) * 15, 0}, 0xFFFF00);
	mlx_put_image_to_window(w->gfx->mlx_ptr, w->gfx->win_ptr, w->image->ptr, 0, 0);
	return (0);
}

void			set_hooks(t_wolf *w)
{
	mlx_hook(w->gfx->win_ptr, 2, 0, toggle_key, w);
	mlx_hook(w->gfx->win_ptr, 3, 0, toggle_key, w);
}

void		map_set_scale(t_map *m)
{
	float	scale;

	scale = MIN(HEIGHT / m->height, WIDTH / m->width);
	scale_vmap(m, scale, scale, 0);
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
	w.gfx->win_ptr = mlx_new_window(w.gfx->mlx_ptr, WIDTH, HEIGHT, "Wolf3D");

	w.map = &map;
	w.map = get_map(file_path);
	map_set_scale(w.map);

	w.image = new_image(w.gfx->mlx_ptr, w.gfx->win_ptr, WIDTH, HEIGHT);

	w.input = &input;

	w.player = &player;
	w.player->px = CENTER_X / w.map->width;
	w.player->py = CENTER_Y / w.map->height;
	w.player->angle = 0;
	w.player->y_position = 0;

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
