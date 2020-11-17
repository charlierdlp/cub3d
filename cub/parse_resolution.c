/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_resolution.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cruiz-de <cruiz-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/12 11:58:25 by cruiz-de          #+#    #+#             */
/*   Updated: 2020/11/17 13:40:54 by cruiz-de         ###   ########.fr       */
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

int    resolution(t_vars *vars, char *str)
{
    int i;

    i = 0;
    if (vars->parser.width == -1 && vars->parser.height == -1)
    {
        i++;
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
        printf("%s\n", &str[i]);
        /*
        if(!empty_line(&str[i]))
        {
            write(1, "Error\nWrong Resolution", 23);
            exit(0);
        }
        */
    }
    return(1);
}