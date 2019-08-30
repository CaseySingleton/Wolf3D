/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csinglet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/02 17:49:40 by csinglet          #+#    #+#             */
/*   Updated: 2019/03/02 17:49:41 by csinglet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Wolf3D.h"
#include "map.h"

t_map			*map_init(char *path)
{
	t_map		*map;

	if (!(map = (t_map *)malloc(sizeof(t_map))))
		return (NULL);
	map->path = NULL;
	map->info = NULL;
	map->name = NULL;
	map->width = -1;
	map->height = -1;
	map->error = 0;
	map->path = path;
	return (map);
}

static int		open_file(const char *file_name)
{
	int			fd;

	if ((fd = open(file_name, O_RDONLY)) < 0)
	{
		ft_printf("file: %s: not found\n", file_name);
		exit(0);
	}
	return (fd);
}

static int		**map_info_init(t_map *m)
{
	int			**info;
	int			i;

	if (!(info = (int **)malloc(sizeof(int **) * m->height)))
		return (NULL);
	i = -1;
	while (++i < m->height)
		if (!(info[i] = (int *)malloc(sizeof(int) * m->width)))
			return (NULL);
	return (info);
}

static void		atoi_line(t_map *m, char *line, int position)
{
	char		**numbers;
	int			i;

	numbers = ft_strsplit(line, ' ');
	i = -1;
	while (numbers[++i] != NULL)
		;
	if (i != m->width)
		m->error = 1;
	i = -1;
	while (numbers[++i] != NULL)
		m->info[position][i] = ft_atoi(numbers[i]);
	i = -1;
	while (numbers[++i] != NULL)
		free(numbers[i]);
	free(numbers);
}

t_map			*get_map(char *path)
{
	t_map		*map;
	int			fd;
	int			i;
	char		*line;

	fd = open_file(path);
	map = map_init(path);
	i = -1;
	while (get_next_line(fd, &line) && map->error == 0)
	{
		if (map->name == NULL)
			map->name = ft_strdup(line);
		else if (map->width == -1)
			map->width = ft_atoi(line);
		else if (map->height == -1)
			map->height = ft_atoi(line);
		else if (map->info == NULL)
			map->info = map_info_init(map);
		if (map->info != NULL && ++i < map->height)
			atoi_line(map, line, i);
		free(line);
	}
	map->error = (i != map->height - 1) ? 1 : 0;
	return (is_map_valid(&map));
}
