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

int				draw_loop(t_wolf *w)
{
	t_object	*temp;
	t_xyz		ray;

	ft_bzero(w->image->buffer, WIDTH * HEIGHT * sizeof(int));
	mlx_clear_window(w->gfx->mlx_ptr, w->gfx->win_ptr);
	handle_input(w);
	circle(w->image, w->player->where, 10, 0xFFFFFF);
	t_xyz p;
	p.x = w->player->where.x + cos(w->player->angle) * 12;
	p.y = w->player->where.y + sin(w->player->angle) * 12;
	temp = w->objects;
	while (temp != NULL)
	{
		lline(w->image, temp->line, 0xFF00FF);
		temp = temp->next;
	}
	w->player->can_move = 15;
	float angle = 0.0f;
	for (int i = 0; i < 8; i++)
	{
		float camera = 2.0f * i / WIDTH - 1.0f;
		ray = w->player->where;
		int dist = (int)ray_march(w, w->player->where, angle, 0xCCCCCC);
		angle += (float)(M_PI / 4);
	}

	t_line l = {w->player->where, p};
	lline(w->image, l, 0xF0F00F);
	mlx_put_image_to_window(w->gfx->mlx_ptr, w->gfx->win_ptr, w->image->ptr, 0, 0);
	return (0);
}

t_object		*new_scene_object(int x1, int y1, int x2, int y2)
{
	t_object	*o;

	if (!(o = (t_object *)malloc(sizeof(t_object))))
		return (NULL);
	o->line.p1.x = x1;
	o->line.p1.y = y1;
	o->line.p2.x = x2;
	o->line.p2.y = y2;
	o->next = NULL;
	return (o);
}

void			set_scene_objects(t_wolf *w)
{
	int			y;
	int			x;
	int			s = (WIDTH / w->map->width < HEIGHT / w->map->height) ? WIDTH / w->map->width : HEIGHT / w->map->height;
	t_object	*temp;

	y = -1;
	while (++y < w->map->height)
	{
		x = -1;
		while (++x < w->map->width)
		{
			if (w->map->info[y][x] == 0)
				continue ;
			if (x + 1 < w->map->width && w->map->info[y][x + 1] != 0)
			{
				temp = new_scene_object(x * s, y * s, (x + 1) * s, y * s);
				temp->next = w->objects;
				w->objects = temp;
				temp = NULL;
			}
			if (y + 1 < w->map->height && w->map->info[y + 1][x] != 0)
			{
				temp = new_scene_object(x * s, y * s, x * s, (y + 1) * s);
				temp->next = w->objects;
				w->objects = temp;
				temp = NULL;
			}
		}
	}
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
	set_scene_objects(&w);

	w.image = new_image(w.gfx->mlx_ptr, w.gfx->win_ptr, WIDTH, HEIGHT);

	w.input = &input;

	w.player = &player;
	w.player->where.x = CENTER_X;
	w.player->where.y = CENTER_Y;
	w.player->direction.x = -1;
	w.player->direction.y = 0;
	w.player->camera.x = 0;
	w.player->camera.y = 1;
	w.player->angle = M_PI * 1.5f;
	w.player->options = 0;
	w.player->can_move = 15;

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
