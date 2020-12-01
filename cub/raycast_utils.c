/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cruiz-de <cruiz-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/01 11:59:35 by cruiz-de          #+#    #+#             */
/*   Updated: 2020/12/01 14:17:11 by cruiz-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

t_dda   dda_coor(int x0, int y0, int x1, int y1)
{
    t_dda coords;

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
	int		x;
	int		y;
	int		dx;
	int		dy;
	int		steps;
	float	xinc;
	float	yinc;
	int		i;

	i = 0;
	dx = coords.x1 - coords.x0;
	dy = coords.y1 - coords.y0;
	steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);
	xinc = dx / (float)steps;
	yinc = dy / (float)steps;
	x = coords.x0;
	y = coords.y0;
	while (i <= steps)
	{
		ch_mlx_pixel_put(data, x, y, color);
		x += xinc;
		y += yinc;
		i++;
	}
}
