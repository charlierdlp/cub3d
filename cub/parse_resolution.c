/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_resolution.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cruiz-de <cruiz-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/12 11:58:25 by cruiz-de          #+#    #+#             */
/*   Updated: 2020/11/15 12:20:02 by cruiz-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int     empty_line(char *str)
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

void    resolution(t_vars *vars, char *str)
{
    int i;

    i = 0;
    while(ft_isspace(str[i]))
        i++;
	if (!ft_isdigit(str[i]))
		return (0);
    while(ft_isspace(str[i]))
        i++;
    if(ft_isdigit(str[i]))
        vars->parser.width = ft_atoi(&str[i]);
    while(ft_isspace(str[i]))
        i++;
    if(ft_isdigit(str[i]))
        vars->parser.height = ft_atoi(&str[i]);
    if(!empty_line(&str[i]))
    {
        write(1, "Error\n Wrong Resolution", 24);
        exit(0);
    }
    return(1);
}