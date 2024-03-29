/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cruiz-de <cruiz-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 11:13:04 by cruiz-de          #+#    #+#             */
/*   Updated: 2020/12/10 11:51:23 by cruiz-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#define BUFFER_SIZE 1000

int	ft_separator(char **content, char **line)
{
	char	*tmp;
	int		i;
	int		j;

	if (!*content)
	{
		*line = ft_strdup("");
		return (0);
	}
	if (!ft_strchr(*content, '\n'))
	{
		*line = ft_strdup(*content);
		free(*content);
		*content = NULL;
		return (0);
	}
	i = ft_strlen(*content);
	j = ft_strlen(ft_strchr(*content, '\n'));
	*line = ft_substr(*content, 0, i - j);
	tmp = *content;
	*content = ft_strdup(ft_strchr(tmp, '\n') + 1);
	free(tmp);
	return (1);
}

int	get_next_line(int fd, char **line)
{
	static char	*content;
	char		*tmp;
	char		*buf;
	int			i;

	if (!(buf = malloc(sizeof(char) * (BUFFER_SIZE + 1))))
		return (-1);
	if (fd == -1 || BUFFER_SIZE < 1 || read(fd, buf, 0) == -1 || line == NULL)
		return (-1);
	while ((i = read(fd, buf, BUFFER_SIZE)) > 0)
	{
		buf[i] = '\0';
		if (!content)
			content = ft_strdup(buf);
		else
		{
			tmp = content;
			content = ft_strjoin(content, buf);
			free(tmp);
		}
		if (ft_strchr(buf, '\n'))
			break ;
	}
	free(buf);
	return (ft_separator(&content, line));
}
