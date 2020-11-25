/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_resolution.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cruiz-de <cruiz-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/12 11:58:25 by cruiz-de          #+#    #+#             */
/*   Updated: 2020/11/25 13:02:21 by cruiz-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	empty_line(char *str)
{
	int i;

	i = 0;
	while (str[i] != '\0')
	{
		if (!ft_isspace(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	resolution(t_vars *vars, char *str)
{
	int i;
	int both;

	both = 2;
	i = 0;
	if (vars->parser.width == 0 && vars->parser.height == 0)
	{
		i++;
		while (ft_isspace(str[i]))
			i++;
		if (!ft_isdigit(str[i]))
			return (0);
		while (ft_isspace(str[i]))
			i++;
		if (ft_isdigit(str[i]))
		{
			vars->parser.width = ft_atoi(&str[i]);
			both = 1;
		}
		while (ft_isdigit(str[i]))
			i++;
		if (!ft_isspace(str[i]))
		{
			write(1, "Error\nWrong Resolution", 23);
			exit(0);
		}
		while (ft_isspace(str[i]))
			i++;
		if (ft_isdigit(str[i]))
		{
			vars->parser.height = ft_atoi(&str[i]);
			both = 2;
		}
		while (ft_isdigit(str[i]))
			i++;
		if (!empty_line(&str[i]))
		{
			write(1, "Error\nWrong Resolution", 23);
			exit(0);
		}
		if (both != 2)
		{
			write(1, "Error\nWrong Resolution", 23);
			exit(0);
		}
	}
	return (1);
}
