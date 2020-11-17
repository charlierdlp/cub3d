/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_start.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cruiz-de <cruiz-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 10:42:17 by cruiz-de          #+#    #+#             */
/*   Updated: 2020/11/17 13:14:04 by cruiz-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int    check_text(t_vars *vars, char *str, int type)
{
    int i;
    
    i = 0;
    if(!(ft_isspace(str[i])))
       return(0);
    while (ft_isspace(str[i]))
	    i++;
    if (!ft_isascii(str[i]))
	    return (0);
    save_path(vars, type, str);
    return(0);
}

int     save_path(t_vars *vars, int type, char *str)
{
    if (type == 1 && vars->north.path != '\0')
		vars->north.path = ft_strtrim(str, " ");
	else if (type == 2 && vars->south.path != '\0')
		vars->south.path = ft_strtrim(str, " ");
	else if (type == 3 && vars->east.path != '\0')
		vars->east.path = ft_strtrim(str, " ");
	else if (type == 4 && vars->west.path != '\0')
		vars->west.path = ft_strtrim(str, " ");
	else if (type == 5 && vars->stexture.path != '\0')
		vars->stexture.path = ft_strtrim(str, " ");
	return (1);
}

int     init_textures(t_vars *vars, char *str, t_textdata *texture)
{
    int fd;

    printf("%s\n", str);
    if((fd = open(str, O_RDONLY)) == -1)
    {
        write(1, "Error\n Wrong Texture", 21);
        exit(0);
    }
    texture->img = mlx_xpm_file_to_image(vars->mlx, str,
	&texture->width, &texture->height);
    if(!(texture->img))
    {
        write(1, "Error\n Wrong img" , 17);
        return(0);
    }
    texture->addr = mlx_get_data_addr(texture->img, &texture->bits_per_pixel,
	&texture->line_length, &texture->endian);
	return (1);
}


int        parse_textures(t_vars *vars, char *str, int type)
{
    t_textdata *texture;
    int i;

    i = 0;
    if (type == 5)
        i = 1;
    else
        i = 2;
    while (ft_isspace(str[i]))
	    i++;
    check_text(vars, &str[i], type);
    if (type == 1)
        texture = &vars->north;
    else if (type == 2)
        texture = &vars->south;
    else if (type == 3)
        texture = &vars->west;
    else if (type == 4)
        texture = &vars->east;
    else if (type == 5)
        texture = &vars->stexture;
    init_textures(vars, &str[i], texture);
    return(0);
}

int find_text(t_vars *vars, char *str)
{
    int     i;

    i = 0;
    if (str[i] == 'N' && str[i + 1] == 'O')
        parse_textures(vars, str, 1);
    else if (str[i] == 'S' && str[i + 1] == 'O')
        parse_textures(vars, str, 2);
    else if (str[i] == 'W' && str[i + 1] == 'E')
        parse_textures(vars, str, 3);
    else if (str[i] == 'E' && str[i + 1] == 'A')
        parse_textures(vars, str, 4);
    else if (str[i] == 'S')
        parse_textures(vars, str, 5);
    else if (str[i] == 'R')
        resolution(vars, str);
    else
        is_colour(vars, str);

    return(0);
}

int     read_file(t_vars *vars, int fd)
{
    char    *line;
    int     i;
    while((i = get_next_line(fd, &line)) > 0)
    {
        find_text(vars, line);
        free(line);
    }
    return(0);
}

int    read_text(t_vars *vars, char *file)
{
    int fd;

    if ((fd = open(file ,O_RDONLY)) == -1)
    {
        write(1, "Error\nFile not found", 21);
        exit(0);
    }
    read_file(vars, fd);
    return(0);
}