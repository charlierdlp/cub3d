/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cruiz-de <cruiz-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/09 11:22:06 by cruiz-de          #+#    #+#             */
/*   Updated: 2020/10/21 14:02:29 by cruiz-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int calc_angles(t_vars *vars)
{
	int xdist;
	int ydist;

	xdist = 4 - vars->player.x; //spritex
	ydist = 3 - vars->player.y; // spritey
	vars->sprite.leftangle = vars->player.angle - (vars->player.fov / 2); //leftangle
	vars->sprite.rightangle = vars->sprite.leftangle + vars->player.fov; 
	vars->sprite.pixels_per_degree = SCREEN_WIDTH / vars->player.fov;
	vars->sprite.relative = atan2(ydist, xdist);
	vars->sprite.position = vars->sprite.pixels_per_degree * vars->sprite.relative;
	vars->sprite.distance = sqrt(pow(xdist, 2) + pow(ydist, 2));
	vars->sprite.drawheight = (int)((SCREEN_HEIGHT/2) / vars->sprite.distance);
	vars->sprite.drawwidth = vars->sprite.texture.width * vars->sprite.drawheight / vars->sprite.texture.height;
	return (0);
}

void square(t_vars *vars, int x1, int y1, int x2, int y2)
{
	while (x1 <= x2)
	{
		dda_algorithm(&vars->data, x1, y1, x2, y2, vars->sprite.texture.color);
		x1++;
	}
}

int	draw_sprites(t_vars *vars)
{
	float	x_inc;
	float	y_inc;
	int		x;
	int		y;
	int		i;
	int		j;

	i = 0;
	j = 0;

	x = vars->sprite.position - (vars->sprite.drawwidth / 2);
	y = vars->sprite.position - (vars->sprite.drawheight / 2);
	x_inc = (vars->sprite.drawwidth * 2) / vars->sprite.texture.width;
	y_inc = (vars->sprite.drawheight * 2) / vars->sprite.texture.height;

	while (i < vars->sprite.texture.width)
	{
		j = 0;
		while (j < vars->sprite.texture.height)
		{
			vars->sprite.texture.color = 0x654321;//((unsigned int*)vars->sprite.texture.addr)[j * vars->sprite.texture.width + x];
			//square(vars, x, y, (x + x_inc), (y + y_inc));
			//printf("%d %d\n", x, y);
			//dda_algorithm(&vars->data, x, y, x, (y + y_inc), vars->sprite.texture.color);
			y += y_inc;
			j++;
		}
		x += x_inc;
		i++;
	}
	return(0);
}
