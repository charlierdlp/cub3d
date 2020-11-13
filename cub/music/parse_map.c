/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cruiz-de <cruiz-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/12 13:03:21 by cruiz-de          #+#    #+#             */
/*   Updated: 2020/11/13 14:06:23 by cruiz-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int     start_map(t_vars *vars, int fd)
{
    char    *line;
    char    i;
    int     length;


    while ((i = get_next_line(fd, &line)) > 0)
	{
        length = ft_strlen(line);
        if (vars->map.width < length)
            vars->map.width = length;
        vars->map.height++;
	}
}

int		mapalloc(t_vars *vars)
{
    char *line;
    int fd;
	int	i;
	int	j;

	if(!(vars->map.map = malloc(vars->map.height * sizeof(char *))))
		return(0);
	i = 0;
     while ((i = get_next_line(fd, &line)) > 0)
	{
        if (!(vars->map.map[i] = malloc(vars->map.width * sizeof(char))))
			return (0);
        vars->map.map[i] = ft_strdup(line);
        vars->map.height++;
        i++;
        free(line);
    }
    return(0);
}

int		recheck_map(t_vars *vars, char *line, int i)
{
	int	i;

	i = 0;
	while (line[i] != '\0')
	{
		if (!ft_strchr("012NESW ", line[i]))
			return (0);
	}
	return (1);
}

