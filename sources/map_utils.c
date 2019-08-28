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

#include "map.h"

void				free_map(t_map *m)
{
	int				y;

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

t_map				*reload_map(t_map *m)
{
	char			*path;

	path = m->path;
	free_map(m);
	m = get_map(path);
	return (m);
}
