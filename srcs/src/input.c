/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csinglet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 13:41:42 by csinglet          #+#    #+#             */
/*   Updated: 2019/02/27 13:41:42 by csinglet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Wolf3D.h"

// (*f)(t_list *elem)

static void	add_if_within_bounds(t_xyz *v1, t_xyz *v2, float add_x, float add_y)
{
	float	x1;
	float	y1;
	float	x2;
	float	y2;

	x1 = v1->x + add_x;
	y1 = v1->y + add_y;
	x2 = v2->x + add_x;
	y2 = v2->y + add_y;
	if (x1 < 0 || x1 > WIDTH || y1 < 0 || y1 > HEIGHT)
		return ;
	if (x2 < 0 || x2 > WIDTH || y2 < 0 || y2 > HEIGHT)
		return ;
	v1->x = x1;
	v1->y = y1;
	v2->x = x2;
	v2->y = y2;
}

/*
**	Rotation of a vector by angle a:
**	new_x = cos(a) - sin(a)
**	new_y = sin(a) + sin(a)
*/

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
	if ((k[KEY_W] && (w->player->can_move & (1 << 1))) || (k[KEY_S] && (w->player->can_move & (1 << 3))))
	{
		float move_x = ((k[KEY_S]) ? cos(w->player->angle) : -cos(w->player->angle)) * 1.5f;
		float move_y = ((k[KEY_S]) ? sin(w->player->angle) : -sin(w->player->angle)) * 1.5f;
		temp = w->objects;
		while (temp != NULL)
		{
			temp->line.p1.x += move_x;
			temp->line.p1.y += move_y;
			temp->line.p2.x += move_x;
			temp->line.p2.y += move_y;
			temp = temp->next;
		}
	}
	if (k[KEY_A] || k[KEY_D])
	{
		ft_printf("Rotation start\n");
		float angle = (k[KEY_A]) ? 0.025f : - 0.025f;
		temp = w->objects;
		while (temp != NULL)
		{
			vector_rotate_around_p2(&(temp->line.p1), w->player->where, angle);
			vector_rotate_around_p2(&(temp->line.p2), w->player->where, angle);
			temp = temp->next;
		}
		ft_printf("Rotation end\n");
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