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

t_map			*map_init(void)
{
	t_map		*map;

	if (!(map = (t_map *)malloc(sizeof(t_map))))
		return (NULL);
	map->file_name = NULL;
	map->info = NULL;
	map->name = NULL;
	map->width = -1;
	map->height = -1;
	return (map);
}

int				open_file(const char *file_name)
{
	int			fd;

	if ((fd = open(file_name, O_RDONLY)) < 0)
	{
		ft_printf("file: %s: not found\n", file_name);
		exit(0);
	}
	return (fd);
}

int				**map_info_init(int width, int height)
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

void			atoi_line(int **wolf, char *line, int position)
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

void			print_map_info(t_map *map)
{
	ft_printf("name: \"%s\" width: %d height: %d\n", map->name, map->width, map->height);
	for (int i = 0; i < map->height; i++)
	{
		for (int j = 0; j < map->width; j++)
			ft_printf("%d ", map->info[i][j]);
		ft_printf("\n");
	}
}

void			print_vmap_info(t_map *map)
{
	ft_printf("name: \"%s\" width: %d height: %d\n", map->name, map->width, map->height);
	for (int i = 0; i < map->height; i++)
		for (int j = 0; j < map->width; j++)
			printf("(%f, %f, %f)\n", map->vmap[i][j].x, map->vmap[i][j].y, map->vmap[i][j].z);
}

t_xyz			**get_vmap(t_map *m)
{
	t_xyz		**vmap;
	int			y;
	int			x;

	vmap = NULL;
	if (!(vmap = (t_xyz **)malloc(sizeof(t_xyz *) * m->height)))
		return (NULL);
	y = -1;
	while (++y < m->height)
	{
		if (!(vmap[(int)y] = (t_xyz *)malloc(sizeof(t_xyz) * m->width)))
			return (NULL);
		x = -1;
		while (++x < m->width)
		{
			vmap[y][x].x = x;
			vmap[y][x].y = y;
			vmap[y][x].z = 0;
		}
	}
	return (vmap);
}

t_map			*get_map(char *file_name)
{
	t_map		*map;
	int			fd;
	int			i;
	char		*line;

	map = map_init();
	map->file_name = ft_strdup(file_name);
	fd = open_file(file_name);
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
	print_map_info(map);
	// map->vmap = get_vmap(map);
	return (map);
}

void			rotate_vmap_around_point(t_map *m, t_xyz *p, double angle)
{
	int			y;
	int			x;

	y = -1;
	while (++y < m->height)
	{
		x = -1;
		while (++x < m->width)
			vector_rotate_around_p2(&(m->vmap[y][x]), *p, angle);
	}
}

void			translate_vmap(t_map *m, int x, int y, int z)
{
	int			i;
	int			j;

	i = -1;
	while (++i < m->height)
	{
		j = -1;
		while (++j < m->width)
			vector_translate(&(m->vmap[i][j]), x, y, z);
	}
}

void			scale_vmap(t_map *m, float xs, float ys, float zs)
{
	float		matrix[4][4];
	int			mid_x;
	int			mid_y;
	int			y;
	int			x;

	matrix_set_scale(matrix, xs, ys, 1);
	mid_x = m->vmap[m->height / 2][m->width / 2].x;
	mid_y = m->vmap[m->height / 2][m->width / 2].y;
	y = -1;
	while (++y < m->height)
	{
		x = -1;
		while (++x < m->width)
		{
			vector_translate(&(m->vmap[y][x]), -mid_x, -mid_y, 0);
			m->vmap[y][x].x *= xs;
			m->vmap[y][x].y *= ys;
			vector_translate(&(m->vmap[y][x]), mid_x, mid_y, 0);
		}
	}
}
