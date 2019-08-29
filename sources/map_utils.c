/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csinglet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/28 14:17:35 by csinglet          #+#    #+#             */
/*   Updated: 2019/08/28 14:17:35 by csinglet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Wolf3D.h"

static void		map_error(t_map **m)
{
	ft_printf("Error: Map is invalid\n");
	free_map(*m);
	*m = NULL;
}

t_map			*is_map_valid(t_map **m)
{
	int			i;

	if ((*m)->error == 0)
	{
		i = -1;
		while (++i < (*m)->height)
		{
			if ((*m)->info[i][0] < 1 || (*m)->info[i][(*m)->width - 1] < 1)
				(*m)->error = 1;
		}
		i = -1;
		while (++i < (*m)->width)
		{
			if ((*m)->info[0][i] < 1 || (*m)->info[(*m)->height - 1][i] < 1)
				(*m)->error = 1;
		}
	}
	if ((*m)->error == 1)
		map_error(m);
	return (*m);
}

void			free_map(t_map *m)
{
	int			y;

	y = -1;
	while (++y < m->height)
	{
		free(m->info[y]);
		m->info[y] = NULL;
	}
	free(m->info);
	free(m->name);
	free(m);
	m->info = NULL;
	m->name = NULL;
	m = NULL;
}
