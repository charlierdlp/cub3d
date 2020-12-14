/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   music.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cruiz-de <cruiz-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/02 13:08:43 by cruiz-de          #+#    #+#             */
/*   Updated: 2020/12/07 13:59:11 by cruiz-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	*ft_play_music(t_vars *vars)
{
	if (vars->pid == 0)
	{
		system("afplay ./music/theme.mp3");
		wait(NULL);
	}
	return (NULL);
}

void	playtrack(char *track)
{
	char	*args[3];

	args[0] = "afplay";
	args[1] = track;
	args[2] = NULL;
	execvp(args[0], args);
}

void	start_music(t_vars *vars)
{
	vars->pid = fork();
	if (vars->pid == 0)
		playtrack("./music/theme.mp3");
}
