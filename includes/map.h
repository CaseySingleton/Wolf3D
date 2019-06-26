/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csinglet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 19:17:35 by csinglet          #+#    #+#             */
/*   Updated: 2019/03/06 19:17:36 by csinglet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_H
# define MAP_H

# include "draw.h"

typedef struct 		s_map
{
	char			*file_name;
	int				**info;
	t_xyz			**vmap;
	char			*name;
	int				width;
	int				height;
}					t_map;

/*
**	map.c
*/

t_map				*map_init(void);
t_xyz				**get_vmap(t_map *m);
t_map				*get_map(char *file_name);
void				rotate_vmap_around_point(t_map *m, t_xyz *p, double angle);
void				translate_vmap(t_map *m, int x, int y, int z);
void				scale_vmap(t_map *m, float xs, float ys, float zs);
void				print_vmap_info(t_map *map);

#endif
