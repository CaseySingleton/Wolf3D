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

void			set_hooks(t_wolf *w)
{
	mlx_do_key_autorepeatoff(w->mlx_ptr);
	mlx_hook(w->win_ptr, 2, 0, toggle_key, w);
	mlx_hook(w->win_ptr, 3, 0, toggle_key, w);
	mlx_hook(w->win_ptr, 6, 0, mouse_motion, w);
	mlx_loop_hook(w->mlx_ptr, game_loop, w);
}

void			wolf_setup(char *file_path)
{
	t_wolf		w;
	t_input		input;
	t_player	player;

	if (!(w.map = get_map(file_path)))
		return ;
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
