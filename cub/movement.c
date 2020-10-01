/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cruiz-de <cruiz-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/29 11:22:38 by cruiz-de          #+#    #+#             */
/*   Updated: 2020/09/29 11:23:35 by cruiz-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "cub.h"

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