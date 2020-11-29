/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cruiz-de <cruiz-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/09 11:22:06 by cruiz-de          #+#    #+#             */
/*   Updated: 2020/11/29 14:19:49 by cruiz-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	find_sprites(t_vars *vars)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	vars->snumber = 0;
	while (i < vars->map.height)
	{
		j = 0;
		while (j < vars->map.width)
		{
			if (vars->map.map[i][j] == '2')
				vars->snumber++;
			j++;
		}
		i++;
	}
}

int		sprite_array(t_vars *vars)
{
	int	i;
	int	j;
	int k;

	i = 0;
	j = 0;
	k = 0;
	find_sprites(vars);
	if (!(vars->sprite = malloc(vars->snumber * sizeof(t_sprite))))
		return (0);
	while (i < vars->map.height)
	{
		j = 0;
		while (j < vars->map.width)
		{
			if (vars->map.map[i][j] == '2')
			{
				vars->sprite[k].x = j + 0.5;
				vars->sprite[k].y = i + 0.5;
				k++;
			}
			j++;
		}
		i++;
	}
	if (!(vars->walls.dist = malloc(vars->parser.width * sizeof(float))))
		return (0);
	return (1);
}

void	sort_sarray(t_vars *vars)
{
	int			i;
	int			j;
	t_sprite	tmp;

	i = 0;
	while (i < vars->snumber)
	{
		j = 0;
		while (j < vars->snumber)
		{
			if (vars->sprite[j].distance < vars->sprite[i].distance)
			{
				tmp = vars->sprite[j];
				vars->sprite[j] = vars->sprite[i];
				vars->sprite[i] = tmp;
			}
			j++;
		}
		i++;
	}
}

int		calc_angles(t_vars *vars, t_sprite *sprite)
{
	float xdist;
	float ydist;

	xdist = sprite->x - vars->player.x;
	ydist = sprite->y - vars->player.y;
	sprite->leftangle = vars->player.angle - (vars->player.fov / 2);
	sprite->leftangle += (sprite->leftangle < 0) ? 360 : 0;
	sprite->pixels_per_degree = vars->parser.width / vars->player.fov;
	sprite->angle = atan2(ydist, xdist) * 180 / M_PI;
	sprite->relative = sprite->angle - sprite->leftangle;
	sprite->relative += (sprite->relative < 0) ? 360 : 0;
	sprite->position = sprite->pixels_per_degree * sprite->relative;
	sprite->distance = sqrt(pow(xdist, 2) + pow(ydist, 2));
	sprite->drawheight = (int)((vars->parser.height / 2) / sprite->distance);
	sprite->drawwidth = vars->stexture.width * sprite->drawheight
	/ vars->stexture.height;
	return (0);
}

void	create_square(t_vars *vars, t_square *square, float x, float y)
{
	vars->stexture.color = ((unsigned int*)vars->stexture.addr)[j * vars->stexture.width + i];
	square->x1 = x;
	square->y1 = y;
	square->x2 = x + sprite->x_inc;
	square->y2 = y + sprite->y_inc;
}

void	squares(t_vars *vars, t_sprite *sprite, t_square *square)
{
	while (square->x1 <= square->x2)
	{
		if (vars->stexture.color != 0xFFFFFF && vars->walls.dist[square->x1]
		> sprite->distance)
			dda_algorithm(&vars->data, square->x1, square->y1, square->x1,
			square->y2, vars->stexture.color);
		square->x1++;
	}
}

int		draw_sprites(t_vars *vars, t_sprite *sprite)
{
	t_square square;
	float	x;
	float	y;
	int		i;
	int		j;

	i = 0;
	j = 0;
	x = sprite->position - sprite->drawwidth;
	sprite->x_inc = (sprite->drawwidth * 2) / vars->stexture.width;
	sprite->y_inc = (sprite->drawheight * 2) / vars->stexture.height;
	while (i < vars->stexture.width)
	{
		j = 0;
		y = vars->parser.height / 2 - sprite->drawheight;
		while (j < vars->stexture.height)
		{
			create_square(vars, &square, x, y);
			squares(vars, sprite, &square);
			y += sprite->y_inc;
			j++;
		}
		x += sprite->x_inc;
		i++;
	}
	return (0);
}
