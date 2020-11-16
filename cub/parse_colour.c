/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_colour.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cruiz-de <cruiz-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 11:36:32 by cruiz-de          #+#    #+#             */
/*   Updated: 2020/11/16 13:00:17 by cruiz-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int		check_colour(t_vars *vars, char *str)
{
	if (vars->texture.sky[0] >= 0
		&& vars->texture.sky[0] <= 255
		&& vars->texture.sky[1] >= 0 && vars->texture.sky[1] <= 255
		&& vars->texture.sky[2] >= 0 && vars->texture.sky[2] <= 255)
		return (1);
	if (vars->texture.floor[0] >= 0 && vars->texture.floor[0]
		<= 255
		&& vars->texture.floor[1] >= 0 && vars->texture.floor[1] <= 255
		&& vars->texture.floor[2] >= 0 && vars->texture.floor[2] <= 255)
		return (1);
	return (0);
}

int		colour_save(t_vars *vars, char *str)
{
	if (!ft_isdigit(str[0]))
		return (0);
	vars->texture.sky[0] = ft_atoi(str);
	vars->texture.sky[1] = ft_atoi(str);
	vars->texture.sky[2] = ft_atoi(str);
	return (1);
}

int		is_colour(t_vars *vars, char *str)
{
	int i;

	i = 1;
	while (ft_isspace(str[i]))
		i++;
	if ((!colour_save(vars, str)))
		return (0);
	while (ft_isdigit(str[i]))
		i++;
	if (str[i] == ',')
		i++;
    while (ft_isspace(str[i]))
		i++;
    if ((!colour_save(vars, str)))
		return (0);
	if (str[i] == ',')
		i++;
    while (ft_isspace(str[i]))
		i++;
	if ((!colour_save(vars, str)))
		return (0);
	if ((!check_colour(vars, str)))
		return (0);
}