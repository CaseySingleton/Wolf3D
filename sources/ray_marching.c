/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_marching.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csinglet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/15 20:05:20 by csinglet          #+#    #+#             */
/*   Updated: 2019/05/15 20:05:21 by csinglet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Wolf3D.h"
#include "draw.h"

float			distance(t_xyz p1, t_xyz p2)
{
	return (sqrt(pow(p2.x - p1.x, 2) + pow(p2.y - p1.y, 2)));
}

// (| a*x1 + b*y1 + c |) / (sqrt( a*a + b*b))

float			distance_from_point_to_line(t_xyz p, t_line l)
{
	float		dist;

	dist = fabs(((l.p2.y - l.p1.y) * p.x) - ((l.p2.x - l.p1.x) * p.y) + (l.p2.x * l.p1.y) - (l.p2.y * l.p1.x));
	dist = dist / distance(l.p1, l.p2);
	return (dist);
}

float			min(float x, float y)
{
	return ((x < y) ? x : y);
}

float			max(float x, float y)
{
	return ((x > y) ? x : y);
}

float			difference(float x, float y)
{
	if (x > y)
		return (difference(y, x));
	return (x - y);
}

int				clamp(t_xyz p)
{
	int			small_x;
	int			small_y;

	small_x = min(p.x, WIDTH - p.x);
	small_y = min(p.y, HEIGHT - p.y);
	return (min(small_x, small_y));
}

float			ray_march(t_wolf *w, t_xyz point, float angle, int color)
{
	t_xyz		new_point;
	t_object	*temp;
	float		d;
	float		radius;

	radius = clamp(point);
	if (point.x >= WIDTH || point.x < 0 || point.y >= HEIGHT || point.y < 0)
		return (0.0f);
	temp = w->objects;
	while (temp != NULL)
	{
		if ((point.x > min(temp->line.p1.x, temp->line.p2.x) &&
			point.x < max(temp->line.p1.x, temp->line.p2.x)) ||
			(point.y > min(temp->line.p1.y, temp->line.p2.y) &&
			point.y < max(temp->line.p1.y, temp->line.p2.y)))
		{
			d = distance_from_point_to_line(point, temp->line);
			if (d < 1.0f)
				lline(w->image, temp->line, 0xFF000F);
		}
		else
		{
			d = min(distance(point, temp->line.p1), distance(point, temp->line.p2));
		}
		radius = min(radius, fabs(d));
		temp = temp->next;
	}
	if (radius < 1.0f)
		return (0.0f);
	new_point.x = point.x + cos(angle) * radius;
	new_point.y = point.y + sin(angle) * radius;
	new_point.z = 0;
	circle(w->image, point, radius, color);
	circle(w->image, point, 4, 0x00FF00);
	line(w->image, point, new_point, color);
	return (radius + ray_march(w, new_point, angle, color - 0x0F0F0F));
}
