/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cruiz-de <cruiz-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/08 10:31:29 by cruiz-de          #+#    #+#             */
/*   Updated: 2020/09/11 12:41:51 by cruiz-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "./minilibx/mlx.h"
#define WIDTH 10
#define HEIGHT 10
#define SCREEN_HIGHT 500
#define SCREEN_WIDTH 500

int map [WIDTH][HEIGHT] =
{
    {1,1,1,1,1,1,1,1,1,1},
    {1,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,1},
    {1,0,0,1,1,0,1,0,0,1},
    {1,0,0,1,0,0,1,0,0,1},
    {1,0,0,1,0,0,1,0,0,1},
    {1,0,0,1,0,1,1,0,0,1},
    {1,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,1},
    {1,1,1,1,1,1,1,1,1,1}
}; 

typedef struct s_player
{   
    int x;
    int y;
    int fov;
    int angle;
    
}              t_player;

typedef struct s_walls
{
    int wall;
    int distance;
    int height;
}               t_walls;

typedef struct  s_vars {
        void    *mlx;
        void    *win;
        int      x;
        int      y;
        int raycount;
        int ray;
        t_player    player;
        t_walls     walls;
}               t_vars;

int printline(t_vars *vars, int x1, int y1, int x2, int y2, int color)
{
    while(x1 < x2)
    {
        mlx_pixel_put(vars->mlx, vars->win, x1, y1, color);
        while(y1 < y2)
        {
            mlx_pixel_put(vars->mlx, vars->win, x2, y2, color);
            y2++;
        }
        x2++;
    }  
}

int raycasting(t_vars *vars)
{
    float raycos;
    float raysin;
    float rayangle;
    

    rayangle = vars->player.angle - vars->player.fov/2;

    while(vars->raycount < SCREEN_WIDTH) //bucle para recorrer la pantalla y ver la posicion
    {
        vars->x = vars->player.x;
        vars->y = vars->player.y;

        //incrementangle = Player FOV / Screen width;

        //degreetoradians = M_PI * 180;

        raycos = cos(rayangle * (M_PI * 180));
        raysin = sin(rayangle * (M_PI * 180));

        //wall check
    
        vars->walls.wall = 0;
        while(vars->walls.wall == 0)
        {
            vars->x += raycos;
            vars->y += raysin;
            vars->walls.wall = map[(int)vars->y][(int)vars->x];

        }

        vars->walls.distance = sqrt(pow(vars->player.x - vars->x, 2) + pow(vars->player.y - vars->y, 2));

        vars->walls.height = (int)((vars->walls.height/2) / vars->walls.distance);

        printline(vars, vars->raycount, 0, vars->raycount, vars->walls.height/2 - vars->walls.height, 0x0000ff);
        printline(vars, vars->raycount, vars->walls.height/2 - vars->walls.height, vars->raycount, vars->walls.height/2 + vars->walls.height, 0xff0000);
        printline(vars, vars->raycount, vars->walls.height/2 + vars->walls.height, vars->raycount, vars->walls.height, 0x00ff00);

        rayangle += vars->player.fov/SCREEN_WIDTH;
    }

}

int move(int keycode, t_vars *vars)
{
    int i = 0;
    int j = 0;
    if (keycode == 53)
    {
        mlx_destroy_window(vars->mlx, vars->win);
        exit(0);
    }
    if(keycode == 123 && (map[i][j - 1] == 0 || map[i][j - 1] == 5))
        vars->x = vars->x-1; 
    if(keycode == 124 && (map[i][j + 1] == 0 || map[i][j + 1] == 5))
        vars->x = vars->x+1;
    if(keycode == 126)
        vars->y = vars->y-1;
    if(keycode == 125)
        vars->y = vars->y+1;

    return(0);
}

int main()
{
    t_vars vars;

    vars.player.fov = 60;
    vars.player.angle = 0;
    vars.player.x = 2;
    vars.player.y = 2;
    vars.raycount = 0;

    printf("%d\n" ,vars.player.fov);
    printf("%d\n", vars.player.angle);
    printf("%d\n", vars.player.x);
    printf("%d\n", vars.player.y);
    printf("%d\n", vars.raycount)
    vars.mlx = mlx_init();
    vars.win = mlx_new_window(vars.mlx, 1280, 1000, "Hello World");
   // mlx_hook(vars.win, 2, 1L<0, move, &vars);
    //mlx_loop_hook(vars.mlx, print_map, &vars)
    mlx_loop_hook(vars.mlx, raycasting, &vars);
    mlx_loop(vars.mlx);
}
