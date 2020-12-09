/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cruiz-de <cruiz-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 11:32:36 by cruiz-de          #+#    #+#             */
/*   Updated: 2020/12/09 12:02:40 by cruiz-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int		check_extension(char *str)
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
	return (0);
}

int		save_path(t_vars *vars, int type, char *str)
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

int		check_text(t_vars *vars, char *str, int type)
{
	int i;

	i = 0;
	if (!ft_isascii(str[i]))
		return (0);
	save_path(vars, type, &str[i]);
	return (0);
}

int		init_textures(t_vars *vars, char *str, t_textdata *texture)
{
	int fd;

	if ((fd = open(str, O_RDONLY)) == -1)
	{
		write(1, "Error\nWrong Texture", 20);
		exit(0);
	}
	check_extension(str);
	texture->img = mlx_xpm_file_to_image(vars->mlx, str,
	&texture->width, &texture->height);
	if (!(texture->img))
	{
		write(1, "Error\nWrong img", 16);
		exit(0);
	}
	texture->addr = mlx_get_data_addr(texture->img, &texture->bits_per_pixel,
	&texture->line_length, &texture->endian);
	return (1);
}

int		parse_textures(t_vars *vars, char *str, int type)
{
	t_textdata	*texture;
	int			i;

	i = 0;
	if (type == 5)
		i = 1;
	else
		i = 2;
	if (!ft_isspace(str[i]))
		exit_error("Error\nWrong Texture\n");
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
	else
		texture = &vars->stexture;
	init_textures(vars, &str[i], texture);
	return (1);
}
