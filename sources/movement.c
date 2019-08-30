/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csinglet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/28 16:50:34 by csinglet          #+#    #+#             */
/*   Updated: 2019/08/28 16:50:35 by csinglet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Wolf3D.h"

void		player_movement(t_wolf *w)
{
	char	*k;
	float	move_x;
	float	move_y;

	k = w->input->keys;
	if (k[KEY_W] || k[KEY_UP_ARROW] || k[KEY_S] || k[KEY_DOWN_ARROW])
	{
		move_x = w->player->direction.x * 0.1;
		move_y = w->player->direction.y * 0.1;
		move_x *= ((k[KEY_W] || k[KEY_UP_ARROW]) ? 1 : -1);
		move_y *= ((k[KEY_W] || k[KEY_UP_ARROW]) ? 1 : -1);
		move_x += w->player->where.x;
		move_y += w->player->where.y;
		if (w->map->info[(int)w->player->where.y][(int)(move_x + 0.1f)] <= 0 &&
			w->map->info[(int)w->player->where.y][(int)(move_x - 0.1f)] <= 0)
			w->player->where.x = move_x;
		if (w->map->info[(int)(move_y + 0.1f)][(int)w->player->where.x] <= 0 &&
			w->map->info[(int)(move_y - 0.1f)][(int)w->player->where.x] <= 0)
			w->player->where.y = move_y;
	}
}

void		player_strafing(t_wolf *w)
{
	char	*k;
	float	move_x;
	float	move_y;

	k = w->input->keys;
	if (k[KEY_Q] || k[KEY_E])
	{
		move_x = w->player->direction.y * 0.1;
		move_y = w->player->direction.x * 0.1;
		move_x *= ((k[KEY_Q]) ? -1 : 1);
		move_y *= ((k[KEY_Q]) ? 1 : -1);
		move_x += w->player->where.x;
		move_y += w->player->where.y;
		if (w->map->info[(int)w->player->where.y][(int)(move_x + 0.1f)] <= 0 &&
			w->map->info[(int)w->player->where.y][(int)(move_x - 0.1f)] <= 0)
			w->player->where.x = move_x;
		if (w->map->info[(int)(move_y + 0.1f)][(int)w->player->where.x] <= 0 &&
			w->map->info[(int)(move_y - 0.1f)][(int)w->player->where.x] <= 0)
			w->player->where.y = move_y;
	}
}

void		player_rotation(t_wolf *w)
{
	char	*k;
	float	old;
	float	r;

	k = w->input->keys;
	if (k[KEY_A] || k[KEY_LEFT_ARROW] || k[KEY_D] || k[KEY_RIGHT_ARROW])
	{
		r = M_PI / 50;
		old = w->player->direction.x;
		r *= (k[KEY_A] || k[KEY_LEFT_ARROW]) ? 1 : -1;
		w->player->direction.x = old * cos(r) - w->player->direction.y * sin(r);
		w->player->direction.y = old * sin(r) + w->player->direction.y * cos(r);
		old = w->player->camera.x;
		w->player->camera.x = old * cos(r) - w->player->camera.y * sin(r);
		w->player->camera.y = old * sin(r) + w->player->camera.y * cos(r);
	}
}
