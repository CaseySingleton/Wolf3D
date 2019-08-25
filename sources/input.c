/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csinglet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 13:41:42 by csinglet          #+#    #+#             */
/*   Updated: 2019/07/13 15:44:08 by csinglet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Wolf3D.h"

int			handle_input(t_wolf *w)
{
	char	*k;
	t_object *temp;

	k = w->input->keys;
	if (k[KEY_ESCAPE])
	{
		ft_printf("Exiting Wolf3D\n");
		exit(0);
	}
	if (k[KEY_W] || k[KEY_UP_ARROW] || k[KEY_S] || k[KEY_DOWN_ARROW])
	{
		float	move_x = w->player->direction.x * 0.1;
		float	move_y = w->player->direction.y * 0.1;

		move_x *= ((k[KEY_W] || k[KEY_UP_ARROW]) ? 1 : -1);
		move_y *= ((k[KEY_W] || k[KEY_UP_ARROW]) ? 1 : -1);
		move_x += w->player->where.x;
		move_y += w->player->where.y;
		if (w->map->info[(int)w->player->where.y][(int)move_x] == 0)
		{
			w->player->where.x = move_x;
		}
		if (w->map->info[(int)move_y][(int)w->player->where.x] == 0)
		{
			w->player->where.y = move_y;
		}
	}
	if (k[KEY_A] || k[KEY_LEFT_ARROW] || k[KEY_D] || k[KEY_RIGHT_ARROW])
	{
		float	old_direction = w->player->direction.x;
		float	old_plane = w->player->camera.x;
		float	rotation = M_PI / 50;
	
		rotation *= (k[KEY_A] || k[KEY_LEFT_ARROW]) ? 1 : -1;
		w->player->direction.x = old_direction * cos(rotation) - w->player->direction.y * sin(rotation);
		w->player->direction.y = old_direction * sin(rotation) + w->player->direction.y * cos(rotation);
		w->player->camera.x = old_plane * cos(rotation) - w->player->camera.y * sin(rotation);
		w->player->camera.y = old_plane * sin(rotation) + w->player->camera.y * cos(rotation);
	}
	if (k[KEY_Q] || k[KEY_E])
	{
		float	move_x = w->player->direction.y * 0.1;
		float	move_y = w->player->direction.x * 0.1;

		move_x *= ((k[KEY_Q]) ? -1 : 1);
		move_y *= ((k[KEY_Q]) ? 1 : -1);
		move_x += w->player->where.x;
		move_y += w->player->where.y;
		if (w->map->info[(int)w->player->where.y][(int)move_x] == 0)
		{
			w->player->where.x = move_x;
		}
		if (w->map->info[(int)move_y][(int)w->player->where.x] == 0)
		{
			w->player->where.y = move_y;
		}
	}
	return (0);
}

int			toggle_key(int key, t_wolf *w)
{
	w->input->keys[key] ^= 1;
	return (0);
}

int			toggle_mouse_key(int key, int x, int y, t_wolf *w)
{
	w->input->mouse_key ^= 1;
	w->input->mouse_x = x;
	w->input->mouse_y = y;
	return (0);
}

int			mouse_motion(int x, int y, t_wolf *w)
{
	w->input->mouse_x = x;
	w->input->mouse_y = y;
	return (0);
}
