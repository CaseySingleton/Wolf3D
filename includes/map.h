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
	char			*path;
	char			*name;
	int				**info;
	int				width;
	int				height;
	int				error;
}					t_map;

/*
**	map.c
*/

t_map				*map_init(void);
t_map				*get_map(char *path);

/*
**	map_utils.c
*/

t_map				*is_map_valid(t_map **m);
void				free_map(t_map *m);

#endif
