/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cruiz-de <cruiz-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/08 10:31:29 by cruiz-de          #+#    #+#             */
/*   Updated: 2020/09/09 13:27:03 by cruiz-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "./minilibx/mlx.h"
#define SCREEN_HIGHT 500
#define SCREEN_WIDTH 500

int map [WIDTH][HEIGHT] =
{
    {1,1,1,1,1,1,1,1,1,1},
    {1,0,0,0,0,0,0,0,0,1},
    {1,0,5,0,0,0,0,0,0,1},
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

typedef struct s_walls
{
    int wall;
    int distance;
    int height;
}               t_walls;

int raycasting(t_vars *vars)
{
    int raycos;
    int raysin;
    int rayangle;
    

    rayangle = vars->player.angle - vars->player.fov/2;

    while(vars->raycount < SCREEN_WIDTH) //bucle para recorrer la pantalla y ver la posicion
    {
        vars->x = vars->player.x;
        vars->y = vars->player.y;

        //incrementangle = Player FOV / Screen width;

        //degreetoradians = M_PI * 180;

        raycos = Math.cos(rayangle * (M_PI * 180));
        raysin = Math.sin(rayangle * (M_PI * 180));

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


        rayangle += vars->player.fov/SCREEN_WIDTH;
    }

}