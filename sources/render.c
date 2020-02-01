/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csinglet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/28 16:54:00 by csinglet          #+#    #+#             */
/*   Updated: 2019/08/28 16:54:01 by csinglet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Wolf3D.h"

/*
** Note: Normally a rendering function is not seperated this much. This was
** due to the project requirement that function bodies could not exceed 25
** lines.
** https://en.wikipedia.org/wiki/Digital_differential_analyzer_(graphics_algorithm)
** The above link is a reference on how a DDA algorithm works. To explain in
** comments alone would be an arduous task.
*/

/*
** Function: init_variables
** Initializes the values in the t_ray_vars structure based on the players
** position found in the t_wolf structure. This is used for every ray created
** by the render_scene function.
**
** w: A t_wolf structure containing information about the game state
** v: A t_ray_vars structure representing the current ray being used to trace
**    the map.
**
** Return: None
*/
static void		init_variables(t_wolf *w, t_ray_vars *v)
{
	v->camera_x = 2 * v->x / (float)WIDTH - 1;
	v->dir_x = w->player->direction.x + w->player->camera.x * v->camera_x;
	v->dir_y = w->player->direction.y + w->player->camera.y * v->camera_x;
	v->map_x = w->player->where.x;
	v->map_y = w->player->where.y;
	v->delta_dist_x = fabs(1 / v->dir_x);
	v->delta_dist_y = fabs(1 / v->dir_y);
	v->hit = 0;
}

/*
** Function: determine_step_direction
** Determines the step direction of the current ray. The step can be in either
** the +-X or +-Y direction.
**
** w: A t_wolf structure containing information about the game state
** v: A t_ray_vars structure representing the current ray being used to trace
**    the map.
**
** Return: None
*/
static void		determine_step_direction(t_wolf *w, t_ray_vars *v)
{
	if (v->dir_x < 0)
	{
		v->step_x = -1;
		v->dist_x = (w->player->where.x - v->map_x) * v->delta_dist_x;
	}
	else
	{
		v->step_x = 1;
		v->dist_x = (v->map_x + 1.0f - w->player->where.x) * v->delta_dist_x;
	}
	if (v->dir_y < 0)
	{
		v->step_y = -1;
		v->dist_y = (w->player->where.y - v->map_y) * v->delta_dist_y;
	}
	else
	{
		v->step_y = 1;
		v->dist_y = (v->map_y + 1.0f - w->player->where.y) * v->delta_dist_y;
	}
}

/*
** Function: dda
** The main portion the DDA algorithm. Finds the collision point between a ray
** and a wall in the map. After a hit is found the side hit by the ray is
** determined.
**
** w: A t_wolf structure containing information about the game state
** v: A t_ray_vars structure representing the current ray being used to trace
**    the map.
**
** Return: None
*/
static void		dda(t_wolf *w, t_ray_vars *v)
{
	while (v->hit == 0)
	{
		if (v->dist_x < v->dist_y)
		{
			v->dist_x += v->delta_dist_x;
			v->map_x += v->step_x;
			v->side = 0;
		}
		else
		{
			v->dist_y += v->delta_dist_y;
			v->map_y += v->step_y;
			v->side = 1;
		}
		if (w->map->info[v->map_y][v->map_x] != 0)
			v->hit = 1;
	}
	if (v->side == 0)
		v->dist = (v->map_x - w->player->where.x + (1 - v->step_x)
			/ 2) / v->dir_x;
	else
		v->dist = (v->map_y - w->player->where.y + (1 - v->step_y)
			/ 2) / v->dir_y;
}

/*
** Function: draw_wall
** Draws a vertical line given a start and stop point. This line is the vertical
** row of pixels representing a slice of the visible wall.
**
** w: A t_wolf structure containing information about the game state
** v: A t_ray_vars structure representing the current ray being used to trace
**    the map.
**
** Return: None
*/
static void		draw_wall(t_wolf *w, t_ray_vars *v)
{
	float		wall_x;
	int			texture_choice;
	int			y;

	y = v->line_start;
	if (v->side == 0)
		wall_x = w->player->where.y + v->dist * v->dir_y;
	else
		wall_x = w->player->where.x + v->dist * v->dir_x;
	wall_x -= floor(wall_x);
	v->tex_x = wall_x * 32;
	if ((v->side == 0 && v->dir_x > 0) || (v->side == 1 && v->dir_y < 0))
		v->tex_x = 32 - v->tex_x - 1;
	while (y < v->line_end)
	{
		v->d = y * 256 - HEIGHT * 128 + v->line_height * 128;
		v->tex_y = ((v->d * 32) / v->line_height) / 256;
		texture_choice = (abs(w->map->info[v->map_y][v->map_x] - 1)) %
			NUM_TEXTURES;
		pixel(w->image[w->front], v->x, y, shader(v->dist,
			w->textures[texture_choice]->buffer[v->tex_y * 32 + v->tex_x]));
		y++;
	}
}

/*
** Function: render_scene
** For the width of the game window in pixels, render_scene draws the vertical
** lines used to represent the ceiling, wall, and floor visible by the player.
**
** info: A void pointer containing a t_wolf structure and t_ray_vars structure
**
** Return: NULL pointer
*/
void			*render_scene(void *info)
{
	t_wolf		*w;
	t_ray_vars	v;

	w = ((t_thread *)info)->w;
	v.x = ((t_thread *)info)->x;
	while (v.x < WIDTH)
	{
		init_variables(w, &v);
		determine_step_direction(w, &v);
		dda(w, &v);
		v.line_height = (HEIGHT / v.dist);
		v.line_start = -v.line_height / 2 + HEIGHT / 2;
		v.line_end = v.line_height / 2 + HEIGHT / 2;
		if (v.line_start < 0)
			v.line_start = 0;
		if (v.line_end > HEIGHT)
			v.line_end = HEIGHT;
		// Draws the ceiling
		line(w->image[w->front], (t_xyz){v.x, v.line_start, 0},
			(t_xyz){v.x, 0, 0}, 0x9edbde);
		// Draws the floor
		line(w->image[w->front], (t_xyz){v.x, v.line_end, 0},
			(t_xyz){v.x, HEIGHT, 0}, 0x2b2b2b);
		draw_wall(w, &v);
		v.x += NUMBER_OF_THREADS;
	}
	return (NULL);
}
