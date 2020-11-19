/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cruiz-de <cruiz-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/08 10:31:29 by cruiz-de          #+#    #+#             */
/*   Updated: 2020/11/19 12:37:15 by cruiz-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int map [HEIGHT][WIDTH] =
{
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,2,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,1,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,2,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

void    *ft_play_music(t_vars *vars)
{
    if (vars->pid == 0)
    {
        system("afplay ./music/theme.mp3");
        wait(NULL);
    }
    return NULL;
}


void	playtrack(char *track)
{
	char	*args[3];

	args[0] = "afplay";
	args[1] = track;
	args[2] = NULL;
	execvp(args[0], args);
}

void    init_vars(t_vars *vars)
{
    vars->player.fov = 60;
    vars->player.angle = 0;
    vars->player.x = 3;
    vars->player.y = 3;
    vars->player.rotation = 5;
    vars->keys.w = 0;
    vars->keys.a = 0;
    vars->keys.d = 0;
    vars->keys.s = 0;
    vars->keys.left = 0;
    vars->keys.right = 0;
    vars->map.width = 0;
    vars->north.path = NULL;
    vars->south.path = NULL;
    vars->east.path = NULL;
    vars->west.path = NULL;
    vars->stexture.path = NULL;
    vars->parser.width = 0;
    vars->parser.height = 0;
}

int main(int argc, char **argv)
{
    t_vars vars;

    init_vars(&vars);
    vars.mlx = mlx_init();
    read_text(&vars, argv[1]);
    /*
    vars.win = mlx_new_window(vars.mlx, vars.parser.width, vars.parser.height, "Hello World");
    vars.data.img = mlx_new_image(vars.mlx, vars.parser.width, vars.parser.height);
    vars.data.addr = mlx_get_data_addr(vars.data.img, &vars.data.bits_per_pixel, &vars.data.line_length, &vars.data.endian);

    textures(&vars, "./text/brick1.xpm", &vars.north);
    textures(&vars, "./text/brick2.xpm", &vars.south);
    textures(&vars, "./text/brick3.xpm", &vars.east);
    textures(&vars, "./text/brick4.xpm", &vars.west);

    sprite_array(&vars);
    //textures(&vars, "./text/8bit.xpm", &vars.stexture);
    vars.pid = fork();

	if (!vars.pid)
		playtrack("./music/theme.mp3");

    mlx_hook(vars.win, 02, 1L<0, key_press, &vars);
    mlx_hook(vars.win, 03, 1L<0, key_release, &vars);
    mlx_hook(vars.win, 17, 1L<0, x_close, &vars);
    mlx_loop_hook(vars.mlx, raycasting, &vars);
    mlx_loop(vars.mlx);
    */
}
