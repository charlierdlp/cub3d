/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_start.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cruiz-de <cruiz-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 10:42:17 by cruiz-de          #+#    #+#             */
/*   Updated: 2020/11/11 13:55:32 by cruiz-de         ###   ########.fr       */
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

void    check_text(char *str)
{
    int i;
    
    i = 0;
    if(!(ft_isspace(str[i])))
       return(0);
    while (ft_isspace(str[i]))
	    i++;
    if (!ft_isascii(str[i]))
	    return (0);
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

void        init_textures(t_vars *vars, char *str);
{
    int fd;

    if((fd = open(str, O_RDONLY)) == -1)
    {
        write(1, "Error\n Wrong Texture");
        exit(0);
    }
    
}

void        parse_textures(t_vars *vars, char *str, int type)
{
    int i;

    i = 0;
    if(type == 1)
    {
        check_text(&str[i]);

        
    }



}

int find_text(t_vars *vars, char *str)
{
    int     i;

    i = 0;
    if (str[i] == 'N' && str[i + 1] == 'O')
        textures(vars, str, 1);
    else if (str[i] == 'S' && str[i + 1] == 'O')
    else if (str[i] == 'W' && str[i + 1] == 'E')
    else if (str[i] == 'E' && str[i + 1] == 'A')
    else if (str[i] == 'S')
    else if (str[i] == 'R')
        resolution(vars, str);

    return(0);
}

int     read_file(t_vars *vars, int fd)
{
    char    *line;
    int     i;
    while((i = get_next_line(fd, &line)) > 0)
    {
        find_text(vars, line);
    }
    return(0);
}

void    read_text(t_vars *vars, char *file)
{
    int fd;

    if ((fd = open(file ,O_RDONLY)) == -1)
    {
        write(1, "Error\nFile not found", 21);
        exit(0);
    }
    read_file(&vars, fd);

}