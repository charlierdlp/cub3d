/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_colour.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cruiz-de <cruiz-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 11:36:32 by cruiz-de          #+#    #+#             */
/*   Updated: 2020/11/18 12:52:25 by cruiz-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int		check_colour(t_vars *vars)
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

int		colour_save(t_vars *vars, char *str, int type, char differ)
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
	else
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

int		is_colour(t_vars *vars, char *str)
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
	if ((!colour_save(vars, &str[i], 0, differ)))
		return (0);
	while (ft_isdigit(str[i]))
		i++;
	if (str[i] == ',')
		i++;
    while (ft_isspace(str[i]))
		i++;
    if ((!colour_save(vars, &str[i], 1, differ)))
		return (0);
	while (ft_isdigit(str[i]))
		i++;
	if (str[i] == ',')
		i++;
    while (ft_isspace(str[i]))
		i++;
	if ((!colour_save(vars, &str[i], 2, differ)))
		return (0);
	if ((!check_colour(vars)))
		return (0);
	return(1);
}