/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_colour.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cruiz-de <cruiz-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 11:36:32 by cruiz-de          #+#    #+#             */
/*   Updated: 2022/04/12 20:30:19 by cruiz-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

int				check_colour(t_vars *vars)
{
	if (vars->texture.sky[0] >= 0
		&& vars->texture.sky[0] <= 255
		&& vars->texture.sky[1] >= 0 && vars->texture.sky[1] <= 255
		&& vars->texture.sky[2] >= 0 && vars->texture.sky[2] <= 255)
	{
		if (vars->texture.floor[0] >= 0 && vars->texture.floor[0] <= 255
		&& vars->texture.floor[1] >= 0 && vars->texture.floor[1] <= 255
		&& vars->texture.floor[2] >= 0 && vars->texture.floor[2] <= 255)
			return (1);
	}
	exit_error("Error\nWrong Colour\n");
	return (0);
}

int				colour_save(t_vars *vars, char *str, int type, char differ)
{
	if (!ft_isdigit(str[0]))
		return (0);
	if (differ == 'F')
	{
		if (type == 0)
			vars->texture.floor[0] = ft_atoi(str);
		else if (type == 1)
			vars->texture.floor[1] = ft_atoi(str);
		else if (type == 2)
			vars->texture.floor[2] = ft_atoi(str);
	}
	else if (differ == 'C')
	{
		if (type == 0)
			vars->texture.sky[0] = ft_atoi(str);
		else if (type == 1)
			vars->texture.sky[1] = ft_atoi(str);
		else if (type == 2)
			vars->texture.sky[2] = ft_atoi(str);
	}
	return (1);
}

int				fill(t_vars *vars, char *str, char differ, int type)
{
	if (!ft_isdigit(str[0]))
		exit_error("Error\nWrong Colour\n");
	if ((!colour_save(vars, str, type, differ)))
		return (0);
	return (1);
}

void			find_comma(char *str, int *i)
{
	while (ft_isdigit(str[*i]))
		*i += 1;
	if (str[*i] == ',')
		*i += 1;
}

int				is_colour(t_vars *vars, char *str)
{
	int		i;
	char	differ;

	i = 0;
	while (ft_isspace(str[i]))
		i++;
	differ = str[i];
	i++;
	while (ft_isspace(str[i]))
		i++;
	if ((differ == 'C' && (vars->texture.sky[0] != -1
	&& vars->texture.sky[1] != -1 && vars->texture.sky[2] != -1)) ||
	(differ == 'F' && (vars->texture.floor[0] != -1
	&& vars->texture.floor[1] != -1 && vars->texture.floor[2] != -1)))
		exit_error("Error\nDouble sky/floor?\n");
	fill(vars, &str[i], differ, 0);
	find_comma(str, &i);
	fill(vars, &str[i], differ, 1);
	find_comma(str, &i);
	fill(vars, &str[i], differ, 2);
	while (ft_isdigit(str[i]))
		i++;
	if (str[i] == ',')
		exit_error("Error\nWhat's with the comma?\n");
	return (1);
}
