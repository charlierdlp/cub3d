/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cruiz-de <cruiz-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/08 10:31:29 by cruiz-de          #+#    #+#             */
/*   Updated: 2020/10/21 14:00:44 by cruiz-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int map [HEIGHT][WIDTH] =
{
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,1,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

int bitmap [8][8] = 
{
    {1,1,1,1,1,1,1,1},
    {0,0,0,1,0,0,0,1},
    {1,1,1,1,1,1,1,1},
    {0,1,0,0,0,1,0,0},
    {1,1,1,1,1,1,1,1},
    {0,0,0,1,0,0,0,1},
    {1,1,1,1,1,1,1,1},
    {0,1,0,0,0,1,0,0}
};
            

/*
int printline(t_vars *vars, int x1, int y1, int x2, int y2, int color)
{
    while(x1 < x2)
    {
        mlx_pixel_put(vars->mlx, vars->win, x1, y1, color);
        while(y1 < y2)
        {
            mlx_pixel_put(vars->mlx, vars->win, x2, y2, color);
            y1++;
        }
        x2++;
    }  
}
*/

int main()
{
    t_vars vars;

    vars.player.fov = 60;
    vars.player.angle = 0;
    vars.player.x = 3;
    vars.player.y = 3;
    vars.player.rotation = 5;
    vars.keys.w = 0;
    vars.keys.a = 0;
    vars.keys.d = 0;
    vars.keys.s = 0;
    vars.keys.left = 0;
    vars.keys.right = 0;

    vars.mlx = mlx_init();
    vars.win = mlx_new_window(vars.mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "Hello World");
    vars.data.img = mlx_new_image(vars.mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
    vars.data.addr = mlx_get_data_addr(vars.data.img, &vars.data.bits_per_pixel, &vars.data.line_length, &vars.data.endian);
    textures(&vars, "./text/wall1.xpm", &vars.north);
    textures(&vars, "./text/wall2.xpm", &vars.south);
    textures(&vars, "./text/wall3.xpm", &vars.east);
    textures(&vars, "./text/wall4.xpm", &vars.west);
    textures(&vars, "./text/wall4.xpm", &vars.sprite.texture);
    mlx_hook(vars.win, 02, 1L<0, key_press, &vars);
    mlx_hook(vars.win, 03, 1L<0, key_release, &vars);
    mlx_loop_hook(vars.mlx, raycasting, &vars);
    mlx_loop(vars.mlx);
}
