/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cruiz-de <cruiz-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/08 10:31:29 by cruiz-de          #+#    #+#             */
/*   Updated: 2020/09/08 13:22:17 by cruiz-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "./minilibx/mlx.h"
#define SCREEN_HIGHT 500
#define SCREEN_WIDTH 500

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
        t_player    player;
        int raycount;
        int ray;
}               t_vars;

int raycasting(t_vars *vars)
{
    int raycos;
    int raysin;
    int rayangle;
    int wall;

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
        wall = 0;
        while(wall == 0)
        {

        }


        rayangle += vars->player.fov/SCREEN_WIDTH;
    }

}