/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multithreading.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csinglet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/28 17:06:31 by csinglet          #+#    #+#             */
/*   Updated: 2019/08/28 17:06:32 by csinglet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Wolf3D.h"

void			*render_threading(void *p)
{
	int			i;
	pthread_t	threads[NUMBER_OF_THREADS];
	t_thread	params[NUMBER_OF_THREADS];
	t_wolf		*w;

	w = (t_wolf *)p;
	i = -1;
	while (++i < NUMBER_OF_THREADS)
	{
		params[i].w = w;
		params[i].x = i;
		if (pthread_create(&threads[i], NULL, render_scene, &params[i]) != 0)
			ft_printf("Error\n");
	}
	i = -1;
	while (++i < NUMBER_OF_THREADS)
		pthread_join(threads[i], NULL);
	pthread_exit(NULL);
	return (NULL);
}
