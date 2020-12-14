/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_resolution.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cruiz-de <cruiz-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/12 11:58:25 by cruiz-de          #+#    #+#             */
/*   Updated: 2020/12/14 14:21:53 by cruiz-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int		empty_line(char *str)
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

void	max_resolution(t_vars *vars)
{
	if (vars->parser.width > 2560)
		vars->parser.width = 2560;
	if (vars->parser.height > 1440)
		vars->parser.height = 1440;
}

void	fill_resolution(t_vars *vars, char *str, int type)
{
	if (type == 0)
	{
		if (ft_isdigit(str[0]))
			vars->parser.width = ft_atoi(str);
	}
	if (type == 1)
	{
		if (ft_isdigit(str[0]))
			vars->parser.height = ft_atoi(str);
	}
}

void		resolution(t_vars *vars, char *str, int i)
{
	if (vars->parser.width == 0 && vars->parser.height == 0)
	{
		while (ft_isspace(str[i]))
			i++;
		if (!ft_isdigit(str[i]))
			exit_error("Error\nWrong Resolution");
		while (ft_isspace(str[i]))
			i++;
		fill_resolution(vars, &str[i], 0);
		while (ft_isdigit(str[i]))
			i++;
		if (!ft_isspace(str[i]))
			exit_error("Error\nWrong Resolution");
		while (ft_isspace(str[i]))
			i++;
		fill_resolution(vars, &str[i], 1);
		while (ft_isdigit(str[i]))
			i++;
		if (!empty_line(&str[i]))
			exit_error("Error\nWrong Resolution");
		max_resolution(vars);
	}
	else
		exit_error("Error\nDouble Resolution");
	if (vars->parser.width <= 0 || vars->parser.height <= 0)
		exit_error("Error\nWrong Resolution");
}
