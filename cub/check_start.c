/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_start.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cruiz-de <cruiz-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 10:42:17 by cruiz-de          #+#    #+#             */
/*   Updated: 2020/12/07 13:54:51 by cruiz-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int		charlie(t_vars *vars, char *str, int i)
{
	if (str[i] == 'N' && str[i + 1] == 'O')
		return (parse_textures(vars, &str[i], 1));
	else if (str[i] == 'S' && str[i + 1] == 'O')
		return (parse_textures(vars, &str[i], 2));
	else if (str[i] == 'W' && str[i + 1] == 'E')
		return (parse_textures(vars, &str[i], 3));
	else if (str[i] == 'E' && str[i + 1] == 'A')
		return (parse_textures(vars, &str[i], 4));
	else if (str[i] == 'S')
		return (parse_textures(vars, &str[i], 5));
	else if (str[i] == 'R')
		return (resolution(vars, &str[i]));
	else if (str[i] == 'F' || str[i] == 'C')
		return (is_colour(vars, &str[i]));
	return (0);
}

void	exit_error(char *str)
{
	if (str)
		write(1, str, ft_strlen(str));
	exit(0);
}

int		find_text(t_vars *vars, char *str, int fd)
{
	int			i;

	i = 0;
	while (ft_isspace(str[i]))
		i++;
	if (charlie(vars, &str[i], i))
		;
	else if (str[i] == '\0')
	{
		if (vars->map.start != 0)
			vars->map.start = 2;
		return (1);
	}
	else if (str[i] == '\0' && vars->map.start == 1)
		exit_error("Error\nOpen Map\n");
	else if (ft_strchr("012", str[i]))
		count_map(vars, &str[i]);
	else if ((vars->map.start == 1 || vars->map.start == 2)
	&& !ft_strchr("012", str[i]))
		exit_error("Error\nFinished Map\n");
	return (0);
}

int		read_file(t_vars *vars, int fd)
{
	char		*line;
	int			i;

	while ((i = get_next_line(fd, &line)) > 0)
	{
		find_text(vars, line, fd);
		free(line);
	}
	find_text(vars, line, fd);
	free(line);
	return (0);
}

int		read_text(t_vars *vars, char *file)
{
	int			fd;

	if ((fd = open(file, O_RDONLY)) == -1)
	{
		write(1, "Error\nFile not found", 21);
		exit(0);
	}
	read_file(vars, fd);
	close(fd);
	if ((fd = open(file, O_RDONLY)) == -1)
	{
		write(1, "Error\nFile not found", 21);
		exit(0);
	}
	start_map(vars, fd);
	return (0);
}
