/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csinglet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 19:09:35 by csinglet          #+#    #+#             */
/*   Updated: 2019/03/06 19:09:35 by csinglet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLAYER_H
# define PLAYER_H

# include "draw.h"

typedef struct      s_player
{
    t_xyz			where;
	t_xyz			direction;
	t_xyz			camera;
	uint8_t			can_move;
	float			angle;
	int				options;
}                   t_player;

#endif
