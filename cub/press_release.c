/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   press_release.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cruiz-de <cruiz-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/12 12:18:38 by cruiz-de          #+#    #+#             */
/*   Updated: 2020/11/11 11:09:36 by cruiz-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	x_close(t_vars *vars)
{
	mlx_destroy_image(vars->mlx, vars->data.img);
	mlx_destroy_window(vars->mlx, vars->win);
	exit(0);
}

int	key_press(int keycode, t_vars *vars)
{
	if (keycode == W)
		vars->keys.w = 1;
	else if (keycode == A)
		vars->keys.a = 1;
	else if (keycode == D)
		vars->keys.d = 1;
	else if (keycode == S)
		vars->keys.s = 1;
	else if (keycode == LEFT)
		vars->keys.left = 1;
	else if (keycode == RIGHT)
		vars->keys.right = 1;
	return (0);
}

int	key_release(int keycode, t_vars *vars)
{
	if (keycode == ESC)
	{
		mlx_destroy_image(vars->mlx, vars->data.img);
		mlx_destroy_window(vars->mlx, vars->win);
		if (vars->pid)
			kill(vars->pid, 15);
		exit(0);
	}
	else if (keycode == W)
		vars->keys.w = 0;
	else if (keycode == A)
		vars->keys.a = 0;
	else if (keycode == D)
		vars->keys.d = 0;
	else if (keycode == S)
		vars->keys.s = 0;
	else if (keycode == LEFT)
		vars->keys.left = 0;
	else if (keycode == RIGHT)
		vars->keys.right = 0;
	return (0);
}
