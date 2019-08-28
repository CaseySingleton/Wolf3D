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

t_map	*map_init(void)
{
	t_map		*map;

	if (!(map = (t_map *)malloc(sizeof(t_map))))
		return (NULL);
	map->path = NULL;
	map->info = NULL;
	map->name = NULL;
	map->width = -1;
	map->height = -1;
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

static int		**map_info_init(int width, int height)
{
	int			**wolf;
	int			i;

	if (!(wolf = (int **)malloc(sizeof(int * *) * height)))
		return (NULL);
	i = -1;
	while (++i < height)
		if (!(wolf[i] = (int *)malloc(sizeof(int) * width)))
			return (NULL);
	return (wolf);
}

static void		atoi_line(int **wolf, char *line, int position)
{
	char		**numbers;
	int			i;

	numbers = ft_strsplit(line, ' ');
	i = -1;
	while (numbers[++i] != NULL)
		wolf[position][i] = ft_atoi(numbers[i]);
	i = -1;
	while (numbers[++i] != NULL)
		free(numbers[i]);
	free(numbers);
}

/*
**	void			print_map_info(t_map *map)
**	{
**		ft_printf("name: \"%s\" width: %d height: %d\n", map->name, map->width, map->height);
**		for (int i = 0; i < map->height; i++)
**		{
**			for (int j = 0; j < map->width; j++)
**				ft_printf("%d ", map->info[i][j]);
**			ft_printf("\n");
**		}
**	}
*/

t_map			*get_map(char *path)
{
	t_map		*map;
	int			fd;
	int			i;
	char		*line;

	map = map_init();
	map->path = path;
	fd = open_file(path);
	i = -1;
	while (get_next_line(fd, &line))
	{
		if (map->name == NULL)
			map->name = ft_strdup(line);
		else if (map->width == -1)
			map->width = ft_atoi(line);
		else if (map->height == -1)
			map->height = ft_atoi(line);
		else if (map->info == NULL)
			map->info = map_info_init(map->width, map->height);
		if (map->info != NULL)
			atoi_line(map->info, line, ++i);
		free(line);
	}
	return (map);
}
