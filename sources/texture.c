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

/*
** Function: shader
** Darkens the color of pixels based on the distance of an object from the
** player.
**
** distance: The distance of an object from the player
** color: The desired color of a pixel
**
** Returns: Integer representing the shaded color of a pixel
*/
int					shader(float distance, int color)
{
	int				new_color;
	int				r;
	int				g;
	int				b;

	new_color = 0;
	r = ((color >> 2 * 8) & 0xFF);
	g = ((color >> 1 * 8) & 0xFF);
	b = ((color >> 0 * 8) & 0xFF);
	distance *= 10;
	if (r > (int)((r / 0xFF) * distance))
		new_color |= (r - (int)((r / (float)0xFF) * distance)) << 2 * 8;
	if (g > (int)((g / 0xFF) * distance))
		new_color |= (g - (int)((g / (float)0xFF) * distance)) << 1 * 8;
	if (b > (int)((b / 0xFF) * distance))
		new_color |= (b - (int)((b / (float)0xFF) * distance)) << 0 * 8;
	return (new_color);
}

/*
** Function: load_texture
** Opens a texture file and converts from XPM format to an int[][]
**
** texture_path: The path to the texture file
** w: A t_wolf structure containing information about the game state
**
** Return: t_image structure containing the texture information
*/
t_image				*load_texture(char *texture_path, t_wolf *w)
{
	t_image			*img;

	if (!(img = (t_image *)malloc(sizeof(t_image))))
		return (NULL);
	if ((img->ptr = mlx_xpm_file_to_image(w->mlx_ptr, texture_path, &img->width,
		&img->height)) == NULL)
	{
		ft_printf("Error: Failed to load texture: %s\n", texture_path);
	}
	img->buffer = (int *)mlx_get_data_addr(img->ptr, &(img->bits_per_pixel),
		&(img->image_length), &(img->endian));
	return (img);
}

/*
** Function: load_all_textures
** Opens and processes all texture files located in the texture directory. If
** there is no texture directory an error is displayed.
**
** w: A t_wolf structure containing information about the game state
**
** Return: None
*/
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
			w->textures[i] = load_texture(texture_full_path, w);
			free(texture_full_path);
			texture_full_path = NULL;
			i++;
		}
		closedir(dir);
	}
	else
		ft_printf("Error: Directory: \'textures\' not found\n");
}

/*
** Function: free_textures
** Frees all allocated memory associated with textures.
**
** w: A t_wolf structure containing information about the game state
**
** Return: None
*/
void				free_textures(t_wolf *w)
{
	int				i;

	i = 0;
	while (i < NUM_TEXTURES)
	{
		mlx_destroy_image(w->mlx_ptr, w->textures[i]->ptr);
		w->textures[i] = NULL;
		i++;
	}
}
