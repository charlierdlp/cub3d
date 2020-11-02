/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cruiz-de <cruiz-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/09 11:22:06 by cruiz-de          #+#    #+#             */
/*   Updated: 2020/11/02 14:14:03 by cruiz-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	find_sprites(t_vars *vars)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	vars->sprite.number = 0;
	// alocar mapa y distancia a las paredes


}

int calc_angles(t_vars *vars)
{
	float xdist;
	float ydist;

	xdist = 5 - vars->player.x; //spritex
	ydist = 4 - vars->player.y; // spritey
	vars->sprite.leftangle = vars->player.angle - (vars->player.fov / 2);
	vars->sprite.leftangle += (vars->sprite.leftangle < 0 ) ? 360 : 0;
	vars->sprite.pixels_per_degree = SCREEN_WIDTH / vars->player.fov;
	vars->sprite.angle = atan2(ydist, xdist) * 180 / M_PI;
	vars->sprite.relative = vars->sprite.angle - vars->sprite.leftangle;
	vars->sprite.relative += (vars->sprite.relative < 0 ) ? 360 : 0;
	vars->sprite.position = vars->sprite.pixels_per_degree * vars->sprite.relative;
	vars->sprite.distance = sqrt(pow(xdist, 2) + pow(ydist, 2));
	vars->sprite.drawheight = (int)(SCREEN_HEIGHT / 2) / vars->sprite.distance;
	vars->sprite.drawwidth = vars->sprite.texture.width * vars->sprite.drawheight / vars->sprite.texture.height;
	return (0);
}

void square(t_vars *vars, int x1, int y1, int x2, int y2)
{
	while (x1 <= x2)
	{
		if (vars->sprite.texture.color != 0 && vars->walls.dist[x1] > vars->sprite.distance)
			dda_algorithm(&vars->data, x1, y1, x1, y2, vars->sprite.texture.color);
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

	x = vars->sprite.position - vars->sprite.drawwidth;
	x_inc = (vars->sprite.drawwidth * 2) / vars->sprite.texture.width;
	y_inc = (vars->sprite.drawheight * 2) / vars->sprite.texture.height;

	printf("x: %d\n", x);

	printf("xinc: %f\n", x_inc);
	printf("yinc: %f\n", y_inc);
	printf("====\n");
	
	printf("drawwidth: %f\n", vars->sprite.drawwidth);
	printf("drawhight: %f\n", vars->sprite.drawheight);
	printf("====\n");
	
	printf("width: %d\n",vars->sprite.texture.width);
	printf("height: %d\n",vars->sprite.texture.height);
	printf("====\n");
	printf("position: %f\n",vars->sprite.position);
	printf("relative: %f\n", vars->sprite.relative);
	printf("leftanle:%f\n", vars->sprite.leftangle);

	while (i < vars->sprite.texture.width)
	{
		j = 0;
		y = SCREEN_HEIGHT / 2 - vars->sprite.drawheight;
		//printf("y:%d\n", y);
		while (j < vars->sprite.texture.height)
		{
			vars->sprite.texture.color = ((unsigned int*)vars->sprite.texture.addr)[j * vars->sprite.texture.width + i];
			square(vars, x, y, (x + x_inc), (y + y_inc));
			y += y_inc;
			j++;
		}
		x += x_inc;
		i++;
	}
	return(0);
}
