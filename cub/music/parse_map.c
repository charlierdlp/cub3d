/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cruiz-de <cruiz-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/12 13:03:21 by cruiz-de          #+#    #+#             */
/*   Updated: 2020/11/15 12:16:36 by cruiz-de         ###   ########.fr       */
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
        free(line);
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
	int	j;

	j = 0;
	while (line[i] != '\0')
	{
		if (!ft_strchr("012NESW ", line[i]))
			return (0);
        if (line[j] == ' ')
			vars->map.map[i][j] = '0';
    	else
			vars->map.map[i][j] = line[j];
		j++;
	}
	return (1);
}

