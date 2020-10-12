/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cruiz-de <cruiz-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/29 11:22:38 by cruiz-de          #+#    #+#             */
/*   Updated: 2020/10/12 14:05:33 by cruiz-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"
#define SPEED 0.2

float	torad(float degree)
{
	return (degree * M_PI / 180);
}

int		forward_backwards(t_vars *vars)
{
	if (vars->keys.w == 1)
	{
		vars->player.cos = cos(torad(vars->player.angle)) * SPEED;
		vars->player.sin = sin(torad(vars->player.angle)) * SPEED;
		if (map[(int)(vars->player.y + vars->player.sin)]
		[(int)(vars->player.x + vars->player.cos)] == 0)
		{
			vars->player.x += vars->player.cos;
			vars->player.y += vars->player.sin;
		}
	}
	if (vars->keys.s == 1)
	{
		vars->player.cos = cos(torad(vars->player.angle)) * SPEED;
		vars->player.sin = sin(torad(vars->player.angle)) * SPEED;
		if (map[(int)(vars->player.y - vars->player.sin)]
		[(int)(vars->player.x - vars->player.cos)] == 0)
		{
			vars->player.x -= vars->player.cos;
			vars->player.y -= vars->player.sin;
		}
	}
	return (0);
}

int		left_right(t_vars *vars, int i)
{
	if (vars->keys.a == 1)
	{
		vars->player.cos = cos((torad(vars->player.angle + 90)) * SPEED);
		vars->player.sin = sin((torad(vars->player.angle + 90)) * SPEED);
		if (map[(int)(vars->player.y - vars->player.sin)]
		[(int)(vars->player.x - vars->player.cos)] == 0)
		{
			vars->player.x -= (vars->player.cos);
			vars->player.y -= (vars->player.sin);
		}
	}
	if (vars->keys.d == 1)
	{
		vars->player.cos = cos((torad(vars->player.angle - 90)) * SPEED);
		vars->player.sin = sin((torad(vars->player.angle - 90)) * SPEED);
		if (map[(int)(vars->player.y - vars->player.sin)]
		[(int)(vars->player.x - vars->player.cos)] == 0)
		{
			vars->player.x -= (vars->player.cos);
			vars->player.y -= (vars->player.sin);
		}
	}
	return (0);
}

int		move(t_vars *vars)
{
	if (vars->keys.left == 1)
		vars->player.angle -= vars->player.rotation;
	if (vars->keys.right == 1)
		vars->player.angle += vars->player.rotation;
	forward_backwards(vars);
	left_right(vars);
	return (0);
}
