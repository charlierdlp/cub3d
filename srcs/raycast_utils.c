/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cruiz-de <cruiz-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/01 11:59:35 by cruiz-de          #+#    #+#             */
/*   Updated: 2022/04/12 20:30:35 by cruiz-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void	init_colours(t_vars *vars)
{
	vars->texture.sky[0] = -1;
	vars->texture.sky[1] = -1;
	vars->texture.sky[2] = -1;
	vars->texture.floor[0] = -1;
	vars->texture.floor[1] = -1;
	vars->texture.floor[2] = -1;
}

t_dda	dda_coor(int x0, int y0, int x1, int y1)
{
	t_dda coords;

	coords.dx = 0;
	coords.dy = 0;
	coords.x0 = x0;
	coords.x1 = x1;
	coords.y0 = y0;
	coords.y1 = y1;
	return (coords);
}

void	ch_mlx_pixel_put(t_img *data, int x, int y, int color)
{
	char *dst;

	if (x < 0 || y < 0 || x >= data->width || y >= data->height)
		return ;
	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void	dda_algorithm(t_img *data, t_dda coords, int color)
{
	int		steps;
	float	xinc;
	float	yinc;
	int		i;

	i = 0;
	coords.dx = coords.x1 - coords.x0;
	coords.dy = coords.y1 - coords.y0;
	steps = abs(coords.dx) > abs(coords.dy) ? abs(coords.dx) : abs(coords.dy);
	xinc = coords.dx / (float)steps;
	yinc = coords.dy / (float)steps;
	while (i <= steps)
	{
		ch_mlx_pixel_put(data, coords.x0, coords.y0, color);
		coords.x0 += xinc;
		coords.y0 += yinc;
		i++;
	}
}
