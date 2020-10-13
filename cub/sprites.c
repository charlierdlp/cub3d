/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cruiz-de <cruiz-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/09 11:22:06 by cruiz-de          #+#    #+#             */
/*   Updated: 2020/10/13 13:47:19 by cruiz-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int calc_angles(t_vars *vars)
{
	int xdist;
	int ydist;

	xdist = vars->sprite.x - vars->player.x;
	ydist = vars->sprite.y - vars->player.y;
	vars->sprite.leftangle = vars->player.angle - (vars->player.fov / 2);
	vars->sprite.rightangle = vars->sprite.leftangle + vars->player.fov;
	vars->sprite.pixels_per_degree = SCREEN_WIDTH / vars->player.fov;
	vars->sprite.relative = atan2(ydist, xdist);
	vars->sprite.pixels_per_degree * vars->sprite.relative;
	vars->sprite.distance = sqrt(pow(xdist, 2) + pow(ydist, 2));
	vars->sprite.drawheight = (int)((SCREEN_HEIGHT/2) / vars->sprite.distance);
	vars->sprite.drawwidth = vars->sprite.width * vars->sprite.drawheight / vars->sprite.height;
	return (0);
}
