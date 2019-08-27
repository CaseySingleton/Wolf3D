/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csinglet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/26 17:37:04 by csinglet          #+#    #+#             */
/*   Updated: 2019/08/26 17:37:05 by csinglet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Wolf3D.h"
#include <dirent.h>

t_image				*load_texture(char *texture_path, t_wolf *w)
{
	t_image			*img;

	if (!(img = (t_image *)malloc(sizeof(t_image))))
		return (NULL);
	if ((img->ptr = mlx_xpm_file_to_image(w->gfx->mlx_ptr, texture_path, &img->width, &img->height)) == NULL)
	{
		ft_printf("Error: Failed to load texture: %s\n", texture_path);
	}
	img->buffer = (int *)mlx_get_data_addr(img->ptr, &(img->bits_per_pixel),
		&(img->image_length), &(img->endian));
	ft_printf("width: %d, height: %d\n", img->width, img->height);
	return (img);
}

void				load_all_textures(t_wolf *w)
{
	int				i;
	DIR				*dir;
	struct dirent	*content;
	char			*texture_full_path;

	if ((dir = opendir("textures")) != NULL)
	{
		i = 0;
		while ((content = readdir(dir)) != NULL)
		{
			if (content->d_name[0] == '.')
				continue ;
			texture_full_path = ft_strjoin("textures/", content->d_name);
			ft_printf("Loading %s\n", texture_full_path);
			w->textures[i] = load_texture(texture_full_path, w);
			free(texture_full_path);
			texture_full_path = NULL;
			i++;
		}
	}
}

void				free_textures(t_wolf *w)
{
	int				i;

	i = 0;
	while (i < NUM_TEXTURES)
	{
		free(w->textures[i]);
		w->textures[i] = NULL;
		i++;
	}
}
