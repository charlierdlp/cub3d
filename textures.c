/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cruiz-de <cruiz-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/05 10:08:45 by cruiz-de          #+#    #+#             */
/*   Updated: 2020/12/08 11:49:31 by cruiz-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	textures(t_vars *vars, char *path, t_textdata *texture)
{
	texture->img = mlx_xpm_file_to_image(vars->mlx, path,
	&texture->width, &texture->height);
	texture->addr = mlx_get_data_addr(texture->img, &texture->bits_per_pixel,
	&texture->line_length, &texture->endian);
	return (0);
}

int	drawtexture(t_vars *vars, int x)
{
	t_dda	coords;
	float	yincrementer;
	float	y;
	int		i;

	i = 0;
	yincrementer = (vars->walls.height * 2) / vars->texture.height;
	y = (vars->parser.height / 2) - vars->walls.height;
	while (i < vars->texture.height)
	{
		coords = dda_coor(x, y, x, (y + yincrementer));
		vars->texture.color = ((unsigned int*)vars->texture.addr)
		[i * vars->texture.width + vars->texture.texturepositionx];
		dda_algorithm(&vars->data, coords,
		vars->texture.color);
		y += yincrementer;
		i++;
	}
	return (0);
}
