/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cruiz-de <cruiz-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/29 12:53:18 by cruiz-de          #+#    #+#             */
/*   Updated: 2020/12/11 12:30:11 by cruiz-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int				count_map(t_vars *vars, char *str)
{
	int	i;
	int	length;

	i = 0;
	if (vars->map.start == 2)
	{
		write(1, "Error\nFinished Map", 19);
		exit(0);
	}
	vars->map.start = 1;
	length = ft_strlen(str);
	if (vars->map.width < length)
		vars->map.width = length;
	vars->map.height++;
	return (0);
}

void			flood_fill(t_vars *vars, int x, int y, int prev_pos)
{
	int	i;

	i = 0;
	if (x < 0 || x >= vars->map.width || y < 0 || y >= vars->map.height)
		return ;
	if (vars->map.map[y][x] == '\0')
	{
		write(1, "Error\nOpen Map", 15);
		exit(0);
	}
	if (vars->map.map[y][x] != prev_pos && vars->map.map[y][x] != '2')
		return ;
	if (vars->map.map[y][x] == '2')
		vars->map.map[y][x] = 'D';
	else
		vars->map.map[y][x] = 'M';
	flood_fill(vars, x + 1, y, prev_pos);
	flood_fill(vars, x - 1, y, prev_pos);
	flood_fill(vars, x, y + 1, prev_pos);
	flood_fill(vars, x, y - 1, prev_pos);
}

void			perimeter_check2(t_vars *vars)
{
	int	i;
	int	y;

	i = 0;
	y = 0;
	while (i < vars->map.height)
	{
		if (vars->map.map[y][0] == 'M'
		|| vars->map.map[y][ft_strlen(vars->map.map[i]) - 1] == 'M'
		|| vars->map.map[y][0] == '2'
		|| vars->map.map[y][ft_strlen(vars->map.map[i]) - 1] == '2')
		{
			write(1, "Error\nOpen Map", 15);
			exit(0);
		}
		y++;
		i++;
	}
}

void			perimeter_check1(t_vars *vars)
{
	size_t	i;
	int		x;

	i = 0;
	x = 0;
	while (i < ft_strlen(vars->map.map[0]))
	{
		if (vars->map.map[0][x] == 'M'
		|| vars->map.map[vars->map.height - 1][x] == 'M'
		|| vars->map.map[0][x] == '2'
		|| vars->map.map[vars->map.height - 1][x] == '2')
		{
			write(1, "Error\nOpen Map", 15);
			exit(0);
		}
		x++;
		i++;
	}
	perimeter_check2(vars);
}

/*
** unsigned	long ft_rgbtohex(int rgb[3])
** {
** 	if (rgb[0] < 0 || rgb[1] < 0 || rgb[2] < 0)
** 		return (0 << 16 | 0 << 8 | 0);
** 	return (rgb[0] << 16 | rgb[1] << 8 | rgb[2]);
** }
*/

unsigned long	ft_rgbtohex(int r, int g, int b)
{
	return ((r << 16) + (g << 8) + b);
}
