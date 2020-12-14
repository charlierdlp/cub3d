/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cruiz-de <cruiz-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/12 13:03:21 by cruiz-de          #+#    #+#             */
/*   Updated: 2020/12/14 11:41:42 by cruiz-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int		spawn(t_vars *vars, int y, int x)
{
	vars->player.y = ((float)y) + 0.5;
	vars->player.x = ((float)x) + 0.5;
	if (vars->map.map[y][x] == 'N')
		vars->player.angle = 270;
	else if (vars->map.map[y][x] == 'S')
		vars->player.angle = 90;
	else if (vars->map.map[y][x] == 'E')
		vars->player.angle = 0;
	else if (vars->map.map[y][x] == 'W')
		vars->player.angle = 180;
	vars->map.map[y][x] = '0';
	return (0);
}

void	recheck_map(t_vars *vars)
{
	int	y;
	int	x;

	y = -1;
	while (++y < vars->map.height)
	{
		x = -1;
		while (vars->map.map[y][++x])
		{
			if (vars->map.map[y][x] == ' ')
				vars->map.map[y][x] = '0';
			if (ft_strchr("NWSE", vars->map.map[y][x]) && vars->map.c == 0)
			{
				spawn(vars, y, x);
				vars->map.c = 1;
			}
			else if (ft_strchr("NWSE", vars->map.map[y][x]) && vars->map.c == 1)
				exit_error("Error\nDouble Player\n");
			else if (!ft_strchr("NWSE012 ", vars->map.map[y][x]))
				exit_error("Error\nWrong Map!\n");
		}
	}
	if (vars->player.x == 0 && vars->player.y == 0)
		exit_error("Error\nNo Player\n");
}

int		jump(t_vars *vars, char *str)
{
	int	i;

	i = 0;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '\0')
		return (0);
	if (ft_strchr("012", str[i]))
	{
		vars->map.map[vars->map.current] = ft_strdup(str);
		vars->map.current++;
	}
	return (0);
}

void	replace(t_vars *vars)
{
	int x;
	int y;

	x = 0;
	y = 0;
	while (y < vars->map.height)
	{
		x = 0;
		while (vars->map.map[y][x])
		{
			if (vars->map.map[y][x] == 'M')
				vars->map.map[y][x] = '0';
			else if (vars->map.map[y][x] == 'D')
				vars->map.map[y][x] = '2';
			x++;
		}
		y++;
	}
}

int		start_map(t_vars *vars, int fd)
{
	char	*line;
	int		i;

	vars->map.c = 0;
	vars->map.map = malloc(sizeof(char *) * vars->map.height * vars->map.width);
	vars->map.current = 0;
	while ((i = get_next_line(fd, &line)) > 0)
	{
		jump(vars, line);
		free(line);
	}
	jump(vars, line);
	free(line);
	recheck_map(vars);
	flood_fill(vars, vars->player.x, vars->player.y, '0');
	perimeter_check1(vars);
	replace(vars);
	return (0);
}
