/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csinglet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/28 17:11:36 by csinglet          #+#    #+#             */
/*   Updated: 2019/08/28 17:11:36 by csinglet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Wolf3D.h"

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
