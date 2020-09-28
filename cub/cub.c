/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cruiz-de <cruiz-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/08 10:31:29 by cruiz-de          #+#    #+#             */
/*   Updated: 2020/09/28 13:41:38 by cruiz-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int map [HEIGHT][WIDTH] =
{
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,1,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
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

int move(int keycode, t_vars *vars)
{
    if (keycode == 53)
    {
        mlx_destroy_window(vars->mlx, vars->win);
        exit(0);
    }
    if(keycode == 123)
        vars->player.angle -= vars->player.rotation;
    if(keycode == 124)
        vars->player.angle += vars->player.rotation;
    if(keycode == 13) //W
    {
       vars->player.cos = cos(vars->player.angle * M_PI / 180) * vars->player.speed;
       vars->player.sin = sin(vars->player.angle * M_PI / 180) * vars->player.speed;
       if(map[(int)(vars->player.y + vars->player.sin)][(int)(vars->player.x + vars->player.cos)] == 0)
       {
       vars->player.x += vars->player.cos;
       vars->player.y += vars->player.sin;
       }
    }
    if(keycode == 1) //S
    {
       vars->player.cos = cos(vars->player.angle * M_PI / 180) * vars->player.speed;
       vars->player.sin = sin(vars->player.angle * M_PI / 180) * vars->player.speed;
       if(map[(int)(vars->player.y - vars->player.sin)][(int)(vars->player.x - vars->player.cos)] == 0)
       {
       vars->player.x -= vars->player.cos;
       vars->player.y -= vars->player.sin;
       }
    }
    if(keycode == 0) //A
    {
       vars->player.cos = cos((vars->player.angle + 90) * M_PI / 180) * vars->player.speed;
       vars->player.sin = sin((vars->player.angle + 90) * M_PI / 180) * vars->player.speed;
       if(map[(int)(vars->player.y - vars->player.sin)][(int)(vars->player.x - vars->player.cos)] == 0)
       {
       vars->player.x -= (vars->player.cos);
       vars->player.y -= (vars->player.sin);
       }
    }
    if(keycode == 2) //D
    {
       vars->player.cos = cos((vars->player.angle - 90) * M_PI / 180) * vars->player.speed;
       vars->player.sin = sin((vars->player.angle - 90) * M_PI / 180) * vars->player.speed;
       if(map[(int)(vars->player.y - vars->player.sin)][(int)(vars->player.x - vars->player.cos)] == 0)
       {
       vars->player.x -= (vars->player.cos);
       vars->player.y -= (vars->player.sin);
       }
    }
    return(0);
}

int main()
{
    t_vars vars;

    vars.player.fov = 60;
    vars.player.angle = 0;
    vars.player.x = 2;
    vars.player.y = 2;
    vars.player.speed = 0.2;
    vars.player.rotation = 5;

    vars.mlx = mlx_init();
    vars.win = mlx_new_window(vars.mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "Hello World");
    vars.data.img = mlx_new_image(vars.mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
    vars.data.addr = mlx_get_data_addr(vars.data.img, &vars.data.bits_per_pixel, &vars.data.line_length, &vars.data.endian);
    mlx_hook(vars.win, 2, 1L<0, move, &vars);
    mlx_loop_hook(vars.mlx, raycasting, &vars);
    mlx_loop(vars.mlx);
}
