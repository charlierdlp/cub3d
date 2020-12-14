/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cruiz-de <cruiz-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/29 14:00:28 by cruiz-de          #+#    #+#             */
/*   Updated: 2020/12/04 12:53:24 by cruiz-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	create_square(t_square *square, float x, float y, t_sprite *sprite)
{
	square->x1 = x;
	square->y1 = y;
	square->x2 = x + sprite->x_inc;
	square->y2 = y + sprite->y_inc;
}

void	squares(t_vars *vars, t_sprite *sprite, t_square *square)
{
	t_dda coords;

	while (square->x1 < 0)
		square->x1++;
	while (square->x1 <= square->x2)
	{
		coords = dda_coor(square->x1, square->y1, square->x1, square->y2);
		if (vars->stexture.color != 0xFFFFFF &&
		vars->walls.dist[square->x1] > sprite->distance)
			dda_algorithm(&vars->data, coords, vars->stexture.color);
		square->x1++;
	}
}
