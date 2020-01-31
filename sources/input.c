/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csinglet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 13:41:42 by csinglet          #+#    #+#             */
/*   Updated: 2019/07/13 15:44:08 by csinglet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Wolf3D.h"

/*
** Function: reload_map
** Reloads the current map file. This is used so that changes to the map can be
** loaded without restarting.
**
** w: A t_wolf structure containing information about the game state
**
** Return: None
*/
static void	reload_map(t_wolf *w)
{
	t_map	*temp;

	ft_printf("Reloading map\n");
	temp = get_map(w->map->path);
	if (temp != NULL)
	{
		free_map(w->map);
		w->map = temp;
	}
	else
		ft_printf("Using last working version of map: \n", w->map->name);
}

/*
** Function: handle_input
** Checks for user input and performes the appropriate tasks. Handles player
** movement, map reloading, and closing of the program.
**
** w: A t_wolf structure containing information about the game state
**
** Return: Integer to indicate a safe return
*/
int			handle_input(t_wolf *w)
{
	char	*k;

	k = w->input->keys;
	if (k[KEY_ESCAPE])
	{
		ft_printf("Exiting Wolf3D\n");
		free_map(w->map);
		free_textures(w);
		mlx_destroy_image(w->mlx_ptr, w->image[0]->ptr);
		mlx_destroy_image(w->mlx_ptr, w->image[1]->ptr);
		mlx_destroy_window(w->mlx_ptr, w->win_ptr);
		exit(0);
	}
	if (k[KEY_R])
		reload_map(w);
	player_movement(w);
	player_strafing(w);
	player_rotation(w);
	return (0);
}

/*
** Function: toggle_key
** On the event that a keyboard key is pressed, toggles the keys state in the
** keys buffer.
**
** key: The pressed key
** w: A t_wolf structure containing information about the game state
**
** Return: Integer to indicate a safe return
*/
int			toggle_key(int key, t_wolf *w)
{
	w->input->keys[key] ^= 1;
	return (0);
}

/*
** Function: toggle_mouse_key
** On the event that the mouse left click is pressed, toggles the mouse left
** click state from 1 to 0 or 0 to 1.
**
** key: The pressed mouse key
** x: The x position of the mouse cursor
** y: The y position of the mouse cursor
** w: A t_wolf structure containing information about the game state
**
** Return: Integer to indicate a safe return
*/
int			toggle_mouse_key(int key, int x, int y, t_wolf *w)
{
	w->input->mouse_key ^= 1;
	w->input->mouse_x = x;
	w->input->mouse_y = y;
	return (0);
}

/*
** Function: mouse_motion
** On the event that the mouse is moved, the saved x and y coordinates of the
** mouse cursor are saved.
**
** x: The x position of the mouse cursor
** y: The y position of the mouse cursor
** w: A t_wolf structure containing information about the game state
**
** Return: Integer to indicate a safe return
*/
int			mouse_motion(int x, int y, t_wolf *w)
{
	w->input->mouse_x = x;
	w->input->mouse_y = y;
	return (0);
}
