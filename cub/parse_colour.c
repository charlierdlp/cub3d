/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_colour.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cruiz-de <cruiz-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 11:36:32 by cruiz-de          #+#    #+#             */
/*   Updated: 2020/12/07 13:51:21 by cruiz-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

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
	write(1, "Error\nColour", 13);
	exit(0);
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
	int i;

	if ((!colour_save(vars, &str[i], type, differ)))
		return (0);
	return (1);
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
	fill(vars, &str[i], differ, 0);
	while (ft_isdigit(str[i]))
		i++;
	if (str[i] == ',')
		i++;
	fill(vars, &str[i], differ, 1);
	while (ft_isdigit(str[i]))
		i++;
	if (str[i] == ',')
		i++;
	fill(vars, &str[i], differ, 2);
	if ((!check_colour(vars)))
		return (0);
	return (1);
}
