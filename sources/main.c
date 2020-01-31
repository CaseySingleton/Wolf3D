/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csinglet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/16 16:00:21 by csinglet          #+#    #+#             */
/*   Updated: 2019/03/16 16:00:22 by csinglet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Wolf3D.h"

/*
** Function: display
** Draws the current buffered image to the window.
**
** p: A t_wolf structure taken in as a void pointer containing the image to be
**    displayed on screen
**
** Return: A NULL pointer
*/
void			*display(void *p)
{
	t_wolf		*w;

	w = (t_wolf *)p;
	mlx_clear_window(w->mlx_ptr, w->win_ptr);
	mlx_put_image_to_window(w->mlx_ptr, w->win_ptr, w->image[w->front ^ 1]->ptr,
		0, 0);
	ft_bzero(w->image[w->front ^ 1]->buffer, sizeof(int) * HEIGHT * WIDTH);
	return (NULL);
}

/*
** Function: game_loop
** Reads the users input, then creates two threads, one to render the next
** image buffer given the users input, and another to display the previously
** Rendered image.
**
** w: A t_wolf structure containing information about the game state
**
** return: 0 to indicate no errors
*/
int				game_loop(t_wolf *w)
{
	pthread_t	threads[3];

	handle_input(w);
	pthread_create(&threads[0], NULL, render_threading, (void *)w);
	pthread_create(&threads[1], NULL, display, (void *)w);
	pthread_join(threads[0], NULL);
	pthread_join(threads[1], NULL);
	w->front ^= 1;
	return (0);
}

/*
** Function: set_hooks
** Sets the functions to be associated with keyboard and mouse events. Sets the
** function game_loop as the primary looping function.
**
** w: A t_wolf structure containing information about the game state
**
** Return: None
*/
void			set_hooks(t_wolf *w)
{
	mlx_do_key_autorepeatoff(w->mlx_ptr);
	mlx_hook(w->win_ptr, 2, 0, toggle_key, w);
	mlx_hook(w->win_ptr, 3, 0, toggle_key, w);
	mlx_hook(w->win_ptr, 6, 0, mouse_motion, w);
	mlx_loop_hook(w->mlx_ptr, game_loop, w);
}

/*
** Function: wolf_setup
** Initializes structures, the window, and the images to be displayed.
**
** file_path: A file path to the desired game map
**
** Return: None
*/
void			wolf_setup(char *file_path)
{
	t_wolf		w;
	t_input		input;
	t_player	player;

	if (!(w.map = get_map(file_path)))
		return ;
	ft_bzero(&input, sizeof(t_input));
	w.input = &input;
	w.mlx_ptr = mlx_init();
	w.win_ptr = mlx_new_window(w.mlx_ptr, WIDTH, HEIGHT, "RayCaster");
	w.image[0] = new_image(w.mlx_ptr, WIDTH, HEIGHT);
	w.image[1] = new_image(w.mlx_ptr, WIDTH, HEIGHT);
	w.front = 0;
	player_init(&player);
	w.player = &player;
	set_player_position(&w);
	load_all_textures(&w);
	set_hooks(&w);
	mlx_loop(w.mlx_ptr);
}

int				main(int argc, char *argv[])
{
	if (argc > 1)
	{
		wolf_setup(argv[1]);
		ft_printf("Exiting Wolf3D\n");
	}
	else
		ft_printf("usage: Wolf3D \"map\"");
	return (0);
}
