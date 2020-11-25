/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cruiz-de <cruiz-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 11:32:36 by cruiz-de          #+#    #+#             */
/*   Updated: 2020/11/20 13:32:55 by cruiz-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int     check_extension(t_vars *vars, char *str)
{

    if (!ft_strrchr(str, '.'))
    {
        write(1, "Error\nWrong Texture", 20);
        exit(0);
    }
    if (ft_strncmp(str + (ft_strlen(str) - 4), ".xpm", 4))
	{
		write(1, "Error\nInvalid name of file", 27);
		exit(0);
	}
    return(0);
}

int     save_path(t_vars *vars, int type, char *str)
{
    if (type == 1 && vars->north.path == NULL)
		vars->north.path = ft_strtrim(str, " ");
	else if (type == 2 && vars->south.path == NULL)
		vars->south.path = ft_strtrim(str, " ");
	else if (type == 3 && vars->east.path == NULL)
		vars->east.path = ft_strtrim(str, " ");
	else if (type == 4 && vars->west.path == NULL)
		vars->west.path = ft_strtrim(str, " ");
	else if (type == 5 && vars->stexture.path == NULL)
		vars->stexture.path = ft_strtrim(str, " ");
	return (1);
}

int    check_text(t_vars *vars, char *str, int type)
{
    int i;
    
    i = 0;
    if (!ft_isascii(str[i]))
	    return (0);
    save_path(vars, type, &str[i]);
    return(0);
}

int     init_textures(t_vars *vars, char *str, t_textdata *texture)
{
    int fd;

    if((fd = open(str, O_RDONLY)) == -1)
    {
        write(1, "Error\nWrong Texture", 20);
        exit(0);
    }
    check_extension(vars, str);
    texture->img = mlx_xpm_file_to_image(vars->mlx, str,
	&texture->width, &texture->height);
    if(!(texture->img))
    {
        write(1, "Error\nWrong img" , 16);
        return(0);
    }
    texture->addr = mlx_get_data_addr(texture->img, &texture->bits_per_pixel,
	&texture->line_length, &texture->endian);
	return (1);
}