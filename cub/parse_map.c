/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cruiz-de <cruiz-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/12 13:03:21 by cruiz-de          #+#    #+#             */
/*   Updated: 2020/11/24 13:15:34 by cruiz-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int     count_map(t_vars *vars, char *str)
{
	int    i;
    int    length;

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

	return(0);
}

int		spawn(t_vars *vars, int y, int x)
{
	if (vars->map.map[y][x] == 'N')
		vars->player.angle = 270;
	else if (vars->map.map[y][x] == 'S')
		vars->player.angle = 90;
	else if (vars->map.map[y][x] == 'E')
		vars->player.angle = 0;
	else if (vars->map.map[y][x] == 'W')
		vars->player.angle = 180;
	return(0);
}

int		recheck_map(t_vars *vars)
{
	int	y;
	int	x;

	y = 0;
	while (y < vars->map.height)
	{
		x = 0;
		while (vars->map.map[y][x])
		{
			if (ft_strchr("NWSE", vars->map.map[y][x]))
			{
				spawn(vars, y, x);
				vars->player.y = ((float)y) + 0.5;
				vars->player.x = ((float)x) + 0.5;
				vars->map.map[y][x] = '0';
			}
			x++;
		}
		y++;
	}
	return (1);
}
void		perimeter_check(t_vars *vars)
{
	int i;
	int x;
	int y;

	i = 0;
	x = 0;
	y = 0;
	while (i < ft_strlen(vars->map.map[0]))
	{
		if (vars->map.map[0][x] == 'M' || vars->map.map[vars->map.height - 1][x] == 'M')
		{
			write(1, "Error\nOpen Map", 15);
        	exit(0);
		}
		x++;
		i++;
	}
	i = 0;
	while (i < vars->map.height)
	{
		if (vars->map.map[y][0] == 'M' || vars->map.map[0][ft_strlen(vars->map.map[0]) - 1] == 'M')
		{
			write(1, "Error\nOpen Map", 15);
       		exit(0);
		}
		y++;
		i++;
	}
}

void	flood_fill(t_vars *vars, int x, int y, int prev_pos)
{
	int i;

	i = 0;
	if (x < 0 || x >= vars->map.width || y < 0 || y >= vars->map.height)
		return ;
	if (vars->map.map[y][x] == '\0')
	{
		write(1, "Error\nOpen Map", 15);
        exit(0);
	}
	if (vars->map.map[y][x] != prev_pos)
		return ;
	vars->map.map[y][x] = 'M';
	flood_fill(vars, x + 1, y, prev_pos);
	flood_fill(vars, x - 1, y, prev_pos);
	flood_fill(vars, x, y + 1, prev_pos);
	flood_fill(vars, x, y - 1, prev_pos);
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
	return(0);
}

void	replace(t_vars *vars)
{
	int x;
	int y;
	x = 0;
	y = 0;

	while(y < vars->map.height)
	{	
		x = 0;
		while(vars->map.map[y][x])
		{
			if(vars->map.map[y][x] == 'M')
				vars->map.map[y][x] = '0';
			x++;
		}
		y++;
	}
}

int     start_map(t_vars *vars, int fd)
{
	char    *line;
    int     i;

	vars->map.map = malloc(sizeof(char *) * vars->map.height * vars->map.width);
	vars->map.current = 0;
    while ((i = get_next_line(fd, &line)) > 0)
    {
		jump(vars, line);
		free(line);
    }
    //printf("%d, %d, %d\n", vars->texture.sky[0], vars->texture.sky[1], vars->texture.sky[2]);
	jump(vars, line);
	free(line);
	recheck_map(vars);
	flood_fill(vars, vars->player.x, vars->player.y, '0');
	perimeter_check(vars);
	replace(vars);
	//printf("%d, %d, %d\n", vars->texture.sky[0], vars->texture.sky[1], vars->texture.sky[2]);
	return(0);
}
